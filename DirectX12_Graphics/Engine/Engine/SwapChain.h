#pragma once


// ��ȯ �罽
// [���� ����]
// - ���� ���� ���� �ִ� ��Ȳ�� ����
// - � �������� ��� ������� ������
// - GPU�� ������ ��� (����)
// - ����� �޾Ƽ� ȭ�鿡 �׷��ش�

// [���� �����]�� ��� ����?
// - � ����(Buffer)�� �׷��� �ǳ��޶�� ��Ź�غ���
// - Ư�� ���̸� ���� -> ó���� �ǳ��ְ� -> ������� �ش� ���̿� �޴´� OK
// - �츮 ȭ�鿡 Ư�� ����(���� �����) ������ش�

// [?]
// - �׷��� ȭ�鿡 ���� ����� ����ϴ� ���߿�, ���� ȭ�鵵 ���ָ� �ðܾ� ��
// - ���� ȭ�� ������� �̹� ȭ�� ��¿� �����
// - Ư�� ���̸� 2�� ����, �ϳ��� ���� ȭ���� �׷��ְ�, �ϳ��� ���� �ñ��...
// - Double Buffering!

// - [0] [1]
// ���� ȭ�� [1]  <-> GPU �۾��� [1] BackBuffer

class SwapChain
{
public:
	void Init(const WindowInfo& _info, ComPtr<ID3D12Device> _device, ComPtr<IDXGIFactory> _dxgi, ComPtr<ID3D12CommandQueue> _cmdQueue);
	void Present();
	void SwapIndex();

	ComPtr<IDXGISwapChain> GetSwapChain() { return swapChain; }
	ComPtr<ID3D12Resource> GetRenderTarget(int32 index) { return rtvBuffer[index]; }

	ComPtr<ID3D12Resource> GetBackRTVBuffer() { return rtvBuffer[backBufferIndex]; }

	D3D12_CPU_DESCRIPTOR_HANDLE	GetBackRTV() { return rtvHandle[backBufferIndex]; }

private:
	void CreatRTV(ComPtr<ID3D12Device> _device);
	void CreatSwapChain(const WindowInfo& _info, ComPtr<IDXGIFactory> _dxgi, ComPtr<ID3D12CommandQueue> _cmdQueue);
private:
	ComPtr<IDXGISwapChain>			swapChain;

	ComPtr<ID3D12Resource>			rtvBuffer[SWAP_CHAIN_BUFFER_COUNT];
	ComPtr<ID3D12DescriptorHeap>	rtvHeap;
	D3D12_CPU_DESCRIPTOR_HANDLE		rtvHandle[SWAP_CHAIN_BUFFER_COUNT];

	uint32							backBufferIndex = 0;
};

