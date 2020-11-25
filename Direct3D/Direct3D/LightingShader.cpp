#include "LightingShader.h"
#include "Utils.h"

bool LightingShader::init(ID3D11Device* pDevice)
{
	if (!TextureShader::init(pDevice) || !initLightBuffer(pDevice))
		return false;

	return true;
}

bool LightingShader::initInputLayout(ID3D11Device* pDevice, ID3DBlob* pData)
{
	D3D11_INPUT_ELEMENT_DESC inputDesc[3] = {};
	inputDesc[0].SemanticName = "POSITION";
	inputDesc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	inputDesc[1].SemanticName = "TEXCOORD";
	inputDesc[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	inputDesc[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	inputDesc[2].SemanticName = "NORMAL";
	inputDesc[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	inputDesc[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

	HRESULT hr = pDevice->CreateInputLayout(inputDesc, 3, pData->GetBufferPointer(), pData->GetBufferSize(), &_pInputLayout);

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

bool LightingShader::initLightBuffer(ID3D11Device* pDevice)
{
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.ByteWidth = sizeof(LightBuffer);
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	HRESULT hr = pDevice->CreateBuffer(&bufferDesc, nullptr, &_pLightBuffer);

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

bool LightingShader::initMatrixBuffer(ID3D11Device* pDevice)
{
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.ByteWidth = sizeof(MatrixBuffer);
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	HRESULT hr = pDevice->CreateBuffer(&bufferDesc, nullptr, &_pMatrixBuffer);

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

void LightingShader::setShaderParameters(ID3D11DeviceContext* pDeviceContext)
{
	D3D11_MAPPED_SUBRESOURCE mappedSubresource = {};
	HRESULT hr;
	
#pragma region MatrixBuffer
	hr = pDeviceContext->Map(_pMatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource);

	if (FAILED(hr))
	{
		return;
	}

	MatrixBuffer* pMatrixBuffer = reinterpret_cast<MatrixBuffer*>(mappedSubresource.pData);
	XMMATRIX worldMatrix = XMLoadFloat4x4(&_worldMatrix);
	worldMatrix = XMMatrixTranspose(worldMatrix);
	XMStoreFloat4x4(&pMatrixBuffer->worldMatrix, worldMatrix);

	XMMATRIX vpMatrix = XMLoadFloat4x4(&_viewMatrix) * XMLoadFloat4x4(&_projectionMatrix);
	vpMatrix = XMMatrixTranspose(vpMatrix);
	XMStoreFloat4x4(&pMatrixBuffer->viewProjectionMatrix, vpMatrix);

	pMatrixBuffer->cameraWorldPosition = _pCamera->getPosition();

	pDeviceContext->Unmap(_pMatrixBuffer, 0);
	pMatrixBuffer = nullptr;

	pDeviceContext->VSSetConstantBuffers(0, 1, &_pMatrixBuffer);
#pragma endregion

#pragma region LightBuffer
	hr = pDeviceContext->Map(_pLightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource);

	if (FAILED(hr))
	{
		return;
	}

	LightBuffer* pLightBuffer = reinterpret_cast<LightBuffer*>(mappedSubresource.pData);
	pLightBuffer->lightVector = XMFLOAT3(-0.2f, -0.5f, 1.0f);
	pLightBuffer->ambientColor = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	pLightBuffer->specularColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	pLightBuffer->lightColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	pLightBuffer->lightIntensity = 0.5f;

	pDeviceContext->Unmap(_pLightBuffer, 0);
	pLightBuffer = nullptr;

	pDeviceContext->PSSetConstantBuffers(0, 1, &_pLightBuffer);
#pragma endregion

#pragma region Textures
	pDeviceContext->PSSetShaderResources(0, 1, &_pMainTexture);
	pDeviceContext->PSSetSamplers(0, 1, &_pMainSampler);
#pragma endregion
}