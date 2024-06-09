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
	const POINTFLOAT befPos = player.getPos();	// 업데이트 전 플레이어 위치

	player.update(elapsedTime);

	bool flagVX = false;		// X방향 가속도를 초기화 할 것인지
	// 좌우 충돌
	POINTFLOAT newPos = player.getPos();
	for (const auto& t : tiles) {
		if (t.isCollide(player)) {	// 플레이어와 충돌시
			if (t.getLeft() < player.getRight() and t.getRight() > player.getLeft()) {	// 좌우에 대하여 충돌이면
				newPos.x = befPos.x;
				player.setPos(newPos);
				flagVX = true;
				break;
			}
		}
	}

	// 상하 충돌 (좌우 해결된 이후 다시 검사
	for (const auto& t : tiles) {
		if (t.isCollide(player)) {	// 플레이어와 충돌시
			if (t.getTop() < player.getBottom() and t.getBottom() > player.getTop()) {	// 상하에 대하여 충돌이면
				newPos.y = befPos.y;
				player.setPos(newPos);
				player.setFly(false);
				flagVX = false;
				break;
			}
		}
	}

	if (flagVX)
		player.setVelocityX(0.f);

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
