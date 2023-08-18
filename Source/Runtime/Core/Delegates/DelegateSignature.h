#pragma once

#include <cassert>
#include <functional>

template <typename Signature>
class Delegate;

template <typename RetType, typename... ParamTypes>
class Delegate<RetType(ParamTypes...)> : public DelegateBase
{
    using FunctionType = RetType(ParamTypes...);
    using DelegateInstanceBaseType = DelegateInstanceBase<RetType(ParamTypes...)>;

public:
    template <typename... ArgTypes>
    [[nodiscard]] inline static Delegate<FunctionType>
    CreateStatic(typename StaticDelegateInstance<FunctionType,
                                                 std::decay_t<ArgTypes>...>::FunctionPtrType func,
                 ArgTypes &&...args)
    {
        Delegate<FunctionType> Result;
        new (Result) StaticDelegateInstance<FunctionType, std::decay_t<ArgTypes>...>(
            func, std::forward<ArgTypes>(args)...);
        return Result;
    }

    template <typename FunctorType, typename... ArgTypes>
    [[nodiscard]] inline static Delegate<FunctionType> CreateLamda(FunctorType &&functor,
                                                                   ArgTypes &&...args)
    {
        Delegate<FunctionType> Result;
        // references not allowed for functors
        new (Result) FunctorDelegateInstance<FunctionType, std::remove_reference_t<FunctorType>,
                                             std::decay_t<ArgTypes>>(
            std::forward<FunctorType>(functor), std::forward<ArgTypes>(args)...);
        return Result;
    }

    template <typename Class, typename... ArgTypes>
    [[nodiscard]] inline static Delegate<FunctionType>
    CreateRaw(const Class *instance,
              typename RawMethodDelegateInstance<true, Class, FunctionType,
                                                 std::decay_t<ArgTypes>...>::FunctionPtrType func,
              ArgTypes &&...args)
    {
        Delegate<FunctionType> Result;
        new (Result)
            RawMethodDelegateInstance<true, const Class, FunctionType, std::decay_t<ArgTypes>...>(
                instance, func, std::forward<ArgTypes>(args)...);
        return Result;
    }

    template <typename Class, typename... ArgTypes>
    [[nodiscard]] inline static Delegate<FunctionType>
    CreateRaw(Class *instance,
              typename RawMethodDelegateInstance<false, Class, FunctionType,
                                                 std::decay_t<ArgTypes>...>::FunctionPtrType func,
              ArgTypes &&...args)
    {
        Delegate<FunctionType> Result;
        new (Result)
            RawMethodDelegateInstance<false, Class, FunctionType, std::decay_t<ArgTypes>...>(
                instance, func, std::forward<ArgTypes>(args)...);
        return Result;
    }

public:
    Delegate()
    {
    }

    ~Delegate()
    {
        Unbind();
    }

    Delegate(const Delegate &other)
    {
        *this = other;
    }

    Delegate &operator=(const Delegate &other)
    {
        if (&other != this) {
            DelegateInstanceBaseType *otherInstance =
                (DelegateInstanceBase *)other.GetAllocatedInstance();
            if (otherInstance != nullptr) {
                otherInstance->CreateCopy(*this);
            } else {
                Unbind();
            }
        }
        return *this;
    }

public:
    /** Bind a static function to the delegate. */
    template <typename... ArgTypes>
    inline void
    BindStatic(typename StaticDelegateInstance<FunctionType,
                                               std::decay_t<ArgTypes>...>::FunctionPtrType func,
               ArgTypes &&...args)
    {
        new (*this) StaticDelegateInstance<FunctionType, std::decay_t<ArgTypes>...>(
            func, std::forward<ArgTypes>(args)...);
    }

    /** Bind a functor (especially lambda) to the delegate. */
    template <typename FunctorType, typename... ArgTypes>
    inline void BindLambda(FunctorType &&functor, ArgTypes &&...args)
    {
        // functor references are now allowed
        new (*this) FunctorDelegateInstance<FunctionType, std::remove_reference_t<FunctorType>,
                                            std::decay_t<ArgTypes>...>(
            std::forward<FunctionType>(functor), std::forward<ArgTypes>(args)...);
    }

    /** Bind a raw member function pointer to the delegate. */
    template <typename Class, typename... ArgTypes>
    inline void
    BindRaw(const Class *instance,
            typename RawMethodDelegateInstance<true, Class, RetType(ParamTypes...),
                                               std::decay_t<ArgTypes>...>::FunctionPtrType func,
            ArgTypes &&...args)
    {
        new (*this)
            RawMethodDelegateInstance<true, const Class, FunctionType, std::decay_t<ArgTypes>...>(
                instance, func, std::forward<ArgTypes>(args)...);
    }

    /** Bind a raw member function pointer to the delegate. */
    template <typename Class, typename... ArgTypes>
    inline void
    BindRaw(Class *instance,
            typename RawMethodDelegateInstance<false, Class, RetType(ParamTypes...),
                                               std::decay_t<ArgTypes>...>::FunctionPtrType func,
            ArgTypes &&...args)
    {
        static_assert(!std::is_const_v<Class>,
                      "Binding const instance to non-const member function.");
        new (*this)
            RawMethodDelegateInstance<false, Class, FunctionType, std::decay_t<ArgTypes>...>(
                instance, func, std::forward<ArgTypes>(args)...);
    }

    template <typename Class, typename... ArgTypes>
    inline void
    BindSP(const std::shared_ptr<Class> &instance,
           typename MemberFunctionPtrType<true, Class, RetType(ParamTypes...),
                                          std::decay_t<ArgTypes>...>::FunctionPtrType func,
           ArgTypes &&...args)
    {
        new (*this)
            SPMethodDelegateInstance<true, const Class, FunctionType, std::decay_t<ArgTypes>...>(
                instance, func, std::forward<ArgTypes>(args)...);
    }

    template <typename Class, typename... ArgTypes>
    inline void
    BindSP(const std::shared_ptr<Class> &instance,
           typename MemberFunctionPtrType<false, Class, RetType(ParamTypes...),
                                          std::decay_t<ArgTypes>...>::FunctionPtrType func,
           ArgTypes &&...args)
    {
        static_assert(!std::is_const_v<Class>,
                      "Binding const instance to non-const member function.");
        new (*this) SPMethodDelegateInstance<false, Class, FunctionType, std::decay_t<ArgTypes>...>(
            instance, func, std::forward<ArgTypes>(args)...);
    }

    /** Invoke calls the underlying bound function along with the parameters passed. */
    RetType operator()(ParamTypes... params) const
    {
        DelegateInstanceBaseType *delegateInstance =
            (DelegateInstanceBaseType *)GetAllocatedInstance();
        assert(delegateInstance != nullptr);
        return delegateInstance->Invoke(params...);
    }

    bool InvokeSafely(ParamTypes... params) const
    {
        if (DelegateInstanceBaseType *delegateInstance =
                (DelegateInstanceBaseType *)GetAllocatedInstance) {
            return delegateInstance->InvokeSafely(params...);
        }
        return false;
    }
};

template <typename... ParamTypes>
class MulticastDelegate : public MulticastDelegateBase
{
public:
    using DelegateType = Delegate<void(ParamTypes...)>;
    using BaseType = MulticastDelegateBase;
    using DelegateInstanceBaseType = DelegateInstanceBase<void(ParamTypes...)>;

public:
    void Add(const DelegateType &delegate)
    {
        BaseType::AddDelegateInstance(delegate);
    }

    void Add(DelegateType &&delegate)
    {
        BaseType::AddDelegateInstance(std::move(delegate));
    }

    template <typename... ArgTypes>
    void AddStatic(typename StaticDelegateInstance<void(ParamTypes...),
                                                   std::decay_t<ArgTypes>...>::FunctionPtrType func,
                   ArgTypes &&...args)
    {
        Add(DelegateType::CreateStatic(func, std::forward<ArgTypes>(args)...));
    }

    template <typename FunctorType, typename... ArgTypes>
    void AddLamda(FunctorType &&functor, ArgTypes &&...args)
    {
        Add(DelegateType::CreateLambda(std::forward<FunctorType>(functor),
                                       std::forward<ArgTypes>(args)...));
    }

    template <typename Class, typename... ArgTypes>
    void AddRaw(const Class *instance,
                typename RawMethodDelegateInstance<true, Class, void(ParamTypes...),
                                                   std::decay_t<ArgTypes>...>::FunctionPtrType func,
                ArgTypes &&...args)
    {
        Add(DelegateType::CreateRaw(instance, func, std::forward<ArgTypes>(args)...));
    }

    template <typename Class, typename... ArgTypes>
    void AddRaw(Class *instance,
                typename RawMethodDelegateInstance<false, Class, void(ParamTypes...),
                                                   std::decay_t<ArgTypes>...>::FunctionPtrType func,
                ArgTypes &&...args)
    {
        static_assert(!std::is_const_v<Class>,
                      "Binding const instance to non-const member function.");
        Add(DelegateType::CreateRaw(instance, func, std::forward<ArgTypes>(args)...));
    }

    /** Invokes all the bound objects. */
    void operator()(ParamTypes... params) const
    {
        BaseType::template Invoke<DelegateInstanceBaseType, ParamTypes...>(params...);
    }
};
