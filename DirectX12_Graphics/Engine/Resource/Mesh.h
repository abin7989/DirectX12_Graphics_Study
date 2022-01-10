#pragma once

// [����Ƽ¯]�� ���� �������� �̷���� ��ü
class Mesh
{
public:
	void Init(vector<Vertex>& _vec);
	void Render();

private:
	ComPtr<ID3D12Resource>		vertexBuffer;
	D3D12_VERTEX_BUFFER_VIEW	vertexBufferView = {};
	uint32 vertexCount = 0;
};

