#include "pch.h"
#include "Mesh.h"
#include "../Engine/Engine.h"

void Mesh::Init(vector<Vertex>& _vec)
{
	vertexCount = static_cast<uint32>(_vec.size());
	uint32 bufferSize = vertexCount * sizeof(Vertex);

	D3D12_HEAP_PROPERTIES heapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	D3D12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);

	DEVICE->CreateCommittedResource(
		&heapProperty,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertexBuffer));

	// Copy the triangle data to the vertex buffer.
	void* vertexDataBuffer = nullptr;
	CD3DX12_RANGE readRange(0, 0); // We do not intend to read from this resource on the CPU.
	vertexBuffer->Map(0, &readRange, &vertexDataBuffer);
	::memcpy(vertexDataBuffer, &_vec[0], bufferSize);
	vertexBuffer->Unmap(0, nullptr);

	// Initialize the vertex buffer view.
	vertexBufferView.BufferLocation = vertexBuffer->GetGPUVirtualAddress();
	vertexBufferView.StrideInBytes = sizeof(Vertex); // 정점 1개 크기
	vertexBufferView.SizeInBytes = bufferSize; // 버퍼의 크기	
}

void Mesh::Render()
{
	CMD_LIST->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	CMD_LIST->IASetVertexBuffers(0, 1, &vertexBufferView); // Slot: (0~15)

	//1) Buffer에다가 데이터 세팅
	//2) TableDescHeap에 CBV전달
	//3) 모든 세팅이 끝나면 TableDescHeap 커밋
	{
		D3D12_CPU_DESCRIPTOR_HANDLE handle = GEngine->GetConstantBuffer()->PushData(0, &transform, sizeof(transform));
		GEngine->GetTableDescHeap()->SetCBV(handle, CBV_REGISTER::b0);
	}
	{
		D3D12_CPU_DESCRIPTOR_HANDLE handle = GEngine->GetConstantBuffer()->PushData(0, &transform, sizeof(transform));
		GEngine->GetTableDescHeap()->SetCBV(handle, CBV_REGISTER::b1);
	}

	GEngine->GetTableDescHeap()->CommitTable();

	CMD_LIST->DrawInstanced(vertexCount, 1, 0, 0);
}