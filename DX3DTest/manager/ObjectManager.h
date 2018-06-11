#pragma once

#define g_pObjMgr ObjectManager::GetInstance()

class IObject;
class IDisplayObject;

class ObjectManager
{
	SINGLETON(ObjectManager)
private:
	set<IObject*> m_setObject;
	map<WORD, list<IDisplayObject*>> m_tagList;

public:
	void AddObject(IObject* pObject);
	void RemoveObject(IObject* pObject);
	void Destroy();

	void AddToTagList(WORD _tag, IDisplayObject* _pObject);
	void RemoveFromTagList(WORD _tag, IDisplayObject* _pObject);
	IDisplayObject* FindObjectByTag(WORD _tag);
	list<IDisplayObject*> FindObjectsByTag(WORD _tag);

};

