#pragma once

#include "Device.h"
#include "CommandQueue.h"
#include "ConstantBuffer.h"
#include "SwapChain.h"
#include "RootSignature.h"
#include "TableDescriptorHeap.h"
#include "../Resource/Mesh.h"
#include "../Resource/Shader.h"
class Engine
{
public:
	void init(const WindowInfo& _window);
	void Render();

public:
	shared_ptr<Device>			GetDevice()		 	 { return device; }
	shared_ptr<CommandQueue>	GetCmdQueue()		 { return cmdQueue; }
	shared_ptr<SwapChain>		GetSwapChain()		 { return swapChain; }
	shared_ptr<RootSignature>	GetRootSignature()	 { return rootSignature; }
	shared_ptr<ConstantBuffer>  GetConstantBuffer()  { return cb; }
	shared_ptr<TableDescriptorHeap> GetTableDescHeap() { return tableDescHeap; }

public:
	void RenderBegin();
	void RenderEnd();

	void Resize_window(int32 _width, int32 _height);
private:
	WindowInfo		window;
	D3D12_VIEWPORT  viewprot = {};
	D3D12_RECT		scissorRect = {};

	shared_ptr<Device>				 device;
	shared_ptr<CommandQueue>		 cmdQueue;
	shared_ptr<SwapChain>	 		 swapChain;
	shared_ptr<RootSignature>		 rootSignature;
	shared_ptr<ConstantBuffer>		 cb;
	shared_ptr<TableDescriptorHeap>  tableDescHeap;
};

