#include "Scene1.h"

Scene1::Scene1()
{
	background.Load(L"./Resources/Images/Background/Stage1.png");

	// 타일 배치
	for (int i = 0; i < 28; ++i) {
		tiles.emplace_back(POINT{ 25 + i * 50, 50 });
		tiles.emplace_back(POINT{ 25 + i * 50, 900 });
		if (i < 12)
			tiles.emplace_back(POINT{ 25 + i * 50, 750 });
	}
	for (int i = 0; i < 22; ++i) {
		tiles.emplace_back(POINT{ 25, 50 + (i + 1) * 50 });
		tiles.emplace_back(POINT{ 1375, 50 + (i + 1) * 50 });
	}

	// 플레이어 배치
	player.setPos(POINT{ 600, 850 });
}

Scene1::~Scene1()
{
}

void Scene1::initialize()
{
}

void Scene1::update(float elapsedTime)
{
	SceneBase::update(elapsedTime);
}

void Scene1::draw(HDC hdc) const
{
	SceneBase::draw(hdc);
}

void Scene1::destroy()
{
}

void Scene1::processWindowMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CHAR:
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_UP:
		case VK_DOWN:
		case VK_LEFT:
		case VK_RIGHT:
		case VK_SPACE:
			player.sendKeyMsg(message, wParam);
			break;
		}
		break;
	case WM_KEYUP:
		switch (wParam)
		{
		case VK_UP:
		case VK_DOWN:
		case VK_LEFT:
		case VK_RIGHT:
		case VK_SPACE:
			player.sendKeyMsg(message, wParam);
			break;
		}
		break;
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MOUSEMOVE:
		break;
	default:
		MessageBoxA(hWnd, "Wrong Window Message On Scene1", nullptr, MB_OK);
		break;
	}
}
