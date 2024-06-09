#include "GameScene.h"

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

GameScene::GameScene()
{
	background.Load(L"./Resources/Images/Background/Stage1.png");

	// 타일 배치
	for (int i = 0; i < 28; ++i) {
		tiles.emplace_back(POINT{ 25 + i * 50, 50 });
		tiles.emplace_back(POINT{ 25 + i * 50, 900 });
		if (i < 12)
			tiles.emplace_back(POINT{ 25 + i * 50, 750 });
	}
	for (int i = 0; i < 22; ++i) {
		tiles.emplace_back(POINT{ 25, 50 + (i + 1) * 50 });
		tiles.emplace_back(POINT{ 1375, 50 + (i + 1) * 50 });
	}

	// 플레이어 배치
	player.setPos(POINT{ 600, 850 });
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
			if (t.getBottom() >= player.getBottom()) {		// 상승시 충돌 범위를 줄여준다
				if (t.getLeft() < player.getRight() and t.getRight() > player.getLeft()) {	// 좌우에 대하여 충돌이면
					newPos.x = befPos.x;
					player.setPos(newPos);
					flagVX = true;
					break;
				}
			}
		}
	}

	// 상하 충돌 (좌우 해결된 이후 다시 검사)
	for (const auto& t : tiles) {
		if (t.isCollide(player)) {	// 플레이어와 충돌시
			if (t.getTop() < player.getBottom() and t.getBottom() > player.getTop()) {	// 상하에 대하여 충돌이면
				if (newPos.y > befPos.y) {				// 낙하 중에만 적용한다. (상승중에는 충돌X)
					if (newPos.y < t.getTop() + 10) {	// 충분히 타일 위에 올라왔을 때만 적용
						newPos.y = static_cast<float>(t.getTop());
						player.setPos(newPos);
						player.setFly(false);
						flagVX = false;
						break;
					}
				}
			}
		}
	}

	if (flagVX)
		player.setVelocityX(0.f);

	if (not player.getFly()) {		// 점프 중이 아닐때
		TileObject tempObj{ POINT{int(newPos.x), int(newPos.y + 10)} };		// 임시 객체 만들기
		tempObj.setSize({ 100, 100 });		// 플레이어 사이즈로 조정

		bool isOnTile = false;
		for (const auto& t : tiles) {
			if (t.isCollide(tempObj)) {		// 타일과 임시 객체 충돌시
				isOnTile = true;			// 플레이어는 타일 위에 있다.
				break;
			}
		}
		if (not isOnTile) {		// 현재 타일 위에 있지 않을때
			player.setFly(true);
			player.setVelocityY(0.f);
		}
	}

}

void GameScene::draw(HDC hdc) const
{
	// 스크롤링 적용
	int windowLeft = player.getPosInt().x - W_WIDTH / 2;
	windowLeft = my_clamp(windowLeft, 0, M_WIDTH - W_WIDTH);

	background.MyDraw(hdc, RECT{ 0, 0, W_WIDTH, W_HEIGHT });

	for (auto& t : tiles)
		t.draw(hdc, windowLeft);

	player.draw(hdc, windowLeft);
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
