#include "GfxSystem.h"
#include "Utils.h"

#include <random>

using namespace std;

bool GfxSystem::init(UINT screenWidth, UINT screenHeight, HWND hWnd)
{
	_pD3D = new Direct3D();
	if (!_pD3D->init(screenWidth, screenHeight, false, hWnd)) return false;

	return true;
}

void GfxSystem::updateFrame(float dt)
{
}

void GfxSystem::renderFrame()
{
	// prepare scene

	// render stuff

	// present scene
}

void GfxSystem::deInit()
{
	safeDeInit<Direct3D>(_pD3D);
}