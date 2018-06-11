#include "stdafx.h"
#include "Wall.h"

Wall::Wall()
{

}

Wall::~Wall()
{
	SAFE_RELEASE(m_pTorus);
	SAFE_RELEASE(m_pTeapot);
	SAFE_RELEASE(m_pCylinder);
}

void Wall::Init()
{
	D3DXCreateTorus(DX::GetDevice(), 1, 3, 10, 10, &m_pTorus, NULL);
	D3DXCreateTeapot(DX::GetDevice(), &m_pTeapot, NULL);
	D3DXCreateCylinder(DX::GetDevice(), 2, 2, 4, 10, 10, &m_pCylinder, NULL);
	DX::GetDevice()->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	//DX::GetDevice()->SetRenderState(D3DRS_AMBIENT, 0xffff0000);
}

void Wall::Update()
{
}

void Wall::Render()
{
	DX::GetDevice()->SetTexture(0, NULL);
	DX::GetDevice()->SetRenderState(D3DRS_LIGHTING, true);
	

	D3DXMATRIXA16 matT, matS, matR;

	D3DXMatrixTranslation(&matT, -8, 3, 5);
	DX::GetDevice()->SetTransform(D3DTS_WORLD, &matT);
	DX::GetDevice()->SetMaterial(&DXUtil::RED_MTRL);
	m_pTorus->DrawSubset(0);

	D3DXMatrixTranslation(&matT, 0, 3, 5);
	D3DXMatrixScaling(&matS, 3, 3, 3);
	DX::GetDevice()->SetTransform(D3DTS_WORLD, &(matS * matT) );
	DX::GetDevice()->SetMaterial(&DXUtil::WHITE_MTRL);
	m_pTeapot->DrawSubset(0);
	
	D3DXMatrixTranslation(&matT, 8, 3, 5);
	D3DXMatrixRotationAxis(&matR, &D3DXVECTOR3(0, 1, 1), D3DX_PI / 2);
	DX::GetDevice()->SetTransform(D3DTS_WORLD, &(matR * matT) );
	DX::GetDevice()->SetMaterial(&DXUtil::GREEN_MTRL);
	m_pCylinder->DrawSubset(0);
}
