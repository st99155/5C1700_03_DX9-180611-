#pragma once
#include "stdafx.h"

class CubemanParts;

class Cubeman : public IDisplayObject
{
private:
	CubemanParts * m_pRootCube;
	bool			m_isMoving;

	D3DXVECTOR3		m_deltaPos;
	D3DXVECTOR3		m_deltaRot;
	D3DXVECTOR3		m_forward;

	float			m_moveSpeed;
	float			m_currMoveSpeedRate;
	float			m_rotationSpeed;

	bool			m_isJumping;
	float			m_jumpPower;
	float			m_gravity;
	float			m_currGravity;

public:
	Cubeman();
	~Cubeman();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	void CreateParts(CubemanParts* &pParts, IDisplayObject* pParent,
		D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 trans, vector<vector<int>>* uv = NULL);
	void UpdateMoving();

	vector<vector<int>> uvBody = {
		{ 32, 32, 32, 20, 40, 20, 40, 32 },	// 후
	{ 20, 32, 20, 20, 28, 20, 28, 32 },	// 전
	{ 28, 32, 28, 20, 32, 20, 32, 32 },	// 좌
	{ 16, 32, 16, 20, 20, 20, 20, 32 },	// 우
	{ 20, 20, 20, 16, 28, 16, 28, 20 },	// 상
	{ 28, 16, 28, 20, 36, 20, 36, 16 }	// 하
	};

	vector<vector<int>> uvHead = {
		{ 24, 16, 24, 8, 32, 8, 32, 16 },	// 후
	{ 8, 16, 8, 8, 16, 8, 16, 16 },		// 전
	{ 16, 16, 16, 8, 24, 8, 24, 16 },	// 좌
	{ 0, 16, 0, 8, 8, 8, 8, 16 },		// 우
	{ 8, 8, 8, 0, 16, 0, 16, 8 },		// 상
	{ 16, 0, 16, 8, 24, 8, 24, 0 }		// 하
	};
};
