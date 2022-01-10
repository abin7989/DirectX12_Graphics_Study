#pragma once

class SwapChain;
class DescriptorHeap;

class CommandQueue
{
public:
	~CommandQueue();

	void Init(ComPtr<ID3D12Device> _device, shared_ptr<SwapChain> _swapChain);
	void WaitSync();

	void RenderBegin(const D3D12_VIEWPORT* _vp, const D3D12_RECT* _rect);
	void RenderEnd();

	ComPtr<ID3D12CommandQueue>			 GetCmdQueue()	 { return cmdQueue; }
	ComPtr<ID3D12GraphicsCommandList>	 GetCmdList()	 { return cmdList; }

private:
	// CommandQueue : DX12에 등장
	// 외주를 요청할 때, 하나씩 요청하면 비효율적
	// [외주 목록]에 일감을 차곡차곡 기록했다가 한 방에 요청하는 것
	ComPtr<ID3D12CommandQueue>			cmdQueue;
	ComPtr<ID3D12CommandAllocator>		cmdAlloc;
	ComPtr<ID3D12GraphicsCommandList>	cmdList;

	// Fence : 울타리(?)
	// CPU / GPU 동기화를 위한 간단한 도구
	ComPtr<ID3D12Fence>					fence;
	uint32								fenceValue = 0;
	HANDLE								fenceEvent = INVALID_HANDLE_VALUE;

	shared_ptr<SwapChain>				swapChain;
	shared_ptr<DescriptorHeap>			descHeap;
};

