#include "Camera.h"

Camera::Camera(UINT screenWidth, UINT screenHeight)
{
	// projection matrix
	FLOAT aspect = static_cast<FLOAT>(screenWidth) / static_cast<FLOAT>(screenHeight);
	XMMATRIX m = XMMatrixPerspectiveFovLH(XM_PI * 0.333333f, aspect, 0.3f, 10.0f);
	XMStoreFloat4x4(&_projectionMatrix, m);
}

void Camera::update(float dt)
{
	// view matrix
	XMVECTOR pos = XMVectorSet(0.0f, 0.0f, -2.0f, 1.0f);
	XMVECTOR dir = XMVectorSet(0.0f, 0.0f, 1.0f, 1.0f);
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);
	XMMATRIX m = XMMatrixLookToLH(pos, dir, up);
	XMStoreFloat4x4(&_viewMatrix, m);
}
