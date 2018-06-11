#pragma once
#include "stdafx.h"

class Camera
{
private:
	static Camera* instance;

	D3DXVECTOR3 m_eye;
	D3DXVECTOR3 m_lookat;
	D3DXVECTOR3 m_up;
	D3DXMATRIXA16 m_matView;
	D3DXMATRIXA16 m_matProj;
	float m_basePosY;
	float m_distance;
	float m_rotX;
	float m_rotY;
	D3DXVECTOR3* m_pTarget;

	Camera();
	~Camera();

public:
	static Camera* Get();
	static void Delete();

	void Init();
	void Update();
	void SetTarget(D3DXVECTOR3* pTarget) { m_pTarget = pTarget; }
	const D3DXVECTOR3& GetPosition() { return m_eye; }
	const D3DXMATRIXA16& GetViewMatrix() { return m_matView; }
};