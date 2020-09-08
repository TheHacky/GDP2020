#pragma once
#include "Direct3D.h"

class GfxSystem
{
public:
	bool init(UINT, UINT, HWND);
	void updateFrame(float);
	void renderFrame();
	void deInit();

private:
	Direct3D*	_pD3D = nullptr;
};

