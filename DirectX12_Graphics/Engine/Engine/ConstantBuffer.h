#pragma once

class ConstantBuffer
{
public:
	ConstantBuffer();
	~ConstantBuffer();

	void Init(uint32 _size, uint32 _count);

	void Clear();
	void PushData(int32 _rootParamIndex, void* _buffer, uint32 _size);

	D3D12_GPU_VIRTUAL_ADDRESS GetGpuVirtualAddress(uint32 _index);

private:
	void CreateBuffer();

private:
	ComPtr<ID3D12Resource>	cbvBuffer;
	BYTE*					mappedBuffer = nullptr;
	uint32					elementSize = 0;
	uint32					elementCount = 0;

	uint32					currentIndex = 0;
};

