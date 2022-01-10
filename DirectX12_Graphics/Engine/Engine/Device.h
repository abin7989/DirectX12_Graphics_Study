#pragma once

//��ü ���� ��
class Device
{
public:
	void Init();
	ComPtr<IDXGIFactory> GetDXGI() { return dxgi; }
	ComPtr<ID3D12Device> GetDevice() { return device; }
private:

	//COM(Component Object Model)
	// DX�� ���α׷��� ��� �������� ���� ȣȯ���� �����ϰ� �ϴ� ���
	// COM ��ü(COM �������̽�)�� ���, ���λ����� �������ִ�.
	// ComPtr ������ ����Ʈ ������.
	
	ComPtr<ID3D12Debug>			debugController;
	ComPtr<IDXGIFactory>		dxgi;				//ȭ�� ���� ��ɵ�
	ComPtr<ID3D12Device>		device;				//���� ��ü ����


};

