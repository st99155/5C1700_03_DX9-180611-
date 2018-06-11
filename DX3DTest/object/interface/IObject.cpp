#include "stdAfx.h"
#include "IObject.h"
#include "./manager/ObjectManager.h"

IObject::IObject()
	: m_nRefCount(1)
{
	g_pObjMgr->AddObject(this);
}

IObject::~IObject()
{
	g_pObjMgr->RemoveObject(this);
	assert(m_nRefCount <= 0 && "Release를 이용해서 객체를 해제하세요.");
}

void IObject::AddRef()
{
	++m_nRefCount;
}

void IObject::Release()
{
	--m_nRefCount;
	if (m_nRefCount <= 0)
	{
		delete this;
	}
}
