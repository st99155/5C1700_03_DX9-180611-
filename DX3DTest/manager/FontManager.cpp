#include "stdafx.h"
#include "FontManager.h"

FontManager::FontManager()
{
}


FontManager::~FontManager()
{
}

LPD3DXFONT FontManager::GetFont(FONT::FontType e)
{
	if (m_mapFont.find(e) == m_mapFont.end())
	{
		if (e == FONT::NORMAL)
		{
			D3DXCreateFont(DX::GetDevice(), 24, 12, FW_NORMAL, 1, false, DEFAULT_CHARSET,
				OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, _T("±Ã¼­Ã¼"), &m_mapFont[e]);
		}
		else if (e == FONT::QUEST)
		{
			AddFontResource(ASSET_PATH + _T("Fonts/umberto.ttf"));
			D3DXCreateFont(DX::GetDevice(), 24, 12, FW_NORMAL, 1, false, DEFAULT_CHARSET,
				OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, _T("umberto"), &m_mapFont[e]);
		}
	}

	return m_mapFont[e];
}

void FontManager::Destroy()
{
	for (auto it : m_mapFont)
	{
		SAFE_RELEASE(it.second);
	}
	m_mapFont.clear();
}
