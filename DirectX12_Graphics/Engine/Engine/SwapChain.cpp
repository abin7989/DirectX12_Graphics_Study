#include "pch.h"
#include "SwapChain.h"


void SwapChain::Init(const WindowInfo& _info, ComPtr<ID3D12Device> _device,ComPtr<IDXGIFactory> _dxgi, ComPtr<ID3D12CommandQueue> _cmdQueue)
{
	CreatSwapChain(_info, _dxgi, _cmdQueue);

	CreatRTV(_device);
}

void SwapChain::Present()
{
	// Present the frame.
	swapChain->Present(0, 0);
}

void SwapChain::SwapIndex()
{
	backBufferIndex = (backBufferIndex + 1) % SWAP_CHAIN_BUFFER_COUNT;
}

void SwapChain::CreatSwapChain(const WindowInfo& _info,  ComPtr<IDXGIFactory> _dxgi, ComPtr<ID3D12CommandQueue> _cmdQueue)
{
	// ������ ���� ���� ������
	swapChain.Reset();

	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc.Width = static_cast<uint32>(_info.width); // ������ �ػ� �ʺ�
	sd.BufferDesc.Height = static_cast<uint32>(_info.height); // ������ �ػ� ����
	sd.BufferDesc.RefreshRate.Numerator = 60; // ȭ�� ���� ����
	sd.BufferDesc.RefreshRate.Denominator = 1; // ȭ�� ���� ����
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // ������ ���÷��� ����
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.SampleDesc.Count = 1; // ��Ƽ ���ø� OFF
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // �ĸ� ���ۿ� �������� �� 
	sd.BufferCount = SWAP_CHAIN_BUFFER_COUNT; // ����+�ĸ� ����
	sd.OutputWindow = _info.hwnd;
	sd.Windowed = _info.windowed;
	sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // ���� �ĸ� ���� ��ü �� ���� ������ ���� ����
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	_dxgi->CreateSwapChain(_cmdQueue.Get(), &sd, &swapChain);

	for (int32 i = 0; i < SWAP_CHAIN_BUFFER_COUNT; i++)
		swapChain->GetBuffer(i, IID_PPV_ARGS(&rtvBuffer[i]));
}


void SwapChain::CreatRTV(ComPtr<ID3D12Device> _device)
{

	// Descriptor (DX12) = View (~DX11)
	// [������ ��]���� RTV ����
	// DX11�� RTV(RenderTargetView), DSV(DepthStencilView), 
	// CBV(ConstantBufferView), SRV(ShaderResourceView), UAV(UnorderedAccessView)�� ����!

	int32 rtvHeapSize = _device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	D3D12_DESCRIPTOR_HEAP_DESC rtvDesc;
	rtvDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvDesc.NumDescriptors = SWAP_CHAIN_BUFFER_COUNT;
	rtvDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	rtvDesc.NodeMask = 0;

	// ���� ������ �����ͳ��� �迭�� ����
	// RTV ��� : [ ] [ ]
	_device->CreateDescriptorHeap(&rtvDesc, IID_PPV_ARGS(&rtvHeap));

	D3D12_CPU_DESCRIPTOR_HANDLE rtvHeapBegin = rtvHeap->GetCPUDescriptorHandleForHeapStart();

	for (int i = 0; i < SWAP_CHAIN_BUFFER_COUNT; i++)
	{
		rtvHandle[i] = CD3DX12_CPU_DESCRIPTOR_HANDLE(rtvHeapBegin, i * rtvHeapSize);
		_device->CreateRenderTargetView(rtvBuffer[i].Get(), nullptr, rtvHandle[i]);
	}
}
