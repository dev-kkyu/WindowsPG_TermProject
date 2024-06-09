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

	// Ÿ�� ��ġ
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

	// �÷��̾� ��ġ
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
	const POINTFLOAT befPos = player.getPos();	// ������Ʈ �� �÷��̾� ��ġ

	player.update(elapsedTime);

	bool flagVX = false;		// X���� ���ӵ��� �ʱ�ȭ �� ������
	// �¿� �浹
	POINTFLOAT newPos = player.getPos();
	for (const auto& t : tiles) {
		if (t.isCollide(player)) {	// �÷��̾�� �浹��
			if (t.getBottom() >= player.getBottom()) {		// ��½� �浹 ������ �ٿ��ش�
				if (t.getLeft() < player.getRight() and t.getRight() > player.getLeft()) {	// �¿쿡 ���Ͽ� �浹�̸�
					newPos.x = befPos.x;
					player.setPos(newPos);
					flagVX = true;
					break;
				}
			}
		}
	}

	// ���� �浹 (�¿� �ذ�� ���� �ٽ� �˻�)
	for (const auto& t : tiles) {
		if (t.isCollide(player)) {	// �÷��̾�� �浹��
			if (t.getTop() < player.getBottom() and t.getBottom() > player.getTop()) {	// ���Ͽ� ���Ͽ� �浹�̸�
				if (newPos.y > befPos.y) {				// ���� �߿��� �����Ѵ�. (����߿��� �浹X)
					if (newPos.y < t.getTop() + 10) {	// ����� Ÿ�� ���� �ö���� ���� ����
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

	if (not player.getFly()) {		// ���� ���� �ƴҶ�
		TileObject tempObj{ POINT{int(newPos.x), int(newPos.y + 10)} };		// �ӽ� ��ü �����
		tempObj.setSize({ 100, 100 });		// �÷��̾� ������� ����

		bool isOnTile = false;
		for (const auto& t : tiles) {
			if (t.isCollide(tempObj)) {		// Ÿ�ϰ� �ӽ� ��ü �浹��
				isOnTile = true;			// �÷��̾�� Ÿ�� ���� �ִ�.
				break;
			}
		}
		if (not isOnTile) {		// ���� Ÿ�� ���� ���� ������
			player.setFly(true);
			player.setVelocityY(0.f);
		}
	}

}

void GameScene::draw(HDC hdc) const
{
	// ��ũ�Ѹ� ����
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
