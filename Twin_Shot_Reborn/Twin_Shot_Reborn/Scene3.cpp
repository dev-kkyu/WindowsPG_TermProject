#include "Scene3.h"

#include "Define.h"

template <class T>
static inline constexpr T my_clamp(T val, T min_val, T max_val)
{
	if (val < min_val)
		return min_val;
	if (val > max_val)
		return max_val;
	return val;
}

Scene3::Scene3()
{
	background.Load(L"./Resources/Images/Background/Stage3.png");
	cloud.Load(L"./Resources/Images/Background/Cloud3.png");

	// 테두리
	for (int i = 0; i < 22; ++i) {
		if (i < 1) nonBlockTiles.emplace_back(POINT{ 25, 50 + i * 50 }, rand() % 4 + 32);
		else {
			tiles.emplace_back(POINT{ 25, 50 + i * 50 }, rand() % 4 + 32);
			tiles.emplace_back(POINT{ 1375, 50 + i * 50 }, rand() % 4 + 32);
		}
	}

	for (int i = 0; i < 28; ++i) { // 바닥 
		nonBlockTiles.emplace_back(POINT{ 25 + i * 50, 50 }, rand() % 4 + 32); // 
		tiles.emplace_back(POINT{ 25 + i * 50, 800 }, rand() % 4 + 32);
	}
	// 플레이어 배치
	player.setPos(POINT{ 1100,700 });

	boss.setPos(POINT{ 700, 400 });

	// 보스 타겟 설정
	boss.setTargetPlayer(player);
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

	boss.update(elapsedTime);
}

void Scene3::draw(HDC hdc) const
{
	SceneBase::draw(hdc);

	// 스크롤링 적용
	int windowLeft = player.getPosInt().x - W_WIDTH / 2;
	windowLeft = my_clamp(windowLeft, 0, M_WIDTH - W_WIDTH);

	boss.draw(hdc, windowLeft);
}

void Scene3::destroy()
{
}

bool Scene3::onClear() const
{
	return false;
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
