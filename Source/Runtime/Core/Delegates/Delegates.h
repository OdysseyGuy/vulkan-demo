#pragma once

/*
 * https://simoncoenen.com/blog/programming/CPP_Delegates
 */

#include "DelegateBase.h"
#include "DelegateInstance.h"
#include "DelegateSignature.h"

#define DELEGATE_DECL(Name, RetType, ...) typedef Delegate<RetType(__VA_ARGS__)> Name
#define MULTICAST_DELEGATE_DECL(Name, ...) typedef MulticastDelegate<__VA_ARGS__> Name

#define DELEGATE0(RetType, Name) DELEGATE_DECL(Name, RetType)
#define DELEGATE1(RetType, Name, Param1) DELEGATE_DECL(Name, RetType, Param1)
#define DELEGATE2(RetType, Name, Param1, Param2) DELEGATE_DECL(Name, RetType, Param1, Param2)
#define DELEGATE3(RetType, Name, Param1, Param2, Param3)                                           \
    DELEGATE_DECL(Name, RetType, Param1, Param2, Param3)
#define DELEGATE4(RetType, Name, Param1, Param2, Param3, Param4)                                   \
    DELEGATE_DECL(Name, RetType, Param1, Param2, Param3, Param4)

#define MULTICAST_DELEGATE0(Name) MULTICAST_DELEGATE_DECL(Name)
#define MULTICAST_DELEGATE1(Name, Param1) MULTICAST_DELEGATE_DECL(Name, Param1)
#define MULTICAST_DELEGATE2(Name, Param1, Param2) MULTICAST_DELEGATE_DECL(Name, Param1, Param2)
#define MULTICAST_DELEGATE3(Name, Param1, Param2, Param3)                                          \
    MULTICAST_DELEGATE_DECL(Name, Param1, Param2, Param3)
#define MULTICAST_DELEGATE4(Name, Param1, Param2, Param3, Param4)                                  \
    MULTICAST_DELEGATE_DECL(Name, Param1, Param2, Param3, Param4)

#include <vector>

MULTICAST_DELEGATE3(ClassDeligate, int, int, int &);
ClassDeligate classDeligate;

static void GlobalSum(int a, int b, int &c)
{
    c = a + b;
}

class Calculator
{
public:
    Calculator(int inData)
        : data(inData)
    {
    }

    void sum(int a, int b, int &c) const
    {
        c = a + b + data;
    }

public:
    int data;
};

void f()
{
    const Calculator calc{5};
    classDeligate.AddRaw(&calc, &Calculator::sum);
    classDeligate.AddStatic(&GlobalSum);
    int sum = 0;
    classDeligate(3, 4, sum);
}
