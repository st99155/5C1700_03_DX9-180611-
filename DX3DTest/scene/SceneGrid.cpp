#include "stdafx.h"
#include "SceneGrid.h"
#include "sample\cube\ColorCube.h"
#include "sample\grid\Grid.h"
#include "sample\cube\Cubeman.h"
#include "sample\grid\Wall.h"
#include "sample\grid\Hexagon.h"
#include "sample\ViewportTest.h"
#include "sample\MipmapFilter.h"
#include "ObjLoader.h"

SceneGrid::SceneGrid()
{
}

SceneGrid::~SceneGrid()
{
	OnDestructIScene();
	m_pMesh->Release();
}

void SceneGrid::Init()
{
	IDisplayObject* pObj = NULL;
	//pObj = new ColorCube(); pObj->Init(); AddDisplayObject(pObj);
	//pObj = new Grid(); pObj->Init(); AddDisplayObject(pObj);
	//pObj = new Cubeman(); pObj->Init(); AddDisplayObject(pObj);
	//pObj = new Wall(); pObj->Init(); AddDisplayObject(pObj);
	//pObj = new ViewportTest(); pObj->Init(); AddDisplayObject(pObj);
	//pObj = new MipmapFilter(); pObj->Init(); AddDisplayObject(pObj);
	//pObj = new Hexagon(); pObj->Init(); AddDisplayObject(pObj);

	ObjLoader loader;
	m_pMesh = loader.LoadMesh(_T("./obj/"), _T("Map.obj"), NULL, m_mtltexList);


	D3DXVECTOR3 dir(1, -1, 1);
	D3DXVec3Normalize(&dir, &dir);
	D3DLIGHT9 light = DXUtil::InitDirectional(&dir, &WHITE);
	DX::GetDevice()->SetLight(0, &light);
	DX::GetDevice()->LightEnable(0, true);
}

void SceneGrid::Update()
{
	OnUpdateIScene();
}

void SceneGrid::Render()
{
	OnRenderIScene();

	for (int i = 0; i < m_mtltexList.size(); i++)
	{
		DX::GetDevice()->SetTexture(0, m_mtltexList[i]->pTexture);
		DX::GetDevice()->SetMaterial(&m_mtltexList[i]->material);
		m_pMesh->DrawSubset(i);
	}
}
