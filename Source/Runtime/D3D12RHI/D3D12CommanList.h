#pragma once

#include <memory>

class D3D12CommandAllocator
{
public:
    D3D12CommandAllocator();

private:
    std::shared_ptr<ID3D12CommandAllocator> commandAllocator;
}

class D3D12CommandList
{
private:
    friend class D

    D3D12CommandList(D3D12CommandAllocator *allocator);

public:
};
