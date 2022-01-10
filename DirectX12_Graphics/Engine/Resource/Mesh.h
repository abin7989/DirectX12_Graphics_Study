#pragma once

// [유니티짱]과 같이 정점으로 이루어진 물체
class Mesh
{
public:
	void Init(vector<Vertex>& _vec);
	void Render();
	void SetTransform(const Transform& _t) { transform = _t; }

private:
	ComPtr<ID3D12Resource>		vertexBuffer;
	D3D12_VERTEX_BUFFER_VIEW	vertexBufferView = {};
	uint32 vertexCount = 0;

	Transform transform = {};
};

