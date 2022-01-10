#pragma once

//객체 생성 등
class Device
{
public:
	void Init();
	ComPtr<IDXGIFactory> GetDXGI() { return dxgi; }
	ComPtr<ID3D12Device> GetDevice() { return device; }
private:

	//COM(Component Object Model)
	// DX의 프로그래밍 언어 독립성과 하위 호환성을 가능하게 하는 기술
	// COM 객체(COM 인터페이스)를 사용, 세부사항은 숨겨져있다.
	// ComPtr 일종의 스마트 포인터.
	
	ComPtr<ID3D12Debug>			debugController;
	ComPtr<IDXGIFactory>		dxgi;				//화명 관련 기능들
	ComPtr<ID3D12Device>		device;				//각종 객체 생성


};

