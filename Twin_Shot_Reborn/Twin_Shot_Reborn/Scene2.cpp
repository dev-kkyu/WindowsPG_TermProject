#include "Scene2.h"

Scene2::Scene2()
{
	background.Load(L"./Resources/Images/Background/Stage2.png");


	// nonBlockTiles ��ġ
	for (int i = 0; i < 2; i++) {
		// ��ũ �� - ����
		nonBlockTiles.emplace_back(POINT{ 75,  151 + i * 400 }, 25);
		nonBlockTiles.emplace_back(POINT{ 125, 151 + i * 400 }, 24);
		nonBlockTiles.emplace_back(POINT{ 175, 151 + i * 400 }, 26);
		nonBlockTiles.emplace_back(POINT{ 225, 151 + i * 400 }, 24);
		nonBlockTiles.emplace_back(POINT{ 275, 151 + i * 400 }, 25);

		nonBlockTiles.emplace_back(POINT{ 1125, 351 + i * 400 }, 25);
		nonBlockTiles.emplace_back(POINT{ 1175, 351 + i * 400 }, 24);
		nonBlockTiles.emplace_back(POINT{ 1225, 351 + i * 400 }, 26);
		nonBlockTiles.emplace_back(POINT{ 1275, 351 + i * 400 }, 24);
		nonBlockTiles.emplace_back(POINT{ 1325, 351 + i * 400 }, 25);

		// �Ķ� �� - ����
		nonBlockTiles.emplace_back(POINT{ 75,  351 + i * 400 }, 29);
		nonBlockTiles.emplace_back(POINT{ 125, 351 + i * 400 }, 30);
		nonBlockTiles.emplace_back(POINT{ 175, 351 + i * 400 }, 31);
		nonBlockTiles.emplace_back(POINT{ 225, 351 + i * 400 }, 30);
		nonBlockTiles.emplace_back(POINT{ 275, 351 + i * 400 }, 29);

		nonBlockTiles.emplace_back(POINT{ 1125, 151 + i * 400 }, 29);
		nonBlockTiles.emplace_back(POINT{ 1175, 151 + i * 400 }, 30);
		nonBlockTiles.emplace_back(POINT{ 1225, 151 + i * 400 }, 31);
		nonBlockTiles.emplace_back(POINT{ 1275, 151 + i * 400 }, 30);
		nonBlockTiles.emplace_back(POINT{ 1325, 151 + i * 400 }, 29);
	}

	// nonBlock ���� 
	nonBlockTiles.emplace_back(POINT{ 525,  151 }, 27);
	nonBlockTiles.emplace_back(POINT{ 925,  401 }, 27);
	nonBlockTiles.emplace_back(POINT{ 725,  651 }, 27);


	// Ÿ�� ��ġ (���� 28, ���� 22)
	for (int i = 0; i < 28; ++i) { // ���� 

		if (i > 0 and i < 6) {
			tiles.emplace_back(POINT{ 25 + i * 50, 200 }, rand() % 3 + 20); // ���� �ٴ�
			tiles.emplace_back(POINT{ 25 + i * 50, 400 }, rand() % 3 + 20); // ���� �ٴ�
			tiles.emplace_back(POINT{ 25 + i * 50, 600 }, rand() % 3 + 20); // ���� �ٴ�
			tiles.emplace_back(POINT{ 25 + i * 50, 800 }, rand() % 3 + 20); // ���� �ٴ�
		}

		if (i > 8 and i < 19) {
			tiles.emplace_back(POINT{ 25 + i * 50, 200 }, rand() % 3 + 20); // ���
			tiles.emplace_back(POINT{ 25 + i * 50, 450 }, rand() % 3 + 20); // ���
			tiles.emplace_back(POINT{ 25 + i * 50, 700 }, rand() % 3 + 20); // ���

		}

		if (i > 21 and i < 28) {
			tiles.emplace_back(POINT{ 25 + i * 50, 200 }, rand() % 3 + 20); // ������ �ٴ�
			tiles.emplace_back(POINT{ 25 + i * 50, 400 }, rand() % 3 + 20); // ������ �ٴ�
			tiles.emplace_back(POINT{ 25 + i * 50, 600 }, rand() % 3 + 20); // ������ �ٴ�
			tiles.emplace_back(POINT{ 25 + i * 50, 800 }, rand() % 3 + 20); // ������ �ٴ�
		}
	}


	// ���� 
	for (int i = 0; i < 22; ++i) {
		tiles.emplace_back(POINT{ 25, 50 + i * 50 }, rand() % 3 + 20);
		tiles.emplace_back(POINT{ 1375, 50 + i * 50 }, rand() % 3 + 20);
	}

	// �÷��̾� ��ġ
	player.setPos(POINT{ 1125,150 });
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
