#pragma once
#include <Windows.h>
#include <DirectXMath.h>

using namespace DirectX;

class Camera
{
public:
	Camera(UINT screenWidth, UINT screenHeight);

	void update(float dt);
	XMFLOAT4X4 getViewMatrix() { return _viewMatrix; }
	XMFLOAT4X4 getProjectionMatrix() { return _projectionMatrix; }

private:
	XMFLOAT4X4	_viewMatrix;
	XMFLOAT4X4	_projectionMatrix;
};

