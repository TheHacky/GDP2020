#include "AMesh.h"
#include "Utils.h"

bool AMesh::init(ID3D11Device* pDevice)
{
	if (!createVertexBuffer(pDevice) || !createIndexBuffer(pDevice)) return false;

	return true;
}

void AMesh::update(FLOAT dt)
{
	
}

void AMesh::render(ID3D11DeviceContext* pDeviceContext)
{
	UINT offset = 0;
	pDeviceContext->IASetVertexBuffers(0, 1, &_pVertexBuffer, &_vertexStride, &offset);
	pDeviceContext->IASetIndexBuffer(_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void AMesh::deInit()
{
	safeRelease<ID3D11Buffer>(_pVertexBuffer);
	safeRelease<ID3D11Buffer>(_pIndexBuffer);
}