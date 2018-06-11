#include "stdafx.h"
#include "Hexagon.h"

Hexagon::Hexagon()
{
}

Hexagon::~Hexagon()
{
}

void Hexagon::Init()
{
	m_radius = 8;
	D3DXCOLOR color = YELLOW;

	for (int i = 0; i < 6; i++)
	{
		D3DXVECTOR3 pt(cos(D3DX_PI * i / 3.0f) * m_radius,
			0, sin(D3DX_PI * i / 3.0f) * m_radius);
		m_vertices.push_back(VERTEX_PC(pt, color));
	}
	m_vertices.push_back(VERTEX_PC(D3DXVECTOR3(m_radius, 0, 0), color));
	
}

void Hexagon::Update()
{
}

void Hexagon::Render()
{
	DX::GetDevice()->SetRenderState(D3DRS_LIGHTING, false);
	DX::GetDevice()->SetTransform(D3DTS_WORLD, &m_matWorld);
	DX::GetDevice()->SetFVF(VERTEX_PC::FVF);
	DX::GetDevice()->DrawPrimitiveUP(D3DPT_LINESTRIP, m_vertices.size() - 1,
		&m_vertices[0], sizeof(VERTEX_PC));
}
