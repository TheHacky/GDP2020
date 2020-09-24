#pragma once
#include "AMesh.h"
class Quad :
	public AMesh
{
public:
	Quad();

protected:
	void createMesh() override;
};

