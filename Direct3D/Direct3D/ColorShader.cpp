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
	return true;
}

void ColorShader::setShaderParameters(ID3D11DeviceContext* pDeviceContext)
{
	
}
