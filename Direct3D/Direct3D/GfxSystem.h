#pragma once
#include "Direct3D.h"
#include "AMesh.h"
#include "AShader.h"

class GfxSystem
{
public:
	bool init(UINT, UINT, HWND);
	void updateFrame(float);
	void renderFrame();
	void deInit();

private:
	Direct3D*	_pD3D = nullptr;
	AMesh*		_pMesh = nullptr;
	AMesh*		_pMesh2 = nullptr;
	AShader*	_pShader = nullptr;
};

