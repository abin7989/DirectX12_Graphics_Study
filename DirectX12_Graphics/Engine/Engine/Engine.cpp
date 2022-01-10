#include "pch.h"
#include "Engine.h"



void Engine::init(const WindowInfo& _info)
{
	window = _info;
	Resize_window(window.width, window.height);

	viewprot = { 0,0,
		static_cast<FLOAT>(_info.width),static_cast<FLOAT>(_info.height),0.0f,1.0f };

	scissorRect = CD3DX12_RECT(0, 0, _info.width, _info.height);

	device = make_shared<Device>();
	cmdQueue = make_shared<CommandQueue>();
	swapChain = make_shared<SwapChain>();
	rootSignature = make_shared<RootSignature>();
	device->Init();
	cmdQueue->Init(device->GetDevice(), swapChain);
	swapChain->Init(_info, device->GetDevice(),device->GetDXGI(), cmdQueue->GetCmdQueue());
	rootSignature->Init(device->GetDevice());
}

void Engine::Render()
{
	RenderBegin();


	RenderEnd();
}

void Engine::RenderBegin()
{
	cmdQueue->RenderBegin(&viewprot, &scissorRect);
}

void Engine::RenderEnd()
{
	cmdQueue->RenderEnd();
}

void Engine::Resize_window(int32 _width, int32 _height)
{
	window.width = _width;
	window.height = _height;
	RECT rect = { 0,0,window.width ,window.height};
	::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
	::SetWindowPos(window.hwnd, 0, 100, 100, _width, _height, 0);
}
