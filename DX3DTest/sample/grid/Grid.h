#pragma once
#include "stdafx.h"

class Grid : public IDisplayObject
{
private:
	vector<VERTEX_PC> m_vertices;

public:
	Grid();
	~Grid();

	void Init();
	void Update();
	void Render();
};