#pragma once

#define g_pTextureManager TextureManager::GetInstance()

class TextureManager
{
	SINGLETON(TextureManager)
private:
	map<CString, LPDIRECT3DTEXTURE9>	m_mapTexture;
	map<CString, D3DXIMAGE_INFO>		m_mapImageInfo;

private:
	LPDIRECT3DTEXTURE9 _GetTexture(LPCTSTR filePath, OUT D3DXIMAGE_INFO* pImageInfo = NULL);
public:
	LPDIRECT3DTEXTURE9 GetTexture(LPCTSTR filePath, OUT D3DXIMAGE_INFO* pImageInfo = NULL);
	
	void Destroy();
};

