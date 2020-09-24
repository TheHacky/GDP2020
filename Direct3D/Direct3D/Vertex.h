#pragma once
#include <DirectXMath.h>

using namespace DirectX;

// SIMD - Single Instruction Multiple Data
struct Vertex
{
	XMFLOAT3 position;
	XMFLOAT4 color;

	Vertex() : position(0.0f, 0.0f, 0.0f), color(1.0f, 1.0f, 1.0f, 1.0f) {}
	Vertex(float x, float y, float z) : position(x, y, z) {}
	Vertex(float x, float y, float z, float r, float g, float b, float a = 1.0f)
		: position(x, y, z), color(r, g, b, a) {}
};
