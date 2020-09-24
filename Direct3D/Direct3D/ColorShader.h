#pragma once
#include "AShader.h"
#include <DirectXMath.h>

using namespace DirectX;

class ColorShader : public AShader
{
public:
	ColorShader();

	bool init(ID3D11Device*);

protected:
	bool initInputLayout(ID3D11Device*, ID3DBlob*);
	bool initMatrixBuffer(ID3D11Device*);
	void setShaderParameters(ID3D11DeviceContext*);

	ID3D11Buffer*		_pMatrixBuffer = nullptr;
};

