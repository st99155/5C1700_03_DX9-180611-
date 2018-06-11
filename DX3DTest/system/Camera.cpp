#include "stdafx.h"
#include "Camera.h"

Camera* Camera::instance = NULL;

Camera * Camera::Get()
{
	if (instance == NULL)
		instance = new Camera();

	return instance;
}

void Camera::Delete()
{
	SAFE_DELETE(instance);
}

Camera::Camera()
{
	m_pTarget = NULL;
	m_distance = 10;
	m_basePosY = 3;
	m_eye = D3DXVECTOR3(0, m_basePosY, -m_distance);
	m_lookat = D3DXVECTOR3(0, 0, 0);
	m_up = D3DXVECTOR3(0, 1, 0);
	m_rotX = 0;
	m_rotY = 0;
}

Camera::~Camera()
{
}

void Camera::Init()
{
	RECT rect;
	GetClientRect(DX::GetInfo().hWnd, &rect);

	D3DXMatrixLookAtLH(&m_matView, &m_eye, &m_lookat, &m_up);
	DX::GetDevice()->SetTransform(D3DTS_VIEW, &m_matView);

	D3DXMatrixPerspectiveFovLH(&m_matProj, D3DX_PI / 4.0f,
		rect.right / (float)rect.bottom, 1, 1000);
	DX::GetDevice()->SetTransform(D3DTS_PROJECTION, &m_matProj);
}

void Camera::Update()
{
	if (Mouse::Get()->ButtonPress(Mouse::LBUTTON))
	{
		m_rotY += (Mouse::Get()->GetDeltaPosition().x) / 100.0f;
		m_rotX += (Mouse::Get()->GetDeltaPosition().y) / 100.0f;

		if (m_rotX <= -D3DX_PI * 0.4f)
			m_rotX = -D3DX_PI * 0.4f;
		if (m_rotX >= D3DX_PI * 0.35f)
			m_rotX = D3DX_PI * 0.35f;
	}

	m_distance -= Mouse::Get()->GetDeltaPosition().z / 120.0f;
	m_distance = max(2, m_distance);
	m_distance = min(100, m_distance);

	m_eye = D3DXVECTOR3(0, m_basePosY, -m_distance);

	D3DXMATRIXA16 matRotX, matRotY, matRot;
	D3DXMatrixRotationX(&matRotX, m_rotX);
	D3DXMatrixRotationY(&matRotY, m_rotY);
	matRot = matRotX * matRotY;
	D3DXVec3TransformCoord(&m_eye, &m_eye, &matRot);

	if (m_pTarget)
	{
		m_lookat = *m_pTarget;
		m_eye = *m_pTarget + m_eye;
	}

	D3DXMatrixLookAtLH(&m_matView, &m_eye, &m_lookat, &m_up);
	DX::GetDevice()->SetTransform(D3DTS_VIEW, &m_matView);
	
}
