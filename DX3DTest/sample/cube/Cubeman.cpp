#include "stdafx.h"
#include "Cubeman.h"
#include "CubemanParts.h"

Cubeman::Cubeman()
{
	m_pRootCube = NULL;
	m_isMoving = false;
	m_moveSpeed = 0.2f;
	m_currMoveSpeedRate = 1.0f;
	m_rotationSpeed = 0.1f;

	m_isJumping = false;
	m_jumpPower = 0.7f;
	m_gravity = 0.05f;
	m_currGravity = 0.0f;
}

Cubeman::~Cubeman()
{
}

void Cubeman::Init()
{
	Camera::Get()->SetTarget(&m_pos);

	CubemanParts* pParts;
	CubemanParts* pParts2;
	//¸öÅë
	m_pRootCube = new CubemanParts();
	CreateParts(m_pRootCube, this, D3DXVECTOR3(0, 3, 0),
		D3DXVECTOR3(1, 1, 0.5f), D3DXVECTOR3(0, 0, 0), &uvBody);
	// ¸Ó¸®
	pParts = new CubemanParts();
	CreateParts(pParts, m_pRootCube, D3DXVECTOR3(0.0f, 1.6f, 0.0f),
		D3DXVECTOR3(0.8f, 0.8f, 0.8f), D3DXVECTOR3(0, 0, 0), &uvHead);
	// ¿ÞÆÈ
	pParts = new CubemanParts(0.1f);
	CreateParts(pParts, m_pRootCube, D3DXVECTOR3(-1.5f, 1.0f, 0.0f),
		D3DXVECTOR3(0.5f, 1.0f, 0.5f), D3DXVECTOR3(0, -1.0f, 0));
	// ¿ÞÆÈ2
	pParts2 = new CubemanParts();
	CreateParts(pParts2, pParts, D3DXVECTOR3(0, -1.8f, 0),
		D3DXVECTOR3(0.7f, 0.7f, 0.7f), D3DXVECTOR3(0, 0, 0));
	// ¿À¸¥ÆÈ
	pParts = new CubemanParts(-0.1f);
	CreateParts(pParts, m_pRootCube, D3DXVECTOR3(1.5f, 1.0f, 0.0f),
		D3DXVECTOR3(0.5f, 1.0f, 0.5f), D3DXVECTOR3(0, -1.0f, 0));
	// ¿À¸¥ÆÈ2
	pParts2 = new CubemanParts();
	CreateParts(pParts2, pParts, D3DXVECTOR3(0, -1.8f, 0),
		D3DXVECTOR3(0.7f, 0.7f, 0.7f), D3DXVECTOR3(0, 0, 0));
	// ¿Þ´Ù¸®
	pParts = new CubemanParts(-0.1f);
	CreateParts(pParts, m_pRootCube, D3DXVECTOR3(-0.5f, -1.0f, 0.0f),
		D3DXVECTOR3(0.5f, 1.0f, 0.5f), D3DXVECTOR3(0, -1.0f, 0));
	// ¿À¸¥´Ù¸®
	pParts = new CubemanParts(0.1f);
	CreateParts(pParts, m_pRootCube, D3DXVECTOR3(0.5f, -1.0f, 0.0f),
		D3DXVECTOR3(0.5f, 1.0f, 0.5f), D3DXVECTOR3(0, -1.0f, 0));
}

void Cubeman::Update()
{
	UpdateMoving();
	static bool isTurnedOnLight = false;

	if (Keyboard::Get()->KeyDown('1'))
	{
		isTurnedOnLight = !isTurnedOnLight;
	}

	if (isTurnedOnLight == true)
	{
		D3DXVECTOR3 pos = m_pos;
		pos.x += m_forward.x * 0.5f;
		pos.z += m_forward.z * 0.5f;
		pos.y += 1.5f;

		D3DLIGHT9 light = DXUtil::InitSpot(&m_forward, &pos, &YELLOW);
		light.Range = 35;
		light.Phi = D3DX_PI / 8;
		light.Theta = D3DX_PI / 12;
		light.Falloff = 1.0f;
		DX::GetDevice()->SetLight(10, &light);
	}
	DX::GetDevice()->LightEnable(10, isTurnedOnLight);

	m_pRootCube->SetMovingState(m_isMoving);
	m_pRootCube->Update();
}

void Cubeman::UpdateMoving()
{
	if (Keyboard::Get()->KeyPress('W')) m_deltaPos.z = 1;
	else if (Keyboard::Get()->KeyPress('S')) m_deltaPos.z = -1;
	else m_deltaPos.z = 0;

	if (Keyboard::Get()->KeyPress('D')) m_deltaRot.y = 1;
	else if (Keyboard::Get()->KeyPress('A')) m_deltaRot.y = -1;
	else m_deltaRot.y = 0;

	if (Keyboard::Get()->KeyDown(VK_SPACE) && m_isJumping == false) m_isJumping = true;

	m_rot += m_deltaRot * m_rotationSpeed;

	D3DXMATRIXA16 matRotY;
	D3DXMatrixRotationY(&matRotY, m_rot.y);
	D3DXVec3TransformNormal(&m_forward, &D3DXVECTOR3(0, 0, 1), &matRotY);

	D3DXVECTOR3 targetPos;
	float height = 0;
	
	if (m_isJumping == true)
	{
		m_currMoveSpeedRate = 0.7f;
		targetPos = m_pos + m_forward * m_deltaPos.z * m_moveSpeed * m_currMoveSpeedRate;

		targetPos.y += m_jumpPower - m_currGravity;
		m_currGravity += m_gravity;

		if (targetPos.y <= height)
		{
			targetPos.y = height;
			m_isJumping = false;
			m_currGravity = 0;
			m_currMoveSpeedRate = 1.0f;
		}
	}
	else //m_isJumping == false
	{
		targetPos = m_pos + m_forward * m_deltaPos.z * m_moveSpeed * m_currMoveSpeedRate;
	}

	m_pos = targetPos;

	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);
	m_matWorld = matRotY * matT;

	if (D3DXVec3LengthSq(&m_deltaRot) > 0 || D3DXVec3LengthSq(&m_deltaPos) > 0)
		m_isMoving = true;
	else
		m_isMoving = false;
}

void Cubeman::Render()
{
	m_pRootCube->Render();
}

void Cubeman::CreateParts(CubemanParts *& pParts, IDisplayObject * pParent,
	D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 trans, vector<vector<int>>* uv)
{
	D3DXMATRIXA16 matS, matT, mat;
	D3DXMatrixScaling(&matS, scale.x, scale.y, scale.z);
	D3DXMatrixTranslation(&matT, trans.x, trans.y, trans.z);
	mat = matS * matT;
	pParts->Init(&mat, uv);
	pParts->SetPosition(&pos);
	pParent->AddChild(pParts);
}


