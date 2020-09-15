#include "Triangle.h"
#include "Vertex.h"

Triangle::Triangle()
{
	_vertexStride = sizeof(Vertex);
	_vertexCount = 3;
	_indexCount = 3;
}

bool Triangle::createVertexBuffer(ID3D11Device *pDevice)
{
	float halfHeight = (FLOAT)sqrt(0.75) * 0.5f;
	Vertex vertices[3] =
	{
		Vertex(0.0f, halfHeight, 0.0f), // top
		Vertex(-0.5f, -halfHeight, 0.0f), // left-bottom
		Vertex(0.5f, -halfHeight, 0.0f), // right-bottom
	};

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.ByteWidth = _vertexStride * _vertexCount;

	D3D11_SUBRESOURCE_DATA initialData = {};
	initialData.pSysMem = vertices;

	HRESULT hr = pDevice->CreateBuffer(&bufferDesc, &initialData, &_pVertexBuffer);

	return SUCCEEDED(hr);
}

bool Triangle::createIndexBuffer(ID3D11Device *pDevice)
{
	UINT indices[3] =
	{
		0, 1, 2
		// 1, 2, 0
		// 2, 0, 1
	};

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.ByteWidth = sizeof(UINT) * _indexCount;

	D3D11_SUBRESOURCE_DATA initialData = {};
	initialData.pSysMem = indices;

	HRESULT hr = pDevice->CreateBuffer(&bufferDesc, &initialData, &_pIndexBuffer);

	return SUCCEEDED(hr);
}
