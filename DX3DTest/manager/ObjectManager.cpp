#include "stdAfx.h"
#include "ObjectManager.h"

ObjectManager::ObjectManager(void)
{
}

ObjectManager::~ObjectManager(void)
{
}

void ObjectManager::AddObject(IObject* pObject)
{
	m_setObject.insert(pObject);
}

void ObjectManager::RemoveObject(IObject* pObject)
{
	m_setObject.erase(pObject);
}

void ObjectManager::Destroy()
{
	assert(m_setObject.empty() && "������ ��ü �� �������� ���� ��ü�� �ֽ��ϴ�.");
}

void ObjectManager::AddToTagList(WORD _tag, IDisplayObject * _object)
{
	m_tagList[_tag].push_back(_object);
}

void ObjectManager::RemoveFromTagList(WORD _tag, IDisplayObject* _pObject)
{
	m_tagList[_tag].remove(_pObject);
}

IDisplayObject * ObjectManager::FindObjectByTag(WORD _tag)
{
	if (m_tagList[_tag].empty() == true) return NULL;

	return m_tagList[_tag].front();
}

list<IDisplayObject*> ObjectManager::FindObjectsByTag(WORD _tag)
{
	return m_tagList[_tag];
}

