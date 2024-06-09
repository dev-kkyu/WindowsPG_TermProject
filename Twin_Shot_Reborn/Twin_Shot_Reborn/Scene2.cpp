#include "Scene2.h"

Scene2::Scene2()
{
	background.Load(L"./Resources/Images/Background/Stage2.png");


	// nonBlockTiles ��ġ
	nonBlockTiles.emplace_back(POINT{ 75, 151 }, 25); // ��

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
		tiles.emplace_back(POINT{ 25, 50 + i * 50 }, rand()%3 + 20);
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
