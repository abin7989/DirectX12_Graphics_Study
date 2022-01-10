#pragma once

// [일감 기술서] 외주 인력들이 뭘 해야할지 기술
class Shader
{
public:
	void Init(const wstring& _path);
	void Update();

private:
	void CreateShader(const wstring& _path, const string& _name, const string& _version, ComPtr<ID3DBlob>& _blob, D3D12_SHADER_BYTECODE& _shaderByteCode);
	void CreateVertexShader(const wstring& _path, const string& _name, const string& _version);
	void CreatePixelShader(const wstring& _path, const string& _name, const string& _version);

private:
	ComPtr<ID3DBlob>					vsBlob;
	ComPtr<ID3DBlob>					psBlob;
	ComPtr<ID3DBlob>					errBlob;

	ComPtr<ID3D12PipelineState>			pipelineState;
	D3D12_GRAPHICS_PIPELINE_STATE_DESC  pipelineDesc = {};
};

