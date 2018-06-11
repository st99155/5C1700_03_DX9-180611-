#pragma once
#include "stdafx.h"

class CubemanParts : public IDisplayObject
{
private:
	vector<VERTEX_PC> m_verticesPC;
	vector<WORD> m_indices;
	vector<VERTEX_PT> m_verticesPT;
	LPDIRECT3DTEXTURE9 m_pTex;
	vector<VERTEX_PNT> m_verticesPNT;

	bool		m_isMoving;
	float		m_rotXAngle;
	float		m_rotXSpeed;

public:
	CubemanParts(float rotXSpeed = 0);
	~CubemanParts();

	void Init();
	void Update();
	void Render();

	void Init(D3DXMATRIXA16* pMat, vector<vector<int>>* uv = NULL);
	void SetMovingState(bool isMoving);
	void SetPCVertex(vector<VERTEX_PC> &out, vector<D3DXVECTOR3> &position, vector<D3DCOLOR> &color);
	void SetPTVertex(vector<VERTEX_PT> &out, vector<D3DXVECTOR3> &position, vector<vector<int>> &uv);
	void SetPNTVertex(vector<VERTEX_PNT> &out, vector<D3DXVECTOR3> &position, vector<vector<int>> &uv);
	void MakeUVList(vector<D3DXVECTOR2> &out, vector<vector<int>> &uv);
};