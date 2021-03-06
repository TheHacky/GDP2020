#include "Cube.h"

Cube::Cube()
{
	_vertexStride = sizeof(VertexTexNormal);
	_vertexCount = 24;
	_indexCount = 36;
}

void Cube::createMesh()
{
	_pVertices = new VertexTexNormal[_vertexCount]
	{
		// front
		VertexTexNormal(-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f), // left-top
		VertexTexNormal( 0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f), // right-top
		VertexTexNormal( 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f), // right-bottom
		VertexTexNormal(-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f), // left-bottom
				 
		// back	 
		VertexTexNormal( 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f), // left-top
		VertexTexNormal(-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f), // right-top
		VertexTexNormal(-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f), // right-bottom
		VertexTexNormal( 0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f), // left-bottom
				 
		// left	 
		VertexTexNormal(-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f), // right-top
		VertexTexNormal(-0.5f,  0.5f, -0.5f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f), // left-top
		VertexTexNormal(-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f), // left-bottom
		VertexTexNormal(-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f), // right-bottom
				 
		// right
		VertexTexNormal(0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f), // right-top
		VertexTexNormal(0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f), // left-top
		VertexTexNormal(0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f), // left-bottom
		VertexTexNormal(0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f), // right-bottom
				 
		// top
		VertexTexNormal(-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f), // right-top
		VertexTexNormal( 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f), // left-top
		VertexTexNormal( 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f), // right-top
		VertexTexNormal(-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f), // left-top
				 
		// bottom
		VertexTexNormal(-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f), // left-bottom
		VertexTexNormal( 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f), // right-bottom
		VertexTexNormal( 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f), // left-bottom
		VertexTexNormal(-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f), // right-bottom
	};

	_pIndices = new UINT[_indexCount]
	{
		// front 0, 1, 2, 3
		0, 1, 2,
		0, 2, 3,
		
		// back 4, 5, 6, 7
		4, 5, 6,
		4, 6, 7,

		// left 5, 0, 3, 6
		8, 9, 10,
		8, 10, 11,

		// right 1, 4, 7, 2
		12, 13, 14, 
		12, 14, 15,

		// top 5, 4, 1, 0
		16, 17, 18,
		16, 18, 19,

		// bottom 3, 2, 7, 6
		20, 21, 22,
		20, 22, 23
	};
}
