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
	XMFLOAT3 getPosition() { return _position; }

private:
	XMFLOAT4X4	_viewMatrix;
	XMFLOAT4X4	_projectionMatrix;

	XMFLOAT3 _position = { 0.0f, 0.0f, 0.0f };
};

