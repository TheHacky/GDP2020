#pragma once
#include "AMesh.h"
#include <DirectXMath.h>

using namespace DirectX;

class Triangle :
	public AMesh
{
public:
	Triangle();

protected:
	bool createVertexBuffer(ID3D11Device*);
	bool createIndexBuffer(ID3D11Device*);
};

