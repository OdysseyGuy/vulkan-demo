#pragma once

#include <cstddef>
#include <cstdlib>
#include <vector>
#include <tuple>

class IDelegateInstance
{
public:
    virtual ~IDelegateInstance()
    {
    }
};

class DelegateBase
{
public:
    DelegateBase()
        : data(nullptr)
        , size(0)
    {
    }

    ~DelegateBase()
    {
        if (data != nullptr) {
            free(data);
            data = nullptr;
        }
    }

    inline IDelegateInstance *GetAllocatedInstance() const
    {
        return (IDelegateInstance *)data;
    }

private:
    friend void *operator new(size_t size, DelegateBase &base);

    void *Allocate(size_t inSize)
    {
        if (IDelegateInstance *instance = GetAllocatedInstance()) {
            instance->~IDelegateInstance();
        }
        if (inSize != size) {
            data = realloc(data, inSize);
            size = inSize;
        }
        return data;
    }

private:
    void *data;
    size_t size;
};

inline void *operator new(size_t size, DelegateBase &base)
{
    return base.Allocate(size);
}

class MulticastDelegateBase
{
protected:
    using InvocationListType = std::vector<DelegateBase>;

public:
    // inline bool IsBound() const
    // {
    // }
};
