#include "AMesh.h"
#include "Utils.h"

bool AMesh::init(ID3D11Device* pDevice)
{
	createMesh();
	if (!initVertexBuffer(pDevice) || !initIndexBuffer(pDevice)) return false;

	return true;
}

void AMesh::update(FLOAT dt)
{
	//static float scaleY = 1.0f;
	//static float dir = 1.0f;
	//static float rotZ = 0.0f;
	//static float rotZ2 = 0.0f;
	//scaleY += dt * dir * 0.25f;
	////if (scaleY > 3.0f) scaleY = -3.0f;
	//if (scaleY > 1.0f || scaleY < 0.0f)
	//{
	//	dir *= -1.0f;
	//	scaleY = scaleY > 1.0f ? 1.0f : scaleY < 0.0f ? 0.0f : scaleY;
	//}
	//rotZ += dt * 0.1f;
	//rotZ2 -= dt * 0.25f;

	XMMATRIX matrix = XMMatrixScaling(1.0f, 1.0f, 1.0f) *
		XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f) *
		XMMatrixTranslation(_position.x, _position.y, _position.z);

	//XMMATRIX matrix = XMMatrixScaling(1.0f, scaleY, 1.0f) *
	//	XMMatrixRotationRollPitchYaw(0.0f, 0.0f, rotZ) *
	//	XMMatrixTranslation(0.0f, 0.0f, 0.0f);

	//XMMATRIX matrix = XMMatrixRotationRollPitchYaw(0.0f, 0.0f, XM_PIDIV4) *
	//	XMMatrixTranslation(0.0f, 0.5f, 0.0f) *
	//	XMMatrixScaling(1.0f, scaleY, 1.0f) *
	//	XMMatrixTranslation(0.0f, -0.5f, 0.0f) *
	//	XMMatrixRotationRollPitchYaw(0.0f, 0.0f, -XM_PIDIV4);

	//XMMATRIX matrix =
	//	XMMatrixTranslation(-0.5f, 0.5f, 0.0f) *
	//	XMMatrixRotationRollPitchYaw(0.0f, 0.0f, rotZ) *
	//	XMMatrixTranslation(0.5f, -0.5f, 0.0f);

	//XMMATRIX matrix =
	//	XMMatrixRotationRollPitchYaw(0.0f, 0.0f, rotZ2) *
	//	XMMatrixTranslation(3.0f, 0.0f, 0.0f) *
	//	XMMatrixRotationRollPitchYaw(0.0f, 0.0f, rotZ);

	XMStoreFloat4x4(&_worldMatrix, matrix);
}

void AMesh::render(ID3D11DeviceContext* pDeviceContext)
{
	// IA - Input Assembler
	UINT offset = 0;
	pDeviceContext->IASetVertexBuffers(0, 1, &_pVertexBuffer, &_vertexStride, &offset);
	pDeviceContext->IASetIndexBuffer(_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void AMesh::deInit()
{
	safeRelease<ID3D11Buffer>(_pVertexBuffer);
	safeRelease<ID3D11Buffer>(_pIndexBuffer);
	
	if (_pVertices != nullptr)
	{
		delete[] _pVertices;
		_pVertices = nullptr;
	}

	if (_pIndices != nullptr)
	{
		delete[] _pIndices;
		_pIndices = nullptr;
	}
}

bool AMesh::initVertexBuffer(ID3D11Device* pDevice)
{
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.ByteWidth = _vertexStride * _vertexCount;

	D3D11_SUBRESOURCE_DATA initialData = {};
	initialData.pSysMem = _pVertices;

	HRESULT hr = pDevice->CreateBuffer(&bufferDesc, &initialData, &_pVertexBuffer);

	return SUCCEEDED(hr);
}

bool AMesh::initIndexBuffer(ID3D11Device* pDevice)
{
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.ByteWidth = sizeof(UINT) * _indexCount;

	D3D11_SUBRESOURCE_DATA initialData = {};
	initialData.pSysMem = _pIndices;

	HRESULT hr = pDevice->CreateBuffer(&bufferDesc, &initialData, &_pIndexBuffer);

	return SUCCEEDED(hr);
}
