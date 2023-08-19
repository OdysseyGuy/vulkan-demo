#pragma once

#include <stdint.h>

class D3D12Adapter;

class D3D12Device
{
public:
    D3D12Device(D3D12Adapter *adapter);

    void registerGPUWork(uint32_t numPrimitives = 0, uint32_t numVertices = 0);
    void registerGPUDisptach();
};
