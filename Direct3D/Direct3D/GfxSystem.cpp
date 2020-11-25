#include "GfxSystem.h"
#include "Utils.h"

#include <random>
#include "Triangle.h"
#include "Quad.h"
#include "ColorShader.h"
#include "Cube.h"
#include "TextureShader.h"
#include "LightingShader.h"

using namespace std;

bool GfxSystem::init(UINT screenWidth, UINT screenHeight, HWND hWnd)
{
	_pD3D = new Direct3D();
	if (!_pD3D->init(screenWidth, screenHeight, false, hWnd)) return false;

	_pMesh = new Cube();
	if (!_pMesh->init(_pD3D->getDevice())) return false;

	_pMesh2 = new Quad();
	if (!_pMesh2->init(_pD3D->getDevice())) return false;
	_pMesh2->setPosition(0.5f, 0.0f, 5.0f);

	_pCamera = new Camera(screenWidth, screenHeight);
	
	_pShader = new LightingShader("stone.jpg", _pCamera);
	if (!_pShader->init(_pD3D->getDevice())) return false;

	return true;
}

void GfxSystem::updateFrame(float dt)
{
	_pCamera->update(dt);
	_pMesh->update(dt);
	_pMesh2->update(dt);
}

void GfxSystem::renderFrame()
{
	static default_random_engine e = {};
	static uniform_real_distribution<float> d(0.0f, 1.0f);

	// prepare scene
	_pD3D->beginScene(0.0f, 0.0f, 0.0f);
	//_pD3D->beginScene(d(e), d(e), d(e));

	// render stuff
	_pMesh->render(_pD3D->getDeviceContext());
	_pShader->setMatrices(_pMesh->getWorldMatrix(), _pCamera->getViewMatrix(), _pCamera->getProjectionMatrix());
	_pShader->render(_pD3D->getDeviceContext(), _pMesh->getIndexCount());

	//_pMesh2->render(_pD3D->getDeviceContext());
	//_pShader->setMatrices(_pMesh2->getWorldMatrix(), _pCamera->getViewMatrix(), _pCamera->getProjectionMatrix());
	//_pShader->render(_pD3D->getDeviceContext(), _pMesh2->getIndexCount());

	// present scene
	_pD3D->endScene();
}

void GfxSystem::deInit()
{
	if (_pCamera != nullptr)
	{
		delete _pCamera;
		_pCamera = nullptr;
	}

	safeDeInit<Direct3D>(_pD3D);
	safeDeInit<AMesh>(_pMesh);
	safeDeInit<AShader>(_pShader);
}