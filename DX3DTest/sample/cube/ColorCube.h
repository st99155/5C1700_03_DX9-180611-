#pragma once
#include "stdafx.h"

class ColorCube : public IDisplayObject
{
private:
	vector<VERTEX_PC> m_vertices;
	vector<WORD> m_indices;
	vector<D3DXVECTOR3> m_point;
	D3DXVECTOR3 m_forward;

	float m_moveSpeed;
	float m_radius;
	int m_targetIndex;
	int m_curIndex;
	

public:
	ColorCube();
	~ColorCube();

	void Init();
	void Update();
	void Render();
};