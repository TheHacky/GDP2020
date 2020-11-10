#include "ColorShader.h"

ColorShader::ColorShader() : AShader(TEXT("ColorVertexShader.hlsl"), TEXT("ColorPixelShader.hlsl"))
{
}

bool ColorShader::init(ID3D11Device* pDevice)
{
	if (!AShader::init(pDevice)) return false;

	if (!initMatrixBuffer(pDevice)) return false;

	return true;
}

bool ColorShader::initInputLayout(ID3D11Device *pDevice, ID3DBlob *pBlob)
{
	D3D11_INPUT_ELEMENT_DESC elements[2] = {};

	// Position
	elements[0].SemanticName = "POSITION";
	elements[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;

	// Color
	elements[1].SemanticName = "COLOR";
	elements[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	elements[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

	HRESULT hr = pDevice->CreateInputLayout(elements, 2, pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &_pInputLayout);
	
	if (FAILED(hr))
		return false;

	return true;
}

bool ColorShader::initMatrixBuffer(ID3D11Device* pDevice)
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

void ColorShader::setShaderParameters(ID3D11DeviceContext* pDeviceContext)
{
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
}
