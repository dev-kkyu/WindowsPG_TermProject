#include "Scene3.h"

Scene3::Scene3()
{
	background.Load(L"./Resources/Images/Background/Stage3.png");

	// Ÿ�� ��ġ (���� 28, ���� 22)
	for (int i = 0; i < 28; ++i) { // ���� 

		nonBlockTiles.emplace_back(POINT{ 25 + i * 50, 50 }); // õ���� �浹�ϸ� �ȵǹǷ� nonBlockTiles�� �߰�

		if (i < 5)
			tiles.emplace_back(POINT{ 25 + i * 50, 400 }); // ���� ù��° �ٴ�

		if (i < 10)
			tiles.emplace_back(POINT{ 25 + i * 50, 750 }, 5); // ���� �Ʒ� �ٴ�

		if (i > 8 and i < 20) {
			tiles.emplace_back(POINT{ 25 + i * 50, 300 }); // ��� ù��° �ٴ�
			tiles.emplace_back(POINT{ 25 + i * 50, 550 }); // ��� �Ʒ� �ٴ�
		}

		if (i > 18)
			tiles.emplace_back(POINT{ 25 + i * 50, 750 }, 5); // ������ �Ʒ� �ٴ�
		if (i > 22)
			tiles.emplace_back(POINT{ 25 + i * 50, 400 }); // ������ ù��° �ٴ�
	}


	// �÷��̾� ��ġ
	player.setPos(POINT{ 1100,700 });
}

Scene3::~Scene3()
{
}

void Scene3::initialize()
{
}

void Scene3::update(float elapsedTime)
{
	SceneBase::update(elapsedTime);
}

void Scene3::draw(HDC hdc) const
{
	SceneBase::draw(hdc);
}

void Scene3::destroy()
{
}

void Scene3::processWindowMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
		MessageBoxA(hWnd, "Wrong Window Message On Scene3", nullptr, MB_OK);
		break;
	}
}
