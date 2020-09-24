#include "AShader.h"
#include "Utils.h"
#include <d3dcompiler.h>

bool AShader::init(ID3D11Device* pDevice)
{
	if (!initVertexShader(pDevice) || !initPixelShader(pDevice)) return false;

	return true;
}

void AShader::render(ID3D11DeviceContext* pDeviceContext, UINT indexCount)
{
	setShaderParameters(pDeviceContext);
	pDeviceContext->IASetInputLayout(_pInputLayout);
	pDeviceContext->VSSetShader(_pVertexShader, nullptr, 0);
	pDeviceContext->PSSetShader(_pPixelShader, nullptr, 0);
	pDeviceContext->DrawIndexed(indexCount, 0, 0);
}

void AShader::deInit()
{
	safeRelease<ID3D11InputLayout>(_pInputLayout);
	safeRelease<ID3D11VertexShader>(_pVertexShader);
	safeRelease<ID3D11PixelShader>(_pPixelShader);
}

bool AShader::initVertexShader(ID3D11Device* pDevice)
{
	ID3DBlob* pCode = nullptr; // blob (binary large object)
	HRESULT hr = D3DCompileFromFile(
		_vertexShaderName, // filename of shader file
		nullptr, // shader macros (like defines in c++)
		nullptr, // like a shader library
		"main", // main function of shader (entrypoint)
		"vs_4_0", // kind of shader and shader version
#if _DEBUG
		D3DCOMPILE_DEBUG |
#endif // _DEBUG
		D3DCOMPILE_ENABLE_STRICTNESS, // optional flags
		0, // optional flags
		&pCode, // compiled shader code
		nullptr // optional blob for error messages
		);

	if (FAILED(hr))
	{
		return false;
	}

	hr = pDevice->CreateVertexShader(pCode->GetBufferPointer(), pCode->GetBufferSize(), nullptr, &_pVertexShader);

	if (FAILED(hr))
	{
		return false;
	}

	if (!initInputLayout(pDevice, pCode)) return false;

	safeRelease<ID3DBlob>(pCode);

	return true;
}

bool AShader::initPixelShader(ID3D11Device* pDevice)
{
	ID3DBlob* pCode = nullptr;
	HRESULT hr = D3DCompileFromFile(_pixelShaderName, nullptr, nullptr, "main", "ps_4_0",
#if _DEBUG
		D3DCOMPILE_DEBUG |
#endif // _DEBUG
		D3DCOMPILE_ENABLE_STRICTNESS, 0, &pCode, nullptr);

	if (FAILED(hr))
	{
		return false;
	}


	hr = pDevice->CreatePixelShader(pCode->GetBufferPointer(), pCode->GetBufferSize(), nullptr, &_pPixelShader);

	if (FAILED(hr))
	{
		return false;
	}

	safeRelease<ID3DBlob>(pCode);

	return true;
}