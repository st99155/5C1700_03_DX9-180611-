#pragma once
#include "stdafx.h"

class MipmapFilter : public IDisplayObject
{
	LPDIRECT3DTEXTURE9 m_pTexMipmap;
	vector<VERTEX_PT> m_vertices;
	UINT m_vtxStrid;
	DWORD m_vtxFVF;

public :
	MipmapFilter()
	{
		m_pTexMipmap = NULL;
	}

	~MipmapFilter() {}

	void Init()
	{
		m_vtxStrid = sizeof(VERTEX_PT);
		m_vtxFVF = (VERTEX_PT::FVF);

		for (int i = 0; i < g_vecQuadIndex.size(); i++)
		{
			m_vertices.push_back(VERTEX_PT(g_vecQuadVertex[g_vecQuadIndex[i]], g_vecQuadUV[g_vecQuadIndex[i]]));
		}

		D3DXMATRIXA16 matS, matR;
		D3DXMatrixScaling(&matS, 20, 20, 0);
		D3DXMatrixRotationX(&matR, D3DX_PI / 2);
		for (auto &p : m_vertices)
			D3DXVec3TransformCoord(&p.p, &p.p, &(matS * matR));

		vector<LPDIRECT3DTEXTURE9> tex;
		tex.push_back(g_pTextureManager->GetTexture(ASSET_PATH + _T("textures/mipmap/png256.png")));
		tex.push_back(g_pTextureManager->GetTexture(ASSET_PATH + _T("textures/mipmap/png128.png")));
		tex.push_back(g_pTextureManager->GetTexture(ASSET_PATH + _T("textures/mipmap/png64.png")));
		tex.push_back(g_pTextureManager->GetTexture(ASSET_PATH + _T("textures/mipmap/png32.png")));
		tex.push_back(g_pTextureManager->GetTexture(ASSET_PATH + _T("textures/mipmap/png16.png")));

		m_pTexMipmap = g_pTextureManager->GetTexture(ASSET_PATH + _T("textures/mipmap/png512.png"));

		LPDIRECT3DSURFACE9 src = NULL;
		LPDIRECT3DSURFACE9 dest = NULL;

		for (int i = 0; i < tex.size(); i++)
		{
			tex[i]->GetSurfaceLevel(0, &src);
			m_pTexMipmap->GetSurfaceLevel(i + 1, &dest);

			D3DXLoadSurfaceFromSurface(dest, NULL, NULL, src, NULL, NULL, D3DX_DEFAULT, 0);
			
			src->Release();
			dest->Release();
		}
		//FILTER
		DX::GetDevice()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
		DX::GetDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		DX::GetDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

		//ADDRESS MODE
		DX::GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
		DX::GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);
	}

	void Update() {};

	void Render()
	{
		DX::GetDevice()->SetRenderState(D3DRS_LIGHTING, false);
		DX::GetDevice()->SetFVF(m_vtxFVF);
		DX::GetDevice()->SetTexture(0, m_pTexMipmap);
		DX::GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vertices.size() / 3,
			&m_vertices[0], m_vtxStrid);
	}

};