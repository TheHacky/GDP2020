#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

class AMesh
{
public:
	bool init(ID3D11Device*);
	void update(FLOAT);
	void render(ID3D11DeviceContext*);
	virtual void deInit();

	UINT getIndexCount() { return _indexCount; }

protected:
	virtual bool createVertexBuffer(ID3D11Device*) = 0;
	virtual bool createIndexBuffer(ID3D11Device*) = 0;

	// mesh variables
	ID3D11Buffer*	_pVertexBuffer = nullptr;
	ID3D11Buffer*	_pIndexBuffer = nullptr;
	UINT			_vertexCount = 0;
	UINT			_indexCount = 0;
	UINT			_vertexStride = 0;
};