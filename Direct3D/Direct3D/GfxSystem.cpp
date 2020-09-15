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
	static default_random_engine e = {};
	static uniform_real_distribution<float> d(0.0f, 1.0f);

	// prepare scene
	//_pD3D->beginScene(0.0f, 0.0f, 0.0f);
	_pD3D->beginScene(d(e), d(e), d(e));

	// render stuff


	// present scene
	_pD3D->endScene();
}

void GfxSystem::deInit()
{
	safeDeInit<Direct3D>(_pD3D);
}