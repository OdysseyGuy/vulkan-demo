#pragma once

/*
 * https://simoncoenen.com/blog/programming/CPP_Delegates
 */

#if 0

template <typename FuncType, typename... ArgTypes>
decltype(auto) ApplyAfter(FuncType &&Func, ArgTypes &&...Args) &
{
    return ::Invoke(Func, Forward<ArgTypes>(Args)...,
                    static_cast<TTupleBase &>(*this).template Get<Indices>()...);
}

template <typename FuncType, typename... ArgTypes>
decltype(auto) ApplyAfter(FuncType &&Func, ArgTypes &&...Args) &
{
    return ::Invoke(Func, Forward<ArgTypes>(Args)...,
                    static_cast<TTupleBase &>(*this).template Get<0>(),
                    static_cast<TTupleBase &>(*this).template Get<1>());
}
template <typename FuncType, typename... ArgTypes>
decltype(auto) ApplyAfter(FuncType &&Func, ArgTypes &&...Args) const &
{
    return ::Invoke(Func, Forward<ArgTypes>(Args)...,
                    static_cast<const TTupleBase &>(*this).template Get<0>(),
                    static_cast<const TTupleBase &>(*this).template Get<1>());
}
template <typename FuncType, typename... ArgTypes>
decltype(auto) ApplyAfter(FuncType &&Func, ArgTypes &&...Args) volatile &
{
    return ::Invoke(Func, Forward<ArgTypes>(Args)...,
                    static_cast<volatile TTupleBase &>(*this).template Get<0>(),
                    static_cast<volatile TTupleBase &>(*this).template Get<1>());
}
template <typename FuncType, typename... ArgTypes>
decltype(auto) ApplyAfter(FuncType &&Func, ArgTypes &&...Args) const volatile &
{
    return ::Invoke(Func, Forward<ArgTypes>(Args)...,
                    static_cast<const volatile TTupleBase &>(*this).template Get<0>(),
                    static_cast<const volatile TTupleBase &>(*this).template Get<1>());
}
template <typename FuncType, typename... ArgTypes>
decltype(auto) ApplyAfter(FuncType &&Func, ArgTypes &&...Args) &&
{
    return ::Invoke(Func, Forward<ArgTypes>(Args)...,
                    static_cast<TTupleBase &&>(*this).template Get<0>(),
                    static_cast<TTupleBase &&>(*this).template Get<1>());
}
template <typename FuncType, typename... ArgTypes>
decltype(auto) ApplyAfter(FuncType &&Func, ArgTypes &&...Args) const &&
{
    return ::Invoke(Func, Forward<ArgTypes>(Args)...,
                    static_cast<const TTupleBase &&>(*this).template Get<0>(),
                    static_cast<const TTupleBase &&>(*this).template Get<1>());
}
template <typename FuncType, typename... ArgTypes>
decltype(auto) ApplyAfter(FuncType &&Func, ArgTypes &&...Args) volatile &&
{
    return ::Invoke(Func, Forward<ArgTypes>(Args)...,
                    static_cast<volatile TTupleBase &&>(*this).template Get<0>(),
                    static_cast<volatile TTupleBase &&>(*this).template Get<1>());
}
template <typename FuncType, typename... ArgTypes>
decltype(auto) ApplyAfter(FuncType &&Func, ArgTypes &&...Args) const volatile &&
{
    return ::Invoke(Func, Forward<ArgTypes>(Args)...,
                    static_cast<const volatile TTupleBase &&>(*this).template Get<0>(),
                    static_cast<const volatile TTupleBase &&>(*this).template Get<1>());
}

#endif

#include "DelegateBase.h"
#include "DelegateInstance.h"
#include "DelegateSignature.h"

#define DELEGATE_DECL(Name, RetType, ...) typedef Delegate<RetType(__VA_ARGS__)> Name
#define MULTICAST_DELEGATE_DECL(Name, RetType, ...)                                                \
    typedef MulticastDelegate<ReturnType(__VA_ARGS__)> Name

#define DELEGATE0(RetType, Name) DELEGATE_DECL(Name, RetType)
#define DELEGATE1(RetType, Name, Param1) DELEGATE_DECL(Name, RetType, Param1)
#define DELEGATE2(RetType, Name, Param1, Param2) DELEGATE_DECL(Name, RetType, Param1, Param2)
#define DELEGATE3(RetType, Name, Param1, Param2, Param3)                                           \
    DELEGATE_DECL(Name, RetType, Param1, Param2, Param3)
#define DELEGATE4(RetType, Name, Param1, Param2, Param3, Param4)                                   \
    DELEGATE_DECL(Name, RetType, Param1, Param2, Param3, Param4)

#define DELEGATE_MULTICAST0(Name) MULTICAST_DELEGATE_DECL(Name, RetType)
#define DELEGATE_MULTICAST1(Name, Param1)
#define DELEGATE_MULTICAST2(Name, Param1, Param2)
#define DELEGATE_MULTICAST3(Name, Param1, Param2, Param3)
#define DELEGATE_MULTICAST4(Name, Param1, Param2, Param3, Param4)

#include <vector>

DELEGATE1(void, StringDelegate, int &);

StringDelegate stringDelegate;

void goga(int &data)
{
    return;
}

void f()
{
    int dob = 0;
    stringDelegate.BindStatic(&goga);
    stringDelegate(std::ref(dob));
}
