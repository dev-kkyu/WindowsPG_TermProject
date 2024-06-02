#include "GameScene.h"

#include "Define.h"

GameScene::GameScene()
{
	background.Load(L"./Resources/Images/Background/Stage1.png");
}

GameScene::~GameScene()
{
}

void GameScene::initialize()
{
}

void GameScene::update(float elapsedTime)
{
	player.update(elapsedTime);
}

void GameScene::draw(HDC hdc)
{
	background.MyDraw(hdc, RECT{ 0, 0, W_WIDTH, W_HEIGHT });
	player.draw(hdc);
}

void GameScene::destroy()
{
}

void GameScene::processWindowMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
		MessageBoxA(hWnd, "Wrong Window Message On GameScene", nullptr, MB_OK);
		break;
	}
}
