#include "Triangle.h"
#include "Vertex.h"

Triangle::Triangle()
{
	_vertexStride = sizeof(Vertex);
	_vertexCount = 3;
	_indexCount = 3;
}

void Triangle::createMesh()
{
	float halfHeight = (FLOAT)sqrt(0.75) * 0.5f;
	_pVertices = new Vertex[_vertexCount]
	{
		Vertex(0.0f, halfHeight, 0.0f, 1.0f, 0.0f, 0.0f), // top
		Vertex(0.5f, -halfHeight, 0.0f, 0.0f, 1.0f, 0.0f), // right-bottom
		Vertex(-0.5f, -halfHeight, 0.0f, 0.0f, 0.0f, 1.0f), // left-bottom
	};

	_pIndices = new UINT[_indexCount]
	{
		0, 1, 2,
		// 1, 2, 0
		// 2, 0, 1
	};
}
