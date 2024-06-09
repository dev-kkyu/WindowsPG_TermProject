#include "Scene1.h"

#include "Define.h"

#include <chrono>

template <class T>
static inline constexpr T my_clamp(T val, T min_val, T max_val)
{
	if (val < min_val)
		return min_val;
	if (val > max_val)
		return max_val;
	return val;
}

Scene1::Scene1()
{
	background.Load(L"./Resources/Images/Background/Stage1.png");

	// nonBlockTiles ��ġ

	// ��� 
	nonBlockTiles.emplace_back(POINT{ 625, 501 }, 17, SIZE{ 50,30 }); // ����

	// ��� �� 
	nonBlockTiles.emplace_back(POINT{ 775, 250 }, 17, SIZE{ 50,20 }); // ����
	nonBlockTiles.emplace_back(POINT{ 825, 250 }, 18);  // ��������

	// ������ �Ʒ� 
	nonBlockTiles.emplace_back(POINT{ 1075, 701 }, 17, SIZE{ 50,30 }); // ����
	nonBlockTiles.emplace_back(POINT{ 1125, 701 }, 18);  // ��������

	// ���� �Ʒ� 
	nonBlockTiles.emplace_back(POINT{ 225, 701 }, 17, SIZE{ 50,30 }); // ����
	nonBlockTiles.emplace_back(POINT{ 275, 701 }, 19, SIZE{ 50,100 });  // ��������


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

	// ����
	tiles.emplace_back(POINT{ 25, 50 + 1 * 50 }, 8); // ���� ��
	tiles.emplace_back(POINT{ 25, 50 + 2 * 50 }, 13); // ���� ��
	tiles.emplace_back(POINT{ 25, 50 + 3 * 50 }, 9); // ���� ��
	tiles.emplace_back(POINT{ 25, 50 + 4 * 50 }, 13); // ���� ��
	tiles.emplace_back(POINT{ 25, 50 + 5 * 50 }, 13); // ���� ��
	tiles.emplace_back(POINT{ 25, 50 + 6 * 50 }, 16); // ���� ��

	tiles.emplace_back(POINT{ 25, 50 + 8 * 50 }, 8); // ���� ��
	tiles.emplace_back(POINT{ 25, 50 + 9 * 50 }, 13); // ���� ��
	tiles.emplace_back(POINT{ 25, 50 + 10 * 50 }, 9); // ���� ��
	tiles.emplace_back(POINT{ 25, 50 + 11 * 50 }, 13); // ���� ��
	tiles.emplace_back(POINT{ 25, 50 + 12 * 50 }, 13); // ���� ��
	tiles.emplace_back(POINT{ 25, 50 + 13 * 50 }, 16); // ���� ��

	tiles.emplace_back(POINT{ 25, 50 + 15 * 50 }, 8); // ���� ��
	tiles.emplace_back(POINT{ 25, 50 + 16 * 50 }, 13); // ���� ��
	tiles.emplace_back(POINT{ 25, 50 + 17 * 50 }, 14); // ���� ��


	tiles.emplace_back(POINT{ 1375, 50 + 1 * 50 }, 8);  // ������ �� 
	tiles.emplace_back(POINT{ 1375, 50 + 2 * 50 }, 13); // ������ �� 
	tiles.emplace_back(POINT{ 1375, 50 + 3 * 50 }, 9);  // ������ �� 
	tiles.emplace_back(POINT{ 1375, 50 + 4 * 50 }, 13); // ������ �� 
	tiles.emplace_back(POINT{ 1375, 50 + 5 * 50 }, 13); // ������ �� 
	tiles.emplace_back(POINT{ 1375, 50 + 6 * 50 }, 16); // ������ �� 

	tiles.emplace_back(POINT{ 1375, 50 + 8 * 50 }, 8);  // ������ �� 
	tiles.emplace_back(POINT{ 1375, 50 + 9 * 50 }, 13); // ������ �� 
	tiles.emplace_back(POINT{ 1375, 50 + 10 * 50 }, 9); // ������ �� 
	tiles.emplace_back(POINT{ 1375, 50 + 11 * 50 }, 13); // ������ �� 
	tiles.emplace_back(POINT{ 1375, 50 + 12 * 50 }, 13); // ������ �� 
	tiles.emplace_back(POINT{ 1375, 50 + 13 * 50 }, 16); // ������ �� 

	tiles.emplace_back(POINT{ 1375, 50 + 15 * 50 }, 8);  // ������ �� 
	tiles.emplace_back(POINT{ 1375, 50 + 16 * 50 }, 13); // ������ �� 
	tiles.emplace_back(POINT{ 1375, 50 + 17 * 50 }, 14); // ������ �� 

	// ��� ��� - ����
	nonBlockTiles.emplace_back(POINT{ 25 + 11 * 50, 350 }, 8);
	nonBlockTiles.emplace_back(POINT{ 25 + 11 * 50, 400 }, 14);

	// ��� ��� - ������
	nonBlockTiles.emplace_back(POINT{ 25 + 17 * 50, 350 }, 8);
	nonBlockTiles.emplace_back(POINT{ 25 + 17 * 50, 400 }, 14);

	// ��� �Ʒ� ��� - ����
	tiles.emplace_back(POINT{ 25 + 9 * 50, 600 }, 8);
	tiles.emplace_back(POINT{ 25 + 9 * 50, 650 }, 13);
	tiles.emplace_back(POINT{ 25 + 9 * 50, 700 }, 16);

	// ��� �Ʒ� ��� - ������
	tiles.emplace_back(POINT{ 25 + 19 * 50, 600 }, 8);
	tiles.emplace_back(POINT{ 25 + 19 * 50, 650 }, 13);
	tiles.emplace_back(POINT{ 25 + 19 * 50, 700 }, 16);

	// ��� �� �Ʒ� ��� - ����
	tiles.emplace_back(POINT{ 25 + 9 * 50, 800 }, 8);
	tiles.emplace_back(POINT{ 25 + 9 * 50, 850 }, 13);
	tiles.emplace_back(POINT{ 25 + 9 * 50, 900 }, 16);

	// ��� �� �Ʒ� ��� - ������
	tiles.emplace_back(POINT{ 25 + 19 * 50, 800 }, 8);
	tiles.emplace_back(POINT{ 25 + 19 * 50, 850 }, 13);
	tiles.emplace_back(POINT{ 25 + 19 * 50, 900 }, 16);

	// �÷��̾� ��ġ
	player.setPos(POINT{ 1100,700 });

	monsters.emplace_back(POINT{ 200, 700 }, 0, SIZE{ 120, 100 });

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

	for (auto& m : monsters)
		m.update(elapsedTime);


	// �÷��̾� ȭ��� ���� �浹 ó��
	std::vector<std::list<ArrowObject>::iterator> deleteArrows;
	for (auto& m : monsters) {
		for (auto a = player.arrows.begin(); a != player.arrows.end(); ++a) {
			if (m.isCollide(*a)) {
				deleteArrows.emplace_back(a);
				m.onHit(*a);
			}
		}
	}
	for (const auto& itr : deleteArrows) {
		player.arrows.erase(itr);
	}
	// ���� ���� ����
	std::vector<std::list<MonsterObject>::iterator> deleteMonsters;
	for (auto m = monsters.begin(); m != monsters.end(); ++m) {
		if (m->getIsDead()) {
			auto nowTime = std::chrono::steady_clock::now();
			if (m->getDeadTime() + std::chrono::milliseconds(1500) <= nowTime) {
				deleteMonsters.emplace_back(m);
			}
		}
	}
	for (const auto& itr : deleteMonsters) {
		monsters.erase(itr);
	}
}

void Scene1::draw(HDC hdc) const
{
	SceneBase::draw(hdc);

	// ��ũ�Ѹ� ����
	int windowLeft = player.getPosInt().x - W_WIDTH / 2;
	windowLeft = my_clamp(windowLeft, 0, M_WIDTH - W_WIDTH);

	for (auto& m : monsters)
		m.draw(hdc, windowLeft);
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
	case WM_KEYUP:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MOUSEMOVE:
		SceneBase::processWindowMessage(hWnd, message, wParam, lParam);
		break;
	default:
		MessageBoxA(hWnd, "Wrong Window Message On Scene1", nullptr, MB_OK);
		break;
	}
}
