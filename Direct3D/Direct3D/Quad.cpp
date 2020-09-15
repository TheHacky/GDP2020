#include "Quad.h"
#include "Vertex.h"

Quad::Quad()
{
}

bool Quad::createVertexBuffer(ID3D11Device *pDevice)
{
	Vertex vertices[4] = 
	{
		Vertex(-0.5f, 0.5f, 0.0f), // left-top
		Vertex(0.5f, 0.5f, 0.0f), // right-top
		Vertex(0.5f, -0.5f, 0.0f), // right-bottom
		Vertex(-0.5f, -0.5f, 0.0f), // left-bottom
	};

	return true;
}

bool Quad::createIndexBuffer(ID3D11Device *pDevice)
{
	UINT indices[6] =
	{
		0, 1, 2,
		0, 2, 3
	};

	return true;
}
