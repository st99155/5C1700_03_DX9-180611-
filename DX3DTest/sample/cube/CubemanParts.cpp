#include "stdafx.h"
#include "CubemanParts.h"

CubemanParts::CubemanParts(float rotXSpeed)
{
	m_rotXSpeed = rotXSpeed;
	m_rotXAngle = 0;
	m_isMoving = false;
}

CubemanParts::~CubemanParts()
{
}

void CubemanParts::Init()
{
	
}

void CubemanParts::Init(D3DXMATRIXA16 * pMat, vector<vector<int>>* uv)
{
	vector<D3DXVECTOR3> position;
	for (int i = 0; i < g_vecCubeVertex.size(); i++)
	{
		position.push_back(g_vecCubeVertex[i]);
	}

	if (pMat)
	{
		for (size_t i = 0; i < position.size(); i++)
		{
			D3DXVec3TransformCoord(&position[i], &position[i], pMat);
		}
	}

	if (uv == NULL)
	{
		D3DCOLOR red = D3DCOLOR_XRGB(255, 0, 0);
		D3DCOLOR green = D3DCOLOR_XRGB(0, 255, 0);
		D3DCOLOR blue = D3DCOLOR_XRGB(0, 0, 255);
		vector<D3DCOLOR> color = { red, green, blue, red, green, blue, red, green };

		SetPCVertex(m_verticesPC, position, color);
	}
	else
	{
		m_pTex = g_pTextureManager->GetTexture(ASSET_PATH + _T("Textures/cubeman/spiderman.png"));
		//SetPTVertex(m_verticesPT, position, *uv);
		SetPNTVertex(m_verticesPNT, position, *uv);
	}
}

void CubemanParts::SetMovingState(bool isMoving)
{
	if (m_isMoving == isMoving)
		return;

	m_isMoving = isMoving;

	if (m_isMoving == false)
	{
		m_rotXAngle = 0;
	}

	for (auto child : m_vecChild)
	{
		static_cast<CubemanParts*>(child)->SetMovingState(m_isMoving);
	}
}

void CubemanParts::SetPCVertex(vector<VERTEX_PC>& out, vector<D3DXVECTOR3>& position, vector<D3DCOLOR>& color)
{
	for (size_t i = 0; i < position.size(); i++)
	{
		out.push_back(VERTEX_PC(position[i], color[i]));
	}
	m_indices = g_vecCubeIndex;
}

void CubemanParts::SetPTVertex(vector<VERTEX_PT>& out, vector<D3DXVECTOR3>& position, vector<vector<int>>& uv)
{
	vector<D3DXVECTOR2> uvList;
	MakeUVList(uvList, uv);

	for (int i = 0; i < g_vecCubeIndex.size(); i++)
	{
		out.push_back(VERTEX_PT(position[g_vecCubeIndex[i]], uvList[i]));
	}
}

void CubemanParts::SetPNTVertex(vector<VERTEX_PNT>& out, vector<D3DXVECTOR3>& position, vector<vector<int>>& uv)
{
	vector<D3DXVECTOR2> uvList;
	MakeUVList(uvList, uv);
	D3DXVECTOR3 normal;

	for (int i = 0; i < g_vecCubeIndex.size(); i++)
	{
		if (i % 6 == 0)
			DXUtil::ComputeNormal(&normal, &position[g_vecCubeIndex[i]],
				&position[g_vecCubeIndex[i + 1]], &position[g_vecCubeIndex[i + 2]]);

		out.push_back(VERTEX_PNT(position[g_vecCubeIndex[i]], normal, uvList[i]));
	}
}

void CubemanParts::MakeUVList(vector<D3DXVECTOR2>& out, vector<vector<int>>& uv)
{
	for (size_t i = 0; i < uv.size(); i++)
	{
		out.push_back(D3DXVECTOR2(uv[i][0] / 64.0f, uv[i][1] / 32.0f));
		out.push_back(D3DXVECTOR2(uv[i][2] / 64.0f, uv[i][3] / 32.0f));
		out.push_back(D3DXVECTOR2(uv[i][4] / 64.0f, uv[i][5] / 32.0f));

		out.push_back(D3DXVECTOR2(uv[i][0] / 64.0f, uv[i][1] / 32.0f));
		out.push_back(D3DXVECTOR2(uv[i][4] / 64.0f, uv[i][5] / 32.0f));
		out.push_back(D3DXVECTOR2(uv[i][6] / 64.0f, uv[i][7] / 32.0f));
	}
}

void CubemanParts::Update()
{
	D3DXMATRIXA16 matT, matR;
	
	if (m_isMoving)
		m_rotXAngle += m_rotXSpeed;

	if (m_rotXAngle < -D3DX_PI / 4.0f)
	{
		m_rotXSpeed *= -1;
		m_rotXAngle = -D3DX_PI / 4.0f;
	}
	else if (m_rotXAngle > D3DX_PI / 4.0f)
	{
		m_rotXSpeed *= -1;
		m_rotXAngle = D3DX_PI / 4.0f;
	}
	D3DXMatrixRotationX(&matR, m_rotXAngle);
	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);

	m_matWorld = matR * matT;

	if (m_pParent)
		m_matWorld = m_matWorld * m_pParent->GetWorldMatrix();

	for (auto child : m_vecChild)
	{
		child->Update();
	}
}

void CubemanParts::Render()
{
	DX::GetDevice()->SetTransform(D3DTS_WORLD, &m_matWorld);
	
	if (m_verticesPC.size() > 0)
	{
		DX::GetDevice()->SetRenderState(D3DRS_LIGHTING, false);
		DX::GetDevice()->SetTexture(0, NULL);
		DX::GetDevice()->SetFVF(VERTEX_PC::FVF);
		DX::GetDevice()->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, m_verticesPC.size(),
			m_indices.size() / 3, &m_indices[0], D3DFMT_INDEX16,
			&m_verticesPC[0], sizeof(VERTEX_PC));
	}
	else if (m_verticesPT.size() > 0)
	{
		DX::GetDevice()->SetRenderState(D3DRS_LIGHTING, false);
		DX::GetDevice()->SetTexture(0, m_pTex);
		DX::GetDevice()->SetFVF(VERTEX_PT::FVF);
		DX::GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_verticesPT.size() / 3,
			&m_verticesPT[0], sizeof(VERTEX_PT));
	}
	else if (m_verticesPNT.size() > 0)
	{
		DX::GetDevice()->SetMaterial(&DXUtil::WHITE_MTRL);
		DX::GetDevice()->SetRenderState(D3DRS_LIGHTING, true);
		DX::GetDevice()->SetTexture(0, m_pTex);
		DX::GetDevice()->SetFVF(VERTEX_PNT::FVF);
		DX::GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_verticesPNT.size() / 3,
			&m_verticesPNT[0], sizeof(VERTEX_PNT));
	}

	for (auto child : m_vecChild)
	{
		child->Render();
	}
}


