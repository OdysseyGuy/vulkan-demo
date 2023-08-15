#pragma once

#include <cassert>
#include <functional>

template <typename Signature>
class Delegate;

template <typename RetType, typename... ParamTypes>
class Delegate<RetType(ParamTypes...)> : DelegateBase
{
    using FunctionType = RetType(ParamTypes...);
    using DelegateInstanceBaseType = DelegateInstanceBase<RetType(ParamTypes...)>;

public:
    template <typename... VarTypes>
    [[nodiscard]] inline static Delegate<FunctionType>
    CreateStatic(typename std::type_identity<FunctionType>::type inFunction, VarTypes &&...vars)
    {
        Delegate<FunctionType> Result;
        new (Result) StaticDelegateInstance<FunctionType>(inFunction);
        return Result;
    }

    template <typename FunctorType, typename... VarTypes>
    [[nodiscard]] inline static Delegate<FunctionType>
    CreateLambda(typename std::type_identity<FunctionType>::type inFunction, VarTypes &&...vars)
    {
        Delegate<FunctionType> Result;
        new (Result) FunctorDelegateInstance<FunctionType>(inFunction);
        return Result;
    }

    template <typename FunctorType, typename... VarTypes>
    [[nodiscard]] inline static Delegate<FunctionType>
    CreateRaw(typename std::type_identity<FunctionType>::type inFunction, VarTypes &&...vars)
    {
        Delegate<FunctionType> Result;
        new (Result) RawMethodDelegateInstance<FunctionType>(inFunction);
        return Result;
    }

    template <typename FunctorType, typename... VarTypes>
    [[nodiscard]] inline static Delegate<FunctionType>
    CreateSP(typename std::type_identity<FunctionType>::type inFunction, VarTypes &&...vars)
    {
        Delegate<FunctionType> Result;
        new (Result) SPMethodDelegateInstance<FunctionType>(inFunction);
        return Result;
    }

public:
    template <typename... VarTypes>
    inline void BindStatic(typename StaticDelegateInstance<FunctionType>::FunctionPtrType inFunc,
                           VarTypes &&...args)
    {
        // new (*this) StaticDelegateInstance<FunctionType, std::decay_t<VarTypes>...>(
        //     inFunc, std::forward<VarTypes>(vars)...);
    }

    template <typename FunctorType, typename... VarTypes>
    void BindLambda(FunctorType &&functor, VarTypes &&...vars)
    {
        // new (*this) FunctorDelegateInstance<FunctionType,
        // std::remove_reference_t<FunctionType>,
        //                                     std::decay_t<VarTypes>...>(
        //     std::forward(functor), std::forward<VarTypes>(vars)...);
    }

    template <typename Class, typename... VarTypes>
    void BindRaw(
        const Class *instance,
        typename MemberFunctionPtrType<true, Class, RetType(ParamTypes...)>::FunctionPtrType inFunc,
        VarTypes &&...vars)
    {
        // new (*this) RawMethodDelegateInstance<true, Class, FunctionType,
        // std::decay_t<VarTypes>...>(
        //     instance, inFunc, std::forward<VarTypes>(vars)...);
    }

    template <typename Class, typename... VarTypes>
    void BindRaw(Class *instance,
                 typename MemberFunctionPtrType<false, Class,
                                                RetType(ParamTypes...)>::FunctionPtrType inFunc,
                 VarTypes &&...vars)
    {
        // static_assert(!std::is_const_v<Class>,
        //               "Binding const instance to non-const member function.");
        // new (*this)
        //     RawMethodDelegateInstance<false, Class, FunctionType, std::decay_t<VarTypes>...>(
        //         instance, inFunc, std::forward<VarTypes>(vars)...);
    }

    template <typename Class, typename... VarTypes>
    void BindSP(
        const std::shared_ptr<Class> &instance,
        typename MemberFunctionPtrType<true, Class, RetType(ParamTypes...)>::FunctionPtrType inFunc,
        VarTypes &&...vars)
    {
        // new (*this) spmethoddelegateinstance<true, class, functiontype,
        // std::decay_t<vartypes>...>(
        //     instance, infunc, std::forward<vartypes>(vars)...);
    }

    template <typename Class, typename... VarTypes>
    void BindSP(const std::shared_ptr<Class> &instance,
                typename MemberFunctionPtrType<false, Class,
                                               RetType(ParamTypes...)>::FunctionPtrType inFunc,
                VarTypes &&...vars)
    {
        // static_assert(!std::is_const_v<Class>,
        //               "Binding const instance to non-const member function.");
        // new (*this) SPMethodDelegateInstance<false, Class, FunctionType,
        // std::decay_t<VarTypes>...>(
        //     instance, inFunc, std::forward<VarTypes>(vars)...);
    }

    RetType operator()(ParamTypes... params) const
    {
        return Invoke(params...);
    }

    RetType Invoke(ParamTypes... params) const
    {
        DelegateInstanceBaseType *delegateInstane =
            (DelegateInstanceBaseType *)GetAllocatedInstance();
        assert(delegateInstane != nullptr);
        return delegateInstane->Invoke(params...);
    }
};

template <typename... ParamTypes>
class MulticastDelegate : public MulticastDelegateBase
{
public:
    using DelegateType = Delegate<void(ParamTypes...)>;
    using BaseType = MulticastDelegateBase;
    using DelegateInstanceBaseTypes = DelegateInstanceBase<void(ParamTypes...)>;

public:
    void Add(DelegateType &inDelegate)
    {
    }

    void Add(DelegateType &&inDelegate)
    {
    }

    void Remove()
    {
    }

    void operator()(ParamTypes... params) const
    {
    }

    MulticastDelegate &operator=(const MulticastDelegate &other)
    {
        if (&other != this) {}
        return *this;
    }
};
