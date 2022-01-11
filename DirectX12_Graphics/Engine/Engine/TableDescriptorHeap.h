#pragma once


class TableDescriptorHeap
{
public:
	void Init(uint32 count);

	void Clear();
	void SetCBV(D3D12_CPU_DESCRIPTOR_HANDLE _srcHandle, CBV_REGISTER _reg);
	void CommitTable();

	ComPtr<ID3D12DescriptorHeap> GetDescriptorHeap() { return descHeap; }

	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUHandle(CBV_REGISTER _reg);

private:
	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUHandle(uint32 _reg);

private:

	ComPtr<ID3D12DescriptorHeap> descHeap;
	uint64					handleSize = 0;
	uint64					groupSize = 0;
	uint64					groupCount = 0;

	uint32					currentGroupIndex = 0;
};

