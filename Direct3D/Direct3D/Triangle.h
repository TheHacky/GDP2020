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
	void createMesh() override;
};

