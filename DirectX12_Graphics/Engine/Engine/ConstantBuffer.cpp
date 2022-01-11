#include "pch.h"
#include "ConstantBuffer.h"
#include "Engine.h"

ConstantBuffer::ConstantBuffer()
{
}

ConstantBuffer::~ConstantBuffer()
{
	if (cbvBuffer)
	{
		if (cbvBuffer != nullptr)
			cbvBuffer->Unmap(0, nullptr);

		cbvBuffer = nullptr;
	}
}



void ConstantBuffer::Init(uint32 _size, uint32 _count)
{
	// 상수 버퍼는 256 바이트 배수로 만들어야 한다
	// 0 256 512 768
	elementSize = (_size + 255) & ~255;
	elementCount = _count;

	CreateBuffer();
	CreateView();
}
void ConstantBuffer::CreateView()
{
	D3D12_DESCRIPTOR_HEAP_DESC cbvDesc = {};
	cbvDesc.NumDescriptors = elementCount;
	cbvDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	cbvDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	DEVICE->CreateDescriptorHeap(&cbvDesc, IID_PPV_ARGS(&cbvHeap));

	cpuHandleBegin = cbvHeap->GetCPUDescriptorHandleForHeapStart();
	handleIncrementSize = DEVICE->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	for (uint32 i = 0; i < elementCount; ++i)
	{
		D3D12_CPU_DESCRIPTOR_HANDLE cbvHandle = GetCpuHandle(i);

		D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
		cbvDesc.BufferLocation = cbvBuffer->GetGPUVirtualAddress() + static_cast<uint64>(elementSize) * i;
		cbvDesc.SizeInBytes = elementSize;   // CB size is required to be 256-byte aligned.

		DEVICE->CreateConstantBufferView(&cbvDesc, cbvHandle);
	}
}

void ConstantBuffer::CreateBuffer()
{
	uint32 bufferSize = elementSize * elementCount;
	D3D12_HEAP_PROPERTIES heapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	D3D12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);

	DEVICE->CreateCommittedResource(
		&heapProperty,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&cbvBuffer));

	cbvBuffer->Map(0, nullptr, reinterpret_cast<void**>(&mappedBuffer));
	// We do not need to unmap until we are done with the resource.  However, we must not write to
	// the resource while it is in use by the GPU (so we must use synchronization techniques).
}



void ConstantBuffer::Clear()
{
	currentIndex = 0;
}

D3D12_CPU_DESCRIPTOR_HANDLE ConstantBuffer::PushData(int32 _rootParamIndex, void* _buffer, uint32 _size)
{
	assert(currentIndex < elementSize);

	::memcpy(&mappedBuffer[currentIndex * elementSize], _buffer, _size);

	D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = GetCpuHandle(currentIndex);
	currentIndex++;

	return cpuHandle;
}

D3D12_GPU_VIRTUAL_ADDRESS ConstantBuffer::GetGpuVirtualAddress(uint32 _index)
{
	D3D12_GPU_VIRTUAL_ADDRESS objCBAddress = cbvBuffer->GetGPUVirtualAddress();
	objCBAddress += _index * elementSize;
	return objCBAddress;
}

D3D12_CPU_DESCRIPTOR_HANDLE ConstantBuffer::GetCpuHandle(uint32 _index)
{
	return CD3DX12_CPU_DESCRIPTOR_HANDLE(cpuHandleBegin, _index * handleIncrementSize);
}
