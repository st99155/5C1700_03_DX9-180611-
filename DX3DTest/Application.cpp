#include "stdafx.h"
#include "Application.h"

Application::Application()
{
}


Application::~Application()
{
}

void Application::Init()
{
	DX::Get()->Init();
	Mouse::Get()->Init(DX::GetInfo().hWnd);
	Camera::Get()->Init();
	SceneManager::Get()->Init();
}

void Application::Destroy()
{
	Mouse::Delete();
	Keyboard::Delete();
	Camera::Delete();
	SceneManager::Delete();
	g_pObjMgr->Destroy();
	g_pFontMgr->Destroy();
	g_pTextureManager->Destroy();
	Debug::Delete();
	DX::Delete();
}

void Application::Update()
{
	Debug::Get()->InitText();
	Time::Get()->Update();
	Mouse::Get()->Update();
	Keyboard::Get()->Update();
	SceneManager::Get()->Update();
	Camera::Get()->Update();
}

void Application::Render()
{
	//Rect 배열 수, Rect 배열, Flags, Color, z, stencil
	DX::GetDevice()->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(64, 64, 64), 1.0f, 0);
	
	DX::GetDevice()->BeginScene();
	
	SceneManager::Get()->Render();
	Debug::Get()->Print();

	DX::GetDevice()->EndScene();
	DX::GetDevice()->Present(NULL, NULL, NULL, NULL);
}

void Application::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Mouse::Get()->InputProc(message, wParam, lParam);
}

