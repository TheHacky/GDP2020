#include "Direct3D.h"
#include "Utils.h"

bool Direct3D::init(UINT screenWidth, UINT screenHeight, bool vSyncEnabled, HWND hWnd)
{
	HRESULT hr;
	_vSyncEnabled = vSyncEnabled;

#pragma region check resolution
	// create factory for getting adapter
	IDXGIFactory* pFactory = nullptr;
	hr = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&pFactory));
	if (FAILED(hr)) return false;

	// create adapter (graphic card object) for getting output
	IDXGIAdapter* pAdapter = nullptr;
	hr = pFactory->EnumAdapters(0, &pAdapter);
	if (FAILED(hr)) return false;

	DXGI_ADAPTER_DESC d;
	pAdapter->GetDesc(&d);

	// create output (monitor)
	IDXGIOutput* pOutput = nullptr;
	hr = pAdapter->EnumOutputs(0, &pOutput);
	if (FAILED(hr)) return false;

	// get element count of display modes
	UINT cnMode = 0;
	hr = pOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &cnMode, nullptr);
	if (FAILED(hr) || cnMode == 0) return false;

	// get display modes
	DXGI_MODE_DESC* pModes = new DXGI_MODE_DESC[cnMode];
	hr = pOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &cnMode, pModes);
	if (FAILED(hr)) return false;

	// check display modes with desired resolution
	UINT numerator = 0;
	UINT denominator = 0;
	for (UINT i = 0; i < cnMode; i++)
	{
		if (pModes[i].Width == screenWidth && pModes[i].Height == screenHeight)
		{
			numerator = pModes[i].RefreshRate.Numerator;
			denominator = pModes[i].RefreshRate.Denominator;
			break;
		}
	}

	// cleaning
	delete[] pModes;
	pModes = nullptr;

	pOutput->Release();
	pOutput = nullptr;

	pAdapter->Release();
	pAdapter = nullptr;

	pFactory->Release();
	pFactory = nullptr;
#pragma endregion

#pragma region create device, device context and swap chain
	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.Width = screenWidth;
	swapChainDesc.BufferDesc.Height = screenHeight;

	if (_vSyncEnabled)
	{
		swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
	}
	else
	{
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1.0f;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0.0f;
	}

	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Windowed = true;

	D3D_FEATURE_LEVEL featureLevels[1] = { D3D_FEATURE_LEVEL_10_1 };

	hr = D3D11CreateDeviceAndSwapChain(
		nullptr, // specific graphic adapter
		D3D_DRIVER_TYPE_HARDWARE, // should the renderer use the graphic card or a software renderer
		nullptr, // necessary only with D3D_DRIVER_TYPE_SOFTWARE
		0,
		featureLevels, 1, // Direct3D versions our graphic should support
		D3D11_SDK_VERSION, // Direct3D SDK version our application is compiled with
		&swapChainDesc, &_pSwapChain, &_pDevice,
		nullptr, // highest feature level from pFeatureLevels our graphic card support
		&_pDeviceContext
		);
	if (FAILED(hr))
	{
#if DEBUG
		MessageBox(nullptr, TEXT("D3D11CreateDeviceAndSwapChain failed!"), TEXT("Error"), 0);
#endif
		return false;
	}
#pragma endregion

#pragma region create depth stencil buffer
	D3D11_TEXTURE2D_DESC depthStencilTextureDesc = {};
	depthStencilTextureDesc.ArraySize = 1;
	depthStencilTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilTextureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilTextureDesc.Width = screenWidth;
	depthStencilTextureDesc.Height = screenHeight;
	depthStencilTextureDesc.MipLevels = 1;
	depthStencilTextureDesc.SampleDesc.Count = 1;

	ID3D11Texture2D* pDepthStencilTexture = nullptr;
	hr = _pDevice->CreateTexture2D(&depthStencilTextureDesc, nullptr, &pDepthStencilTexture);
	if (FAILED(hr)) return false;

	hr = _pDevice->CreateDepthStencilView(pDepthStencilTexture, nullptr, &_pDepthStencilView);
	if (FAILED(hr)) return false;

	safeRelease<ID3D11Texture2D>(pDepthStencilTexture);

	D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;

	hr = _pDevice->CreateDepthStencilState(&depthStencilDesc, &_pDepthStencilState);
	if (FAILED(hr)) return false;

	_pDeviceContext->OMSetDepthStencilState(_pDepthStencilState, 0);
#pragma endregion

#pragma region create render target view
	// get backpuffer texture
	ID3D11Texture2D* pBackpuffer = nullptr;
	hr = _pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackpuffer));
	if (FAILED(hr))
		return false;

	hr = _pDevice->CreateRenderTargetView(pBackpuffer, nullptr, &_pRenderTargetView);

	pBackpuffer->Release();
	pBackpuffer = nullptr;

	if (FAILED(hr))
		return false;

	_pDeviceContext->OMSetRenderTargets(1, &_pRenderTargetView, nullptr);
#pragma endregion

#pragma region create rasterizer state
	D3D11_RASTERIZER_DESC rasterizerDesc = {};
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_BACK;
	rasterizerDesc.AntialiasedLineEnable = true;

	hr = _pDevice->CreateRasterizerState(&rasterizerDesc, &_pRasterizerState);
	if (FAILED(hr))
		return false;

	_pDeviceContext->RSSetState(_pRasterizerState);
#pragma endregion

#pragma region set viewport
	D3D11_VIEWPORT viewport = {};
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.Width = screenWidth;
	viewport.Height = screenHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	_pDeviceContext->RSSetViewports(1, &viewport);
#pragma endregion

	return true;
}

void Direct3D::beginScene(FLOAT red, FLOAT green, FLOAT blue)
{
}

void Direct3D::endScene()
{
}

void Direct3D::deInit()
{
	safeRelease<ID3D11RasterizerState>(_pRasterizerState);
	safeRelease<ID3D11RenderTargetView>(_pRenderTargetView);
	safeRelease<ID3D11DepthStencilState>(_pDepthStencilOffState);
	safeRelease<ID3D11DepthStencilState>(_pDepthStencilState);
	safeRelease<ID3D11DepthStencilView>(_pDepthStencilView);
	safeRelease<ID3D11DeviceContext>(_pDeviceContext);
	safeRelease<ID3D11Device>(_pDevice);
	safeRelease<IDXGISwapChain>(_pSwapChain);
}

void Direct3D::toogleDepthEnabled(bool activate)
{
}