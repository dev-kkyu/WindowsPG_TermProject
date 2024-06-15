#include "Scene2.h"

#include "Define.h"

#include "MySound.h"

template <class T>
static inline constexpr T my_clamp(T val, T min_val, T max_val)
{
	if (val < min_val)
		return min_val;
	if (val > max_val)
		return max_val;
	return val;
}

Scene2::Scene2()
{
	background.Load(L"./Resources/Images/Background/Stage2.png");
	cloud.Load(L"./Resources/Images/Background/Cloud2.png");

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


	// �׵θ�
	for (int i = 0; i < 22; ++i) {
		tiles.emplace_back(POINT{ 25, 50 + i * 50 }, rand() % 3 + 20);
		tiles.emplace_back(POINT{ 1375, 50 + i * 50 }, rand() % 3 + 20);
	}

	// �÷��̾� ��ġ
	player.setPos(POINT{ 1125,150 });

	// ���� ��ġ 

	// ��� 
	monsters.emplace_back(POINT{ 550, 150 }, 2, SIZE{ 75, 70 }, 500, 900); // �¿� �̵� ���� - 1��° ĭ
	monsters.emplace_back(POINT{ 550, 290 }, 1, SIZE{ 90, 90 }, 400, 1000); // ����ٴϴ� ���� - 2��° ĭ
	monsters.emplace_back(POINT{ 1000, 540 }, 1, SIZE{ 90, 90 }, 400, 1000); // ����ٴϴ� ���� - 3��° ĭ

	// ����
	monsters.emplace_back(POINT{ 100, 150 }, 2, SIZE{ 75, 70 }, 100, 250); // �¿� �̵� ���� - 1��° ĭ
	monsters.emplace_back(POINT{ 240, 350 }, 2, SIZE{ 75, 70 }, 100, 250); // �¿� �̵� ���� - 2��° ĭ
	monsters.emplace_back(POINT{ 120, 550 }, 2, SIZE{ 75, 70 }, 100, 250); // �¿� �̵� ���� - 3��° ĭ
	monsters.emplace_back(POINT{ 190, 750 }, 2, SIZE{ 75, 70 }, 100, 250); // �¿� �̵� ���� - 4��° ĭ

	// ������
	//monsters.emplace_back(POINT{ 1300, 150 }, 2, SIZE{ 75, 70 }, 1120, 1320); // �¿� �̵� ���� - 1��° ĭ
	monsters.emplace_back(POINT{ 1210, 350 }, 2, SIZE{ 75, 70 }, 1120, 1320); // �¿� �̵� ���� - 2��° ĭ
	monsters.emplace_back(POINT{ 1130, 550 }, 2, SIZE{ 75, 70 }, 1120, 1320); // �¿� �̵� ���� - 3��° ĭ
	monsters.emplace_back(POINT{ 1311, 750 }, 2, SIZE{ 75, 70 }, 1120, 1320); // �¿� �̵� ���� - 4��° ĭ

	MySound::getInstance().playNormalBGM();
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

	for (auto& m : monsters)
		m.update(elapsedTime);

	// �÷��̾� ȭ��� ���� �浹 ó��
	std::vector<std::list<ArrowObject>::iterator> deleteArrows;
	for (auto& m : monsters) {
		for (auto a = player.arrows.begin(); a != player.arrows.end(); ++a) {
			if (not m.getIsDead()) {
				if (m.isCollide(*a)) {
					playerScore += 100;				// ���� �߰�
					items.emplace_back(m.getPosInt());
					deleteArrows.emplace_back(a);
					m.onHit(*a);
				}
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
			if (m->getDeadTime() + std::chrono::milliseconds(3000) <= nowTime) {
				deleteMonsters.emplace_back(m);
			}
		}
	}
	for (const auto& itr : deleteMonsters) {
		monsters.erase(itr);
	}
	// �÷��̾� �ǰ�
	if (not player.getHit()) {
		for (const auto& m : monsters) {
			if (not m.getIsDead()) {
				if (m.isCollide(player)) {
					player.onHit();
					break;
				}
			}
		}
	}
}

void Scene2::draw(HDC hdc) const
{
	SceneBase::draw(hdc);

	// ��ũ�Ѹ� ����
	int windowLeft = player.getPosInt().x - W_WIDTH / 2;
	windowLeft = my_clamp(windowLeft, 0, M_WIDTH - W_WIDTH);

	for (auto& m : monsters)
		m.draw(hdc, windowLeft);
}

void Scene2::destroy()
{
}

bool Scene2::onClear() const
{
	return 0 == monsters.size();
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
