#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

class AShader
{
public:
	AShader(LPTSTR vsName, LPTSTR psName) : _vertexShaderName(vsName), _pixelShaderName(psName) {}

	virtual bool init(ID3D11Device*);
	void render(ID3D11DeviceContext*, UINT);
	void deInit();

	void setMatrices(XMFLOAT4X4 wm, XMFLOAT4X4 vm, XMFLOAT4X4 pm)
	{
		_worldMatrix = wm;
		_viewMatrix = vm;
		_projectionMatrix = pm;
	}

protected:
	bool initVertexShader(ID3D11Device*);
	bool initPixelShader(ID3D11Device*);
	virtual bool initInputLayout(ID3D11Device*, ID3DBlob*) = 0;
	virtual void setShaderParameters(ID3D11DeviceContext*) = 0;

	// shader variables
	ID3D11VertexShader*		_pVertexShader = nullptr;
	ID3D11PixelShader*		_pPixelShader = nullptr;

	// input layout
	ID3D11InputLayout*		_pInputLayout = nullptr;

	// shader names
	LPTSTR	_vertexShaderName = TEXT("");
	LPTSTR	_pixelShaderName = TEXT("");

	// matrices
	XMFLOAT4X4	_worldMatrix;
	XMFLOAT4X4	_viewMatrix;
	XMFLOAT4X4	_projectionMatrix;
};