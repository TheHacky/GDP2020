#pragma once
#include <DirectXMath.h>

using namespace DirectX;

// SIMD - Single Instruction Multiple Data
struct Vertex
{
	XMFLOAT3 position;
	XMFLOAT4 color;

	Vertex() : position(0.0f, 0.0f, 0.0f), color(1.0f, 1.0f, 1.0f, 1.0f) {}
	Vertex(float x, float y, float z) : position(x, y, z), color(1.0f, 1.0f, 1.0f, 1.0f) {}
	Vertex(float x, float y, float z, float r, float g, float b, float a = 1.0f)
		: position(x, y, z), color(r, g, b, a) {}
};

struct VertexTex
{
	XMFLOAT3 position;
	XMFLOAT2 uv;

	VertexTex() : position(0.0f, 0.0f, 0.0f), uv(0.0f, 0.0f) {}
	VertexTex(float x, float y, float z) : position(x, y, z), uv(0.0f, 0.0f) {}
	VertexTex(float x, float y, float z, float u, float v)
		: position(x, y, z), uv(u, v) {}
};

struct VertexTexNormal
{
	XMFLOAT3 position;
	XMFLOAT2 uv;
	XMFLOAT3 normal;

	VertexTexNormal() : position(0.0f, 0.0f, 0.0f), uv(0.0f, 0.0f), normal(0.0f, 0.0f, 0.0f) {}
	VertexTexNormal(float x, float y, float z) : position(x, y, z), uv(0.0f, 0.0f), normal(0.0f, 0.0f, 0.0f) {}
	VertexTexNormal(float x, float y, float z, float u, float v)
		: position(x, y, z), uv(u, v), normal(0.0f, 0.0f, 0.0f) {}
	VertexTexNormal(float x, float y, float z, float u, float v, float nx, float ny, float nz)
		: position(x, y, z), uv(u, v), normal(nx, ny, nz) {}
};
