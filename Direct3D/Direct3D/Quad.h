#pragma once
#include "AMesh.h"
class Quad :
	public AMesh
{
public:
	Quad();

protected:
	bool createVertexBuffer(ID3D11Device*);
	bool createIndexBuffer(ID3D11Device*);
};

