#include "Quad.h"
#include "Vertex.h"

Quad::Quad()
{
	_vertexStride = sizeof(VertexTex);
	_vertexCount = 4;
	_indexCount = 6;
}

void Quad::createMesh()
{
	_pVertices = new VertexTex[_vertexCount]
	{
		VertexTex(-0.5f,  0.5f, 0.0f, 0.0f, 0.0f), // left-top
		VertexTex( 0.5f,  0.5f, 0.0f, 1.0f, 0.0f), // right-top
		VertexTex( 0.5f, -0.5f, 0.0f, 1.0f, 1.0f), // right-bottom
		VertexTex(-0.5f, -0.5f, 0.0f, 0.0f, 1.0f), // left-bottom
	};

	_pIndices = new UINT[_indexCount]
	{
		0, 1, 2,
		0, 2, 3,
	};
}
