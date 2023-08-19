#pragma once

#include <cassert>
#include <memory>
#include <functional>

template <bool Const, typename Class, typename Signature>
struct MemberFunctionPtrType;

template <typename Class, typename RetType, typename... ParamTypes>
struct MemberFunctionPtrType<false, Class, RetType(ParamTypes...)>
{
    typedef RetType (Class::*type)(ParamTypes...);
};

template <typename Class, typename RetType, typename... ParamTypes>
struct MemberFunctionPtrType<true, Class, RetType(ParamTypes...)>
{
    typedef RetType (Class::*type)(ParamTypes...) const;
};

template <typename Signature, typename... ArgTypes>
class DelegateInstanceBase;

/**
 * Base class for all the function pointer wrappers. Holds additional payload data that can be
 * passed with the parameters provided while invoking the underlying function.
 */
template <typename RetType, typename... ParamTypes, typename... ArgTypes>
class DelegateInstanceBase<RetType(ParamTypes...), ArgTypes...> : public IDelegateInstance
{
public:
    template <typename... InArgTypes>
    DelegateInstanceBase(InArgTypes &&...args)
        : payload(std::forward<InArgTypes>(args)...)
    {
    }

    /** Create a copy of self. */
    virtual void CreateCopy(DelegateBase &base) const = 0;

    /** Invokes the underlying function pointer. */
    virtual RetType Invoke(ParamTypes...) const = 0;

    /**
     * Invokes the underlying function pointer only if the function pointer is bound to a valid
     * function.
     *
     * @returns True if the fuction pointer was valid and return successfully.
     */
    virtual bool InvokeSafely(ParamTypes...) const = 0;

protected:
    std::tuple<ArgTypes...> payload;
};

namespace Details {

template <typename FunctionType, typename TupleType, typename... ArgTypes, std::size_t... Indices>
constexpr decltype(auto) ApplyAfterImpl(FunctionType &&f, TupleType &&t,
                                        std::index_sequence<Indices...>, ArgTypes &&...args)
{
    return std::invoke(std::forward<FunctionType>(f), std::forward<ArgTypes>(args)...,
                       std::get<Indices>(std::forward<TupleType>(t))...);
}

} // namespace Details

/**
 * Utility function to invoke a function with provided arguments followed by the tuple of additional
 * parameters.
 *
 * @returns Result of the function call.
 */
template <typename FunctionType, typename TupleType, typename... ArgTypes>
constexpr decltype(auto) ApplyAfter(FunctionType &&f, TupleType &&t, ArgTypes &&...args)
{
    return Details::ApplyAfterImpl(
        std::forward<FunctionType>(f), std::forward<TupleType>(t),
        std::make_index_sequence<std::tuple_size_v<std::decay_t<TupleType>>>{},
        std::forward<ArgTypes>(args)...);
}

template <typename Signature, typename... ArgTypes>
class StaticDelegateInstance;

/**
 * Wrapper around a static function pointer that can be bound to a delegate.
 */
template <typename RetType, typename... ParamTypes, typename... ArgTypes>
class StaticDelegateInstance<RetType(ParamTypes...), ArgTypes...>
    : public DelegateInstanceBase<RetType(ParamTypes...), ArgTypes...>
{
    using Base = DelegateInstanceBase<RetType(ParamTypes...), ArgTypes...>;

public:
    using FunctionPtrType = RetType (*)(ParamTypes..., ArgTypes...);

    template <typename... InArgTypes>
    explicit StaticDelegateInstance(FunctionPtrType function, InArgTypes &&...args)
        : Base(std::forward<InArgTypes>(args)...)
        , func(function)
    {
        assert(func != nullptr);
    }

    void CreateCopy(DelegateBase &base) const final
    {
        new (base) StaticDelegateInstance(*this);
    }

    RetType Invoke(ParamTypes... params) const final
    {
        return ApplyAfter(func, this->payload, params...);
    }

    bool InvokeSafely(ParamTypes... params) const final
    {
        (void)ApplyAfter(func, this->payload, params...);
        return true;
    }

private:
    FunctionPtrType func;
};

template <typename Signature, typename FunctorType, typename... ArgTypes>
class FunctorDelegateInstance;

template <typename RetType, typename... ParamTypes, typename FunctorType, typename... ArgTypes>
class FunctorDelegateInstance<RetType(ParamTypes...), FunctorType, ArgTypes...>
    : public DelegateInstanceBase<RetType(ParamTypes...), ArgTypes...>
{
    static_assert(std::is_same_v<FunctorType, std::remove_reference_t<FunctorType>>,
                  "FunctorType cannot be a reference");
    using Base = DelegateInstanceBase<RetType(ParamTypes...), ArgTypes...>;

public:
    template <typename InFunctorType, typename... InArgTypes>
    FunctorDelegateInstance(InFunctorType &&inFunctor, InArgTypes &&...args)
        : Base(std::forward<InArgTypes>(args)...)
        , functor(std::forward<InFunctorType>(inFunctor))
    {
    }

    void CreateCopy(DelegateBase &base) const final
    {
        new (base) FunctorDelegateInstance(*this);
    }

    RetType Invoke(ParamTypes... params) const final
    {
        return ApplyAfter(functor, this->payload, params...);
    }

    bool InvokeSafely(ParamTypes... params) const final
    {
        (void)ApplyAfter(functor, this->payload, params...);
        return true;
    }

private:
    mutable std::remove_const_t<FunctorType> functor;
};

template <bool Const, typename Class, typename Signature, typename... ArgTypes>
class RawMethodDelegateInstance;

template <bool Const, typename Class, typename RetType, typename... ParamTypes,
          typename... ArgTypes>
class RawMethodDelegateInstance<Const, Class, RetType(ParamTypes...), ArgTypes...>
    : DelegateInstanceBase<RetType(ParamTypes...), ArgTypes...>
{
    using Base = DelegateInstanceBase<RetType(ParamTypes...), ArgTypes...>;

public:
    using FunctionPtrType =
        typename MemberFunctionPtrType<Const, Class, RetType(ParamTypes..., ArgTypes...)>::type;

public:
    template <typename... InArgTypes>
    RawMethodDelegateInstance(Class *inInstance, FunctionPtrType function, InArgTypes &&...args)
        : Base(std::forward<ArgTypes>(args)...)
        , instance(inInstance)
        , func(function)
    {
        assert(func != nullptr && instance != nullptr);
    }

    void CreateCopy(DelegateBase &base) const final
    {
        new (base) RawMethodDelegateInstance(*this);
    }

    RetType Invoke(ParamTypes... params) const final
    {
        return ApplyAfter(func, this->payload, instance, params...);
    }

    bool InvokeSafely(ParamTypes... params) const final
    {
        (void)ApplyAfter(func, this->payload, instance, params...);
        return true;
    }

private:
    /** Instance on which the member function will be called. */
    Class *instance;
    /** Pointer to the original function. */
    FunctionPtrType func;
};

template <bool Const, typename Class, typename Signature, typename... ArgTypes>
class SPMethodDelegateInstance;

template <bool Const, typename Class, typename RetType, typename... ParamTypes,
          typename... ArgTypes>
class SPMethodDelegateInstance<Const, Class, RetType(ParamTypes...), ArgTypes...>
    : DelegateInstanceBase<RetType(ParamTypes...), ArgTypes...>
{
    using Base = DelegateInstanceBase<RetType(ParamTypes...), ArgTypes...>;

public:
    using FunctionPtrType =
        typename MemberFunctionPtrType<Const, Class, RetType(ParamTypes..., ArgTypes...)>::type;

public:
    template <typename... InArgTypes>
    SPMethodDelegateInstance(const std::shared_ptr<Class> &inInstance, FunctionPtrType function,
                             InArgTypes &&...args)
        : Base(std::forward<InArgTypes>(args)...)
        , instance(inInstance)
        , func(function)
    {
        assert(func != nullptr);
    }

    void CreateCopy(DelegateBase &base) const final
    {
        new (base) SPMethodDelegateInstance(*this);
    }

    RetType Invoke(ParamTypes... params) const final
    {
        return ApplyAfter(func, this->payload, instance, params...);
    }

    bool InvokeSafely(ParamTypes... params)
    {
        return false;
    }

private:
    /** Instance on which the member function will be called. */
    std::weak_ptr<Class> instance;
    /** Pointer to the original function. */
    FunctionPtrType func;
};
