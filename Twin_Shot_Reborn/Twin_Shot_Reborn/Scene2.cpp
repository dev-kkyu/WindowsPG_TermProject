#include "Scene2.h"

Scene2::Scene2()
{
	background.Load(L"./Resources/Images/Background/Stage2.png");

	// 타일 배치 (가로 28, 세로 22)
	for (int i = 0; i < 28; ++i) { // 가로 

		nonBlockTiles.emplace_back(POINT{ 25 + i * 50, 50 }); // 천장은 충돌하면 안되므로 nonBlockTiles에 추가

		if (i < 5)
			tiles.emplace_back(POINT{ 25 + i * 50, 400 }); // 왼쪽 첫번째 바닥

		if (i < 10)
			tiles.emplace_back(POINT{ 25 + i * 50, 750 }, 5); // 왼쪽 아래 바닥

		if (i > 8 and i < 20) {
			tiles.emplace_back(POINT{ 25 + i * 50, 300 }); // 가운데 첫번째 바닥
			tiles.emplace_back(POINT{ 25 + i * 50, 550 }); // 가운데 아래 바닥
		}

		if (i > 18)
			tiles.emplace_back(POINT{ 25 + i * 50, 750 }, 5); // 오른쪽 아래 바닥
		if (i > 22)
			tiles.emplace_back(POINT{ 25 + i * 50, 400 }); // 오른쪽 첫번째 바닥
	}


	// 플레이어 배치
	player.setPos(POINT{ 1100,700 });
}

Scene2::~Scene2()
{
}

void Scene2::initialize()
{
}

void Scene2::update(float elapsedTime)
{
	SceneBase::update(elapsedTime);
}

void Scene2::draw(HDC hdc) const
{
	SceneBase::draw(hdc);
}

void Scene2::destroy()
{
}

void Scene2::processWindowMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CHAR:
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MOUSEMOVE:
		SceneBase::processWindowMessage(hWnd, message, wParam, lParam);
		break;
	default:
		MessageBoxA(hWnd, "Wrong Window Message On Scene2", nullptr, MB_OK);
		break;
	}
}
