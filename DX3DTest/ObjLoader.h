#pragma once
#include "stdafx.h"

class ObjLoader
{
public:
	CString m_filepath;
	map<CString, MTLTEX*> m_mtltexList;

	ObjLoader();
	~ObjLoader();

	LPD3DXMESH LoadMesh(LPCTSTR filepath, LPCTSTR filename, D3DXMATRIXA16* pMat, vector<MTLTEX*> &vecMtltex);
	void LoadMtlLib(LPCTSTR fullpath);
};