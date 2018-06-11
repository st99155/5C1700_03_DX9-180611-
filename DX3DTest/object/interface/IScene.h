#pragma once
#include "stdafx.h"
#include "IObject.h"

class IDisplayObject;

class IScene : public IObject
{
protected:
	set<IDisplayObject*> m_pDisplayObjects;

	IScene() {}

public:
	virtual ~IScene() {}
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	
	void AddDisplayObject(IDisplayObject* p) { m_pDisplayObjects.insert(p); }
	void RemoveDisplayObject(IDisplayObject* p) { m_pDisplayObjects.erase(p); }
	void OnUpdateIScene() { for (auto p : m_pDisplayObjects) SAFE_UPDATE(p); }
	void OnRenderIScene() { for (auto p : m_pDisplayObjects) SAFE_RENDER(p); }
	void OnDestructIScene() { for (auto p : m_pDisplayObjects) SAFE_RELEASE(p); }
};

