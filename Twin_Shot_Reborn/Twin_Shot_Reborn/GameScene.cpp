#include "GameScene.h"

#include "Define.h"

GameScene::GameScene()
{
	background.Load(L"./Resources/Images/Background/Stage1.png");

	// 타일 배치
	for (int i = 0; i < 24; ++i) {
		tiles.emplace_back(POINT{ 25 + i * 50, 50 });
		tiles.emplace_back(POINT{ 25 + i * 50, 900 });
	}
	for (int i = 0; i < 22; ++i) {
		tiles.emplace_back(POINT{ 25, 50 + (i + 1) * 50 });
		tiles.emplace_back(POINT{ 1175, 50 + (i + 1) * 50 });
	}
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

	// 바닥 충돌처리 로직 (추후 장애물에 관하여로 수정)
	if (player.getFly()) {		// 현재 공중에 떠 있는 상태이면
		POINTFLOAT playerPos = player.getPos();
		if (playerPos.y > 450.f) {
			player.setFly(false);
			player.setPos(POINTFLOAT{ playerPos.x, 450.f });
		}
	}

}

void GameScene::draw(HDC hdc)
{
	background.MyDraw(hdc, RECT{ 0, 0, W_WIDTH, W_HEIGHT });

	for (auto& t : tiles)
		t.draw(hdc);

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
