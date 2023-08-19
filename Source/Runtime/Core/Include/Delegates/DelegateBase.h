#pragma once

#include <cstddef>
#include <cstdlib>
#include <vector>
#include <tuple>
#include <iostream>
#include <cassert>

class IDelegateInstance
{
public:
    virtual ~IDelegateInstance()
    {
    }
};

class HeapAllocator
{
public:
    explicit HeapAllocator()
        : data(nullptr)
    {
    }

    ~HeapAllocator()
    {
        if (data != nullptr) {
            free(data);
            data = nullptr;
        }
    }

    void MoveToEmpty(HeapAllocator &other)
    {
        assert(this != &other);
        if (data != nullptr) {
            free(data);
        }
        data = other.data;
        other.data = nullptr;
    }

    void ResizeAllocation(size_t size)
    {
        data = realloc(data, size);
    }

    void *GetAllocation() const
    {
        return data;
    }

private:
    void *data;
};

class DelegateBase
{
public:
    DelegateBase()
        : size(0)
    {
    }

    ~DelegateBase()
    {
        Unbind();
    }

    DelegateBase(DelegateBase &&other)
    {
        allocator.MoveToEmpty(other.allocator);
        size = other.size;
        other.size = 0;
    }

    DelegateBase &operator=(DelegateBase &&other)
    {
        Unbind();
        allocator.MoveToEmpty(other.allocator);
        size = other.size;
        other.size = 0;
        return *this;
    }

    inline void Unbind()
    {
        if (IDelegateInstance *ptr = GetAllocatedInstance()) {
            ptr->~IDelegateInstance();
            allocator.ResizeAllocation(0);
            size = 0;
        }
    }

    inline IDelegateInstance *GetAllocatedInstance() const
    {
        return (IDelegateInstance *)allocator.GetAllocation();
    }

private:
    friend void *operator new(size_t size, DelegateBase &base);

    void *Allocate(size_t inSize)
    {
        if (IDelegateInstance *instance = GetAllocatedInstance()) {
            instance->~IDelegateInstance();
        }
        if (inSize != size) {
            allocator.ResizeAllocation(inSize);
            size = inSize;
        }
        return allocator.GetAllocation();
    }

private:
    HeapAllocator allocator;
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
    void Clear()
    {
        for (DelegateBase &delegateBaseRef : invocationList) {
            delegateBaseRef.Unbind();
        }
    }

    /** Returns true if at least one function is bound to this delegate. */
    inline bool IsBound() const
    {
        for (const DelegateBase &delegate : invocationList) {
            if (delegate.GetAllocatedInstance()) {
                return true;
            }
        }
        return false;
    }

    template <typename DelegateInstanceBaseType, typename... ParamTypes>
    void Invoke(ParamTypes... params) const
    {
        bool needsCleanup = false;
        const InvocationListType &localList = GetInvocationList();

        for (int32_t i = localList.size() - 1; i >= 0; i--) {
            const DelegateBase &base = (const DelegateBase &)localList[i];
            IDelegateInstance *delegate = base.GetAllocatedInstance();
            if (delegate == nullptr ||
                ((DelegateInstanceBaseType *)delegate)->InvokeSafely(params...)) {
                needsCleanup = true;
            }
        }

        // cleanup if there are unbound delegate instances
        if (needsCleanup) {
            const_cast<MulticastDelegateBase *>(this)->CleanupInvocationList();
        }
    }

    inline void AddDelegateInstance(DelegateBase &&newDelegate)
    {
        if (newDelegate.GetAllocatedInstance()) {
            CleanupInvocationList();
            invocationList.emplace_back(std::move(newDelegate));
        }
    }

private:
    void CleanupInvocationList()
    {
        for (uint32_t i = 0; i < invocationList.size();) {
            auto &delegate = invocationList[i];

            IDelegateInstance *delegateInstance = delegate.GetAllocatedInstance();
            if (delegateInstance == nullptr) {
                invocationList.erase(invocationList.begin() + i);
            } else {
                i++;
            }
        }
    }

    inline InvocationListType &GetInvocationList()
    {
        return invocationList;
    }

    inline const InvocationListType &GetInvocationList() const
    {
        return invocationList;
    }

private:
    InvocationListType invocationList;
};
