#pragma once

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

template <typename Signature>
class DelegateInstanceBase;

template <typename RetType, typename... ParamTypes>
class DelegateInstanceBase<RetType(ParamTypes...)> : public IDelegateInstance
{
public:
    template <typename... InParamTypes>
    DelegateInstanceBase(InParamTypes &&...params)
        : payload(std::forward<InParamTypes>(params)...)
    {
    }

    virtual RetType Invoke(ParamTypes...) const = 0;
    virtual void InvokeIfBound(ParamTypes...) const = 0;

protected:
    std::tuple<ParamTypes...> payload;
};

template <typename Signature, typename... VarTypes>
class StaticDelegateInstance;

template <typename RetType, typename... ParamTypes>
class StaticDelegateInstance<RetType(ParamTypes...)>
    : public DelegateInstanceBase<RetType(ParamTypes...)>
{
public:
    using FunctionPtrType = RetType (*)(ParamTypes...);
    using Base = DelegateInstanceBase<RetType(ParamTypes...)>;

    explicit StaticDelegateInstance(FunctionPtrType inFunction)
        : staticFunc(inFunction)
    {
    }

    RetType Invoke(ParamTypes... params) const
    {
        return std::invoke(staticFunc, params...);
    }

    void InvokeIfBound(ParamTypes... params) const
    {
    }

private:
    FunctionPtrType staticFunc;
};

template <typename Signature, typename FunctorType>
class FunctorDelegateInstance;

template <typename RetType, typename FunctorType, typename... ParamTypes>
class FunctorDelegateInstance<RetType(ParamTypes...), FunctorType>
    : DelegateInstanceBase<RetType(ParamTypes...)>
{
public:
    template <typename InFunctorType, typename... InParamTypes>
    FunctorDelegateInstance(InFunctorType &&inFunctor, InParamTypes &&...params)
        : functor(std::forward<InFunctorType>(inFunctor))
    {
    }

    RetType Invoke(ParamTypes... params) const
    {
    }

    void InvokeIfBound(ParamTypes... params) const
    {
    }

private:
    mutable typename std::remove_const<FunctorType>::type functor;
};

template <bool Const, typename Class, typename Signature>
class RawMethodDelegateInstance;

template <bool Const, typename Class, typename RetType, typename... ParamTypes>
class RawMethodDelegateInstance<Const, Class, RetType(ParamTypes...)>
    : DelegateInstanceBase<RetType(ParamTypes...)>
{
public:
    using FunctionPtrType =
        typename MemberFunctionPtrType<Const, Class, RetType(ParamTypes...)>::type;

public:
    RawMethodDelegateInstance(Class *inInstance, FunctionPtrType inMethodPtr,
                              ParamTypes &&...params)
        : instance(inInstance)
        , methodPtr(inMethodPtr)
    {
    }

    RetType Invoke(ParamTypes... params) const
    {
        using MutableClass = typename std::remove_const<Class>::type;
        MutableClass *mutInstance = const_cast<MutableClass *>(instance);
        // std::invoke();
    }

    void InvokeIfBound(ParamTypes... params) const
    {
    }

private:
    /** Instance on which the member function will be called. */
    Class *instance;
    /** Pointer to the original function. */
    FunctionPtrType methodPtr;
};

template <bool Const, typename Class, typename Signature>
class SPMethodDelegateInstance;

template <bool Const, typename Class, typename RetType, typename... ParamTypes>
class SPMethodDelegateInstance<Const, Class, RetType(ParamTypes...)>
    : DelegateInstanceBase<RetType(ParamTypes...)>
{
public:
    using FunctionPtrType =
        typename MemberFunctionPtrType<Const, Class, RetType(ParamTypes...)>::type;

public:
    SPMethodDelegateInstance(const std::shared_ptr<Class> &inInstance, FunctionPtrType inMethodPtr,
                             ParamTypes &&...params)
        : instance(inInstance)
        , methodPtr(inMethodPtr)
    {
    }

    RetType Invoke(ParamTypes... params) const final
    {
        // using MutableClass = std::remove_const_t<Class>;
        // std::invoke();
    }

    void InvokeIfBound(ParamTypes... params)
    {
    }

private:
    /** Instance on which the member function will be called. */
    std::weak_ptr<Class> instance;
    /** Pointer to the original function. */
    FunctionPtrType methodPtr;
};
