#pragma once
#include "stdafx.h"

class Hexagon : public IDisplayObject
{
private:
	vector<VERTEX_PC> m_vertices;
	float m_radius;

public:
	Hexagon();
	~Hexagon();

	void Init();
	void Update();
	void Render();
};