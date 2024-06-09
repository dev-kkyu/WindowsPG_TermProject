#include "Scene1.h"

Scene1::Scene1()
{
	background.Load(L"./Resources/Images/Background/Stage1.png");

	// 타일 배치 (가로 28, 세로 22)
	for (int i = 0; i < 28; ++i) { // 가로 

		tiles.emplace_back(POINT{ 25 + i * 50, 50 }); // 천장

		if (i < 5)
			tiles.emplace_back(POINT{ 25 + i * 50, 400 }); // 왼쪽 첫번째 바닥

		if (i < 10)
			tiles.emplace_back(POINT{ 25 + i * 50, 750 }, 5); // 왼쪽 아래 바닥
		
		if (i > 8 and i < 20){
			tiles.emplace_back(POINT{ 25 + i * 50, 300 }); // 가운데 첫번째 바닥
			tiles.emplace_back(POINT{ 25 + i * 50, 550 }); // 가운데 아래 바닥
		}

		if (i > 18)
			tiles.emplace_back(POINT{ 25 + i * 50, 750 }, 5); // 오른쪽 아래 바닥
		if ( i > 22)
			tiles.emplace_back(POINT{ 25 + i * 50, 400 }); // 오른쪽 첫번째 바닥
	}


	// 세로 
		
		tiles.emplace_back(POINT{ 25, 50 + 1 * 50 }, 8); // 왼쪽 벽
		tiles.emplace_back(POINT{ 25, 50 + 2 * 50 }, 13); // 왼쪽 벽
		tiles.emplace_back(POINT{ 25, 50 + 3 * 50 }, 9); // 왼쪽 벽
		tiles.emplace_back(POINT{ 25, 50 + 4 * 50 }, 13); // 왼쪽 벽
		tiles.emplace_back(POINT{ 25, 50 + 5 * 50 }, 13); // 왼쪽 벽
		tiles.emplace_back(POINT{ 25, 50 + 6 * 50 }, 16); // 왼쪽 벽

		tiles.emplace_back(POINT{ 25, 50 + 8 * 50 }, 8); // 왼쪽 벽
		tiles.emplace_back(POINT{ 25, 50 + 9 * 50 }, 13); // 왼쪽 벽
		tiles.emplace_back(POINT{ 25, 50 + 10 * 50 }, 9); // 왼쪽 벽
		tiles.emplace_back(POINT{ 25, 50 + 11 * 50 }, 13); // 왼쪽 벽
		tiles.emplace_back(POINT{ 25, 50 + 12 * 50 }, 13); // 왼쪽 벽
		tiles.emplace_back(POINT{ 25, 50 + 13 * 50 }, 16); // 왼쪽 벽

		tiles.emplace_back(POINT{ 25, 50 + 15 * 50 }, 8); // 왼쪽 벽
		tiles.emplace_back(POINT{ 25, 50 + 16 * 50 }, 13); // 왼쪽 벽
		tiles.emplace_back(POINT{ 25, 50 + 17 * 50 }, 14); // 왼쪽 벽

		
		tiles.emplace_back(POINT{ 1375, 50 + 1 * 50 }, 8);  // 오른쪽 벽 
		tiles.emplace_back(POINT{ 1375, 50 + 2 * 50 }, 13); // 오른쪽 벽 
		tiles.emplace_back(POINT{ 1375, 50 + 3 * 50 }, 9);  // 오른쪽 벽 
		tiles.emplace_back(POINT{ 1375, 50 + 4 * 50 }, 13); // 오른쪽 벽 
		tiles.emplace_back(POINT{ 1375, 50 + 5 * 50 }, 13); // 오른쪽 벽 
		tiles.emplace_back(POINT{ 1375, 50 + 6 * 50 }, 16); // 오른쪽 벽 
								  
		tiles.emplace_back(POINT{ 1375, 50 + 8 * 50 }, 8);  // 오른쪽 벽 
		tiles.emplace_back(POINT{ 1375, 50 + 9 * 50 }, 13); // 오른쪽 벽 
		tiles.emplace_back(POINT{ 1375, 50 + 10 * 50 }, 9); // 오른쪽 벽 
		tiles.emplace_back(POINT{ 1375, 50 + 11 * 50 }, 13); // 오른쪽 벽 
		tiles.emplace_back(POINT{ 1375, 50 + 12 * 50 }, 13); // 오른쪽 벽 
		tiles.emplace_back(POINT{ 1375, 50 + 13 * 50 }, 16); // 오른쪽 벽 
								 
		tiles.emplace_back(POINT{ 1375, 50 + 15 * 50 }, 8);  // 오른쪽 벽 
		tiles.emplace_back(POINT{ 1375, 50 + 16 * 50 }, 13); // 오른쪽 벽 
		tiles.emplace_back(POINT{ 1375, 50 + 17 * 50 }, 14); // 오른쪽 벽 
		
		// 가운데 기둥 - 왼쪽
		tiles.emplace_back(POINT{ 25 + 11 * 50, 350 }, 8);
		tiles.emplace_back(POINT{ 25 + 11 * 50, 400 }, 14); 

		// 가운데 기둥 - 오른쪽
		tiles.emplace_back(POINT{ 25 + 17 * 50, 350 }, 8);
		tiles.emplace_back(POINT{ 25 + 17 * 50, 400 }, 14);
	
		// 가운데 아래 기둥 - 왼쪽
		tiles.emplace_back(POINT{ 25 + 9 * 50, 600 }, 8);
		tiles.emplace_back(POINT{ 25 + 9 * 50, 650 }, 13);
		tiles.emplace_back(POINT{ 25 + 9 * 50, 700 }, 16);
		
		// 가운데 아래 기둥 - 오른쪽
		tiles.emplace_back(POINT{ 25 + 19 * 50, 600 }, 8);
		tiles.emplace_back(POINT{ 25 + 19 * 50, 650 }, 13);
		tiles.emplace_back(POINT{ 25 + 19 * 50, 700 }, 16);

		// 가운데 더 아래 기둥 - 왼쪽
		tiles.emplace_back(POINT{ 25 + 9 * 50, 800 }, 8);
		tiles.emplace_back(POINT{ 25 + 9 * 50, 850 }, 13);
		tiles.emplace_back(POINT{ 25 + 9 * 50, 900 }, 16);

		// 가운데 더 아래 기둥 - 오른쪽
		tiles.emplace_back(POINT{ 25 + 19 * 50, 800 }, 8);
		tiles.emplace_back(POINT{ 25 + 19 * 50, 850 }, 13);
		tiles.emplace_back(POINT{ 25 + 19 * 50, 900 }, 16);

	// 플레이어 배치
	player.setPos(POINT{ 1100,700});
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
