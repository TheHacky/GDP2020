#pragma once

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <d3d11.h>

class Direct3D
{
public:
	bool init(UINT screenWidth, UINT screenHeight, bool vSyncEnabled, HWND hWnd);
	void beginScene(FLOAT red, FLOAT green, FLOAT blue);
	void endScene();
	void deInit();

	ID3D11Device* getDevice() { return _pDevice; }
	ID3D11DeviceContext* getDeviceContext() { return _pDeviceContext; }
	void toogleDepthEnabled(bool activate);

private:
	ID3D11Device*				_pDevice = nullptr;
	ID3D11DeviceContext*		_pDeviceContext = nullptr;
	IDXGISwapChain*				_pSwapChain = nullptr;
	ID3D11DepthStencilView*		_pDepthStencilView = nullptr;
	ID3D11DepthStencilState*	_pDepthStencilState = nullptr;
	ID3D11DepthStencilState*	_pDepthStencilOffState = nullptr;
	ID3D11RenderTargetView*		_pRenderTargetView = nullptr;
	ID3D11RasterizerState*		_pRasterizerState = nullptr;
	bool						_vSyncEnabled = false;
};