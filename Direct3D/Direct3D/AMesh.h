#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include "Vertex.h"

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
	bool initVertexBuffer(ID3D11Device*);
	bool initIndexBuffer(ID3D11Device*);
	virtual void createMesh() = 0;

	// mesh variables
	ID3D11Buffer*	_pVertexBuffer = nullptr;
	ID3D11Buffer*	_pIndexBuffer = nullptr;
	Vertex*			_pVertices = nullptr;
	UINT*			_pIndices = nullptr;
	UINT			_vertexCount = 0;
	UINT			_indexCount = 0;
	UINT			_vertexStride = 0;

	// world matrix
	XMFLOAT4X4		_worldMatrix = {};
};