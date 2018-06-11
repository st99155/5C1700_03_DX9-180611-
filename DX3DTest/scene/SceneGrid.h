#pragma once
#include "stdafx.h"

class SceneGrid : public IScene
{
private:
	LPD3DXMESH m_pMesh;
	vector<MTLTEX*> m_mtltexList;
	
public:
	SceneGrid();
	~SceneGrid();

	void Init();
	void Update();
	void Render();

};