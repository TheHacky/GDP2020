#pragma once
#include "AShader.h"
class TextureShader :
	public AShader
{
public:
	TextureShader(char* textureFilename);
	
	bool init(ID3D11Device*);

protected:
	bool initInputLayout(ID3D11Device*, ID3DBlob*);
	bool initMatrixBuffer(ID3D11Device*);
	bool initMainTexture(ID3D11Device*);
	void setShaderParameters(ID3D11DeviceContext*);

	ID3D11Buffer*		_pMatrixBuffer = nullptr;

	char*						_textureFilename = "";
	ID3D11ShaderResourceView*	_pMainTexture = nullptr;
	ID3D11SamplerState*			_pMainSampler = nullptr;
};

