#pragma once
#include "stdafx.h"

class ViewportTest : public IDisplayObject
{
	LPD3DXMESH m_pMesh;
	UINT m_bufferWidth;
	UINT m_bufferHeight;

	~ViewportTest() { SAFE_RELEASE(m_pMesh); }

	void Init()
	{
		D3DXCreateTeapot(DX::GetDevice(), &m_pMesh, NULL);

		LPDIRECT3DSURFACE9 pBackBuffer = NULL;
		D3DSURFACE_DESC bufferDesc;
		DX::GetDevice()->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
		pBackBuffer->GetDesc(&bufferDesc);
		pBackBuffer->Release();

		m_bufferWidth = bufferDesc.Width;
		m_bufferHeight = bufferDesc.Height;
	}

	void Update() {}

	void Render()
	{
		DX::GetDevice()->SetRenderState(D3DRS_LIGHTING, true);

		D3DVIEWPORT9 LViewport, RViewport;
		
		//¿ÞÂÊ ºäÆ÷Æ® ·»´õ¸µ
		LViewport.X = 0;
		LViewport.Y = 0;
		LViewport.Width = m_bufferWidth / 2.0f;
		LViewport.Height = m_bufferHeight;

		DX::GetDevice()->SetViewport(&LViewport);
		DX::GetDevice()->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
		DX::GetDevice()->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
			D3DXCOLOR(0.8f, 0.3f, 0.3f, 1), 1.0f, 0);
		DX::GetDevice()->SetTransform(D3DTS_WORLD, &m_matWorld);
		DX::GetDevice()->SetMaterial(&DXUtil::BLUE_MTRL);
		m_pMesh->DrawSubset(0);

		//¿À¸¥ÂÊ ºäÆ÷Æ® ·»´õ¸µ
		RViewport.X = LViewport.Width;
		RViewport.Y = 0;
		RViewport.Width = LViewport.Width;
		RViewport.Height = LViewport.Height;

		DX::GetDevice()->SetViewport(&RViewport);
		DX::GetDevice()->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);

		D3DXMATRIXA16 matView = Camera::Get()->GetViewMatrix();
		D3DXMATRIXA16 matR;
		D3DXMatrixRotationY(&matR, D3DX_PI);
		matView = matR * matView;

		DX::GetDevice()->SetTransform(D3DTS_VIEW, &matView);


		DX::GetDevice()->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
			D3DXCOLOR(0.3f, 0.3f, 0.8f, 1), 1.0f, 0);
		DX::GetDevice()->SetTransform(D3DTS_WORLD, &m_matWorld);
		DX::GetDevice()->SetMaterial(&DXUtil::RED_MTRL);
		m_pMesh->DrawSubset(0);
	}
};