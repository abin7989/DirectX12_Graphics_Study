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
	// CommandQueue : DX12�� ����
	// ���ָ� ��û�� ��, �ϳ��� ��û�ϸ� ��ȿ����
	// [���� ���]�� �ϰ��� �������� ����ߴٰ� �� �濡 ��û�ϴ� ��
	ComPtr<ID3D12CommandQueue>			cmdQueue;
	ComPtr<ID3D12CommandAllocator>		cmdAlloc;
	ComPtr<ID3D12GraphicsCommandList>	cmdList;

	// Fence : ��Ÿ��(?)
	// CPU / GPU ����ȭ�� ���� ������ ����
	ComPtr<ID3D12Fence>					fence;
	uint32								fenceValue = 0;
	HANDLE								fenceEvent = INVALID_HANDLE_VALUE;

	shared_ptr<SwapChain>				swapChain;
	shared_ptr<DescriptorHeap>			descHeap;
};

