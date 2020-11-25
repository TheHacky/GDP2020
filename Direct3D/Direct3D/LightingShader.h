#pragma once
#include "TextureShader.h"
#include "Camera.h"

class LightingShader :
	public TextureShader
{
public:
	LightingShader(char* mainTextureName, Camera* pCamera) : TextureShader(mainTextureName), _pCamera(pCamera)
	{
		_vertexShaderName = TEXT("LightingVertexShader.hlsl");
		_pixelShaderName = TEXT("LightingPixelShader.hlsl");
	}

	bool init(ID3D11Device*);

protected:
	bool initInputLayout(ID3D11Device*, ID3DBlob*);
	bool initMatrixBuffer(ID3D11Device*); 
	bool initLightBuffer(ID3D11Device*);
	void setShaderParameters(ID3D11DeviceContext*);

	struct MatrixBuffer
	{
		XMFLOAT4X4	viewProjectionMatrix;
		XMFLOAT4X4	worldMatrix;
		XMFLOAT3	cameraWorldPosition;
		float		padding;
	};

	struct LightBuffer
	{
		XMFLOAT4	ambientColor;
		XMFLOAT4	specularColor;
		XMFLOAT4	lightColor;
		XMFLOAT3	lightVector;
		float		lightIntensity;
	};

	ID3D11Buffer*	_pLightBuffer	= nullptr;
	Camera*			_pCamera		= nullptr;
};

