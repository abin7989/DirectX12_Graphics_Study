#include "pch.h"
#include "Shader.h"
#include "../Engine/Engine.h"

void Shader::Init(const wstring& _path)
{
	CreateVertexShader(_path, "VS_Main", "vs_5_0");
	CreatePixelShader(_path, "PS_Main", "ps_5_0");

	D3D12_INPUT_ELEMENT_DESC desc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
	};

	pipelineDesc.InputLayout = { desc, _countof(desc) };
	pipelineDesc.pRootSignature = ROOT_SIGNATURE.Get();

	pipelineDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	pipelineDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	pipelineDesc.DepthStencilState.DepthEnable = FALSE;
	pipelineDesc.DepthStencilState.StencilEnable = FALSE;
	pipelineDesc.SampleMask = UINT_MAX;
	pipelineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	pipelineDesc.NumRenderTargets = 1;
	pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	pipelineDesc.SampleDesc.Count = 1;

	DEVICE->CreateGraphicsPipelineState(&pipelineDesc, IID_PPV_ARGS(&pipelineState));
}

void Shader::Update()
{
	CMD_LIST->SetPipelineState(pipelineState.Get());
}

void Shader::CreateShader(const wstring& _path, const string& _name, const string& _version, ComPtr<ID3DBlob>& _blob, D3D12_SHADER_BYTECODE& _shaderByteCode)
{
	uint32 compileFlag = 0;
#ifdef _DEBUG
	compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	if (FAILED(::D3DCompileFromFile(_path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, _name.c_str(), _version.c_str(), compileFlag, 0, &_blob, &errBlob)))
	{
		::MessageBoxA(nullptr, "Shader Create Failed !", nullptr, MB_OK);
	}

	_shaderByteCode = { _blob->GetBufferPointer(), _blob->GetBufferSize() };
}

void Shader::CreateVertexShader(const wstring& _path, const string& _name, const string& _version)
{
	CreateShader(_path, _name, _version, vsBlob, pipelineDesc.VS);
}

void Shader::CreatePixelShader(const wstring& _path, const string& _name, const string& _version)
{
	CreateShader(_path, _name, _version, psBlob, pipelineDesc.PS);
}