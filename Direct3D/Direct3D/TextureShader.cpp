#include "TextureShader.h"
#include "Utils.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

TextureShader::TextureShader(char* textureFilename) : _textureFilename(textureFilename), AShader(TEXT("TextureVertexShader.hlsl"), TEXT("TexturePixelShader.hlsl"))
{
}

bool TextureShader::init(ID3D11Device * pDevice)
{
	if (!AShader::init(pDevice)) return false;

	if (!initMatrixBuffer(pDevice)) return false;

	if (!initMainTexture(pDevice)) return false;

	return true;
}

bool TextureShader::initInputLayout(ID3D11Device * pDevice, ID3DBlob * pBlob)
{
	D3D11_INPUT_ELEMENT_DESC elements[2] = {};

	// Position
	elements[0].SemanticName = "POSITION";
	elements[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;

	// UV
	elements[1].SemanticName = "TEXCOORD";
	elements[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	elements[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

	HRESULT hr = pDevice->CreateInputLayout(elements, 2, pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &_pInputLayout);
	if (FAILED(hr))
		return false;

	return true;
}

bool TextureShader::initMatrixBuffer(ID3D11Device * pDevice)
{
	// define buffer
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.ByteWidth = sizeof(XMFLOAT4X4);
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;

	// create buffer
	HRESULT hr = pDevice->CreateBuffer(&bufferDesc, nullptr, &_pMatrixBuffer);
	if (FAILED(hr)) return false;

	return true;
}

bool TextureShader::initMainTexture(ID3D11Device * pDevice)
{
#pragma region Main Texture
	int width;
	int height;
	int channelCount;
	BYTE* pixels = stbi_load(_textureFilename, &width, &height, &channelCount, 4);
	if (pixels == nullptr || width == 0 || height == 0) return false;

	D3D11_TEXTURE2D_DESC texture2DDesc = {};
	texture2DDesc.ArraySize = 1;
	texture2DDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	texture2DDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	texture2DDesc.Width = width;
	texture2DDesc.Height = height;
	texture2DDesc.MipLevels = 1;
	texture2DDesc.SampleDesc.Count = 1;

	D3D11_SUBRESOURCE_DATA data = {};
	data.pSysMem = pixels;
	data.SysMemPitch = width * 4; // one row with 4 byte per pixel

	ID3D11Texture2D* pTexture2D = nullptr;
	HRESULT hr = pDevice->CreateTexture2D(&texture2DDesc, &data, &pTexture2D);
	if (FAILED(hr)) return false;

	hr = pDevice->CreateShaderResourceView(pTexture2D, nullptr, &_pMainTexture);
	if (FAILED(hr)) return false;

	safeRelease<ID3D11Texture2D>(pTexture2D);
#pragma endregion

#pragma region Main Sampler State
	// http://www.3dgep.com/texturing-lighting-directx-11/
	D3D11_SAMPLER_DESC mainSamplerDesc = {};
	mainSamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	mainSamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	mainSamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	mainSamplerDesc.BorderColor[0] = 1.0f;
	mainSamplerDesc.BorderColor[1] = 0.0f;
	mainSamplerDesc.BorderColor[2] = 1.0f;
	mainSamplerDesc.BorderColor[3] = 1.0f;
	mainSamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	mainSamplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	mainSamplerDesc.MinLOD = 0.0f;
	mainSamplerDesc.MaxLOD = FLT_MAX;
	mainSamplerDesc.MipLODBias = 0.0f;

	hr = pDevice->CreateSamplerState(&mainSamplerDesc, &_pMainSampler);
	if (FAILED(hr)) return false;
#pragma endregion

	return true;
}

void TextureShader::setShaderParameters(ID3D11DeviceContext * pDeviceContext)
{
#pragma region Matrix Buffer
	// build wvp matrix
	XMMATRIX worldMatrix = XMLoadFloat4x4(&_worldMatrix);
	XMMATRIX viewMatrix = XMLoadFloat4x4(&_viewMatrix);
	XMMATRIX projectionMatrix = XMLoadFloat4x4(&_projectionMatrix);

	XMMATRIX wvpMatrix = XMMatrixTranspose(worldMatrix * viewMatrix * projectionMatrix);

	// map matrix buffer
	D3D11_MAPPED_SUBRESOURCE data = {};
	HRESULT hr = pDeviceContext->Map(_pMatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
	if (FAILED(hr)) return;

	XMStoreFloat4x4(reinterpret_cast<XMFLOAT4X4*>(data.pData), wvpMatrix);

	// unmap buffer
	pDeviceContext->Unmap(_pMatrixBuffer, 0);

	// set buffer
	pDeviceContext->VSSetConstantBuffers(0, 1, &_pMatrixBuffer);
#pragma endregion

#pragma region Main Texture
	pDeviceContext->PSSetShaderResources(0, 1, &_pMainTexture);
	pDeviceContext->PSSetSamplers(0, 1, &_pMainSampler);
#pragma endregion
}
