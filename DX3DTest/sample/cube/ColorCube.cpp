#include "stdafx.h"
#include "ColorCube.h"

ColorCube::ColorCube()
{
	m_moveSpeed = 0.1f;
	m_targetIndex = 1;
	m_curIndex = 0;
	m_radius = 8;
}

ColorCube::~ColorCube()
{
}

void ColorCube::Init()
{
	D3DCOLOR red = D3DCOLOR_XRGB(255, 0, 0);
	D3DCOLOR green = D3DCOLOR_XRGB(0, 255, 0);
	D3DCOLOR blue = D3DCOLOR_XRGB(0, 0, 255);
	D3DCOLOR c[8] = { red, green, blue, red, green, blue, red, green };

	for (size_t i = 0; i < g_vecCubeVertex.size(); i++)
	{
		m_vertices.push_back(VERTEX_PC(g_vecCubeVertex[i], c[i]));
	}

	m_indices = g_vecCubeIndex;

	for (int i = 0; i < 6; i++)
	{
		m_point.push_back(D3DXVECTOR3(cos(D3DX_PI * i / 3.0f) * m_radius,
			0, sin(D3DX_PI * i / 3.0f) * m_radius));	
	}

	m_forward = m_point[1] - m_point[0];
	D3DXVec3Normalize(&m_forward, &m_forward);
	m_pos = m_point[0];

}

void ColorCube::Update()
{
	D3DXMATRIXA16 matR, matT;
	//D3DXVECTOR3 trans;
	D3DXVECTOR3 dist = m_point[m_targetIndex] - m_pos;
	D3DXVec3Normalize(&m_forward, &dist);
	
	if (D3DXVec3Length(&dist) < m_moveSpeed)
	{
		m_pos = m_pos + m_forward * m_moveSpeed;
	}
	else
	{
		m_pos = m_point[m_targetIndex];
		m_targetIndex++;
		m_curIndex++;
		if (m_targetIndex >= m_point.size())
		{
			m_targetIndex = 1;
			m_curIndex = 0;
		}
		m_forward = m_point[m_targetIndex] - m_point[m_curIndex];
	}
	D3DXMatrixLookAtLH(&matR, &D3DXVECTOR3(0, 0, 0), &m_forward, &D3DXVECTOR3(0, 1, 0));
	D3DXMatrixTranspose(&matR, &matR);
	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);
	m_matWorld = matR * matT;

}

void ColorCube::Render()
{
	//static float angle = 0;
	//D3DXMATRIXA16 matR, matT;
	//D3DXMatrixTranslation(&matT, 5, 2, 0);
	//angle += 0.01f;
	//D3DXMatrixRotationY(&matR, angle);
	//m_matWorld = matR * matT;
	DX::GetDevice()->SetTransform(D3DTS_WORLD, &m_matWorld);
	DX::GetDevice()->SetRenderState(D3DRS_LIGHTING, false);
	DX::GetDevice()->SetFVF(VERTEX_PC::FVF);
	DX::GetDevice()->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, m_vertices.size(),
		m_indices.size() / 3, &m_indices[0], D3DFMT_INDEX16,
		&m_vertices[0], sizeof(VERTEX_PC));
}
