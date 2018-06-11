#include "StdAfx.h"
#include "TextureManager.h"


TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}


LPDIRECT3DTEXTURE9 TextureManager::_GetTexture(LPCTSTR filePath, OUT D3DXIMAGE_INFO * pImageInfo)
{
	if (pImageInfo)
	{
		if (m_mapTexture.find(filePath) == m_mapTexture.end() ||
			m_mapImageInfo.find(filePath) == m_mapImageInfo.end())
		{
			SAFE_RELEASE(m_mapTexture[filePath]);

			D3DXCreateTextureFromFileEx(
				DX::GetDevice(),
				filePath,
				0,	//Width : 0 �Ǵ� D3DX_DEFAULT - ���� ������ ���
				0,	//Height : D3DX_DEFAULT_NONPOW2 - ���� ������ ���(2^n ���� ���� �ȵ�)
				1,	//MipLevels : D3DX_DEFAULT �̸� ������ �Ӹ� ü�� ����
				0,	//Usage	: D3DUSAGE_RENDERTARGET ������ Ÿ�����μ� ���
				D3DFMT_UNKNOWN,	//Format : D3DFMT_UNKNOWN �������� ���
				D3DPOOL_MANAGED,	//Pool
				D3DX_FILTER_NONE,	//Filter
				D3DX_DEFAULT,	//MipFilter
				0,	//D3DCOLOR_ARGB(10, 64, 64, 64),	//ColorKey : Ű���� �������� ����
				&m_mapImageInfo[filePath],	//pSrcInfo
				NULL,	//pPalette
				&m_mapTexture[filePath]);	//ppTexture
		}
		*pImageInfo = m_mapImageInfo[filePath];
	}
	else
	{
		if (m_mapTexture.find(filePath) == m_mapTexture.end())
		{
			if (FAILED(D3DXCreateTextureFromFile(DX::GetDevice(), filePath, &m_mapTexture[filePath])));
				//assert(false && "Loading texture is failed");
		}
	}

	return m_mapTexture[filePath];
}

LPDIRECT3DTEXTURE9 TextureManager::GetTexture(LPCTSTR filePath, OUT D3DXIMAGE_INFO* pImageInfo)
{
	if (lstrlen(filePath) == 0) return NULL;

	return _GetTexture(filePath, pImageInfo);
}


void TextureManager::Destroy()
{
	for (auto it : m_mapTexture)
	{
		SAFE_RELEASE(it.second);
	}
	m_mapTexture.clear();
	m_mapImageInfo.clear();
}
