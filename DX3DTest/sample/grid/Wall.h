#pragma once
#include "stdafx.h"

class Wall : public IDisplayObject
{
private:
	LPD3DXMESH m_pTeapot;
	LPD3DXMESH m_pCylinder;
	LPD3DXMESH m_pTorus;

public:
	Wall();
	~Wall();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};