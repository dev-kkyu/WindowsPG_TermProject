#include "SceneBase.h"

#include "Define.h"

#include "MySound.h"

int SceneBase::playerScore = 0;

template <class T>
static inline constexpr T my_clamp(T val, T min_val, T max_val)
{
	if (val < min_val)
		return min_val;
	if (val > max_val)
		return max_val;
	return val;
}

SceneBase::SceneBase()
{
	cloudPosXf = W_WIDTH / 2.f;		// ���� �ʱⰪ �߾�

	// �������� ����ϴ� ���� ���� �̹���
	scoreBackground.Load(L"./Resources/Images/Character/Score.png");

	LOGFONTA logFont{};
	logFont.lfHeight = 33;
	logFont.lfWeight = FW_BOLD;
	//strcpy_s(logFont.lfFaceName, "����");

	scoreFont = CreateFontIndirectA(&logFont);
}

SceneBase::~SceneBase()
{
	DeleteObject(scoreFont);
}

void SceneBase::update(float elapsedTime)
{
	const POINTFLOAT befPos = player.getPos();	// ������Ʈ �� �÷��̾� ��ġ

	player.update(elapsedTime);

	bool flagVX = false;		// X���� ���ӵ��� �ʱ�ȭ �� ������
	// �¿� �浹
	POINTFLOAT newPos = player.getPos();
	for (const auto& t : tiles) {
		if (t.isCollide(player)) {	// �÷��̾�� �浹��
			if (t.getBottom() >= player.getBottom()) {	// ��½� �浹 ������ �ٿ��ش�
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
					if (newPos.y < t.getTop() + 25) {	// ����� Ÿ�� ���� �ö���� ���� ����
						newPos.y = static_cast<float>(t.getTop());
						player.setPos(newPos);
						player.setFly(false);
						player.setHit(false);
						flagVX = false;
						break;
					}
				}
			}
		}
	}
	// ���� �浹 (���� �����ϴ� ȭ�쿡 ���Ͽ�)
	for (const auto& arrow : arrows) {
		if (arrow.isCollide(player)) {	// �÷��̾�� �浹��
			if (arrow.getTop() < player.getBottom() and arrow.getBottom() > player.getTop()) {	// ���Ͽ� ���Ͽ� �浹�̸�
				if (newPos.y > befPos.y) {					// ���� �߿��� �����Ѵ�. (����߿��� �浹X)
					if (newPos.y < arrow.getTop() + 10) {	// ����� Ÿ�� ���� �ö���� ���� ����
						newPos.y = static_cast<float>(arrow.getTop() + arrow.getBottom()) / 2.f;
						player.setPos(newPos);
						player.setFly(false);
						player.setHit(false);
						break;
					}
				}
			}
		}
	}

	if (flagVX)
		player.setVelocityX(0.f);

	// ���� ����
	if (not player.getFly()) {		// ���� ���� �ƴҶ�
		TileObject tempObj{ POINT{int(newPos.x), int(newPos.y + 10)} };		// �ӽ� ��ü �����
		tempObj.setSize({ 100, 100 });		// �÷��̾� ������� ����

		bool isOnTile = false;
		for (const auto& t : tiles) {
			if (t.isCollide(tempObj)) {		// Ÿ�ϰ� �ӽ� ��ü �浹��
				if (newPos.y <= t.getTop()) {
					isOnTile = true;			// �÷��̾�� Ÿ�� ���� �ִ�.
					break;
				}
			}
		}
		for (const auto& arrow : arrows) {
			if (arrow.isCollide(tempObj)) {	// ȭ��� �ӽ� ��ü �浹��
				if (newPos.y <= (arrow.getTop() + arrow.getBottom()) / 2.f) {
					isOnTile = true;			// �÷��̾�� Ÿ��(ȭ��) ���� �ִ�.
					break;
				}
			}
		}
		if (not isOnTile) {		// ���� Ÿ�� ���� ���� ������
			player.setFly(true);
			player.setVelocityY(0.f);
		}
	}

	// ������ ������Ʈ (�ִϸ��̼�)
	for (auto& item : items)
		item.update(elapsedTime);

	// ������ ����
	for (auto& i : items) {
		const POINTFLOAT bef_pos = i.getPos();
		POINTFLOAT newPos = bef_pos;
		newPos.y += elapsedTime * 300.f;
		for (const auto& t : tiles) {
			if (i.isCollide(t)) {			// Ÿ�ϰ� ������ �浹
				newPos.y = bef_pos.y;
				break;
			}
		}
		i.setPos(newPos);
	}

	// ������ �浹 ó��
	std::vector<std::list<ItemObject>::iterator> deleteItems;
	for (auto itr = items.begin(); itr != items.end(); ++itr) {
		if (itr->isCollide(player)) {
			auto type = itr->getItemType();
			switch (type)
			{
			case ItemObject::HP:
				player.onHpItem();
				MySound::getInstance().playItemSound();
				break;
			case ItemObject::S_COIN:
				playerScore += 50;
				MySound::getInstance().playSilverCoinSound();
				break;
			case ItemObject::G_COIN:
				playerScore += 100;
				MySound::getInstance().playGoldCoinSound();
				break;
			}
			deleteItems.emplace_back(itr);
		}
	}

	for (const auto& itr : deleteItems) {
		items.erase(itr);
	}

	// ȭ�� ���ҽ� ����
	std::vector<std::list<ArrowObject>::iterator> deleteArrows;
	// �÷��̾� ȭ�� ���ҽ� ȸ��
	deleteArrows.clear();
	for (auto itr = player.arrows.begin(); itr != player.arrows.end(); ++itr) {
		POINT arrowPos = itr->getPosInt();
		SIZE arrowSize = itr->getSize();
		if (arrowPos.x <= -arrowSize.cx / 2 or arrowPos.x >= M_WIDTH + arrowSize.cx / 2) {
			deleteArrows.emplace_back(itr);							// �� ������ ������ ����
		}
	}
	for (const auto& itr : deleteArrows) {
		player.arrows.erase(itr);
	}
	// �� ȭ�� ���ҽ� ȸ��
	deleteArrows.clear();
	auto nowTime = std::chrono::steady_clock::now();
	for (auto itr = arrows.begin(); itr != arrows.end(); ++itr) {
		auto hitTime = itr->getHitTime();
		if (hitTime + std::chrono::seconds{ 6 } <= nowTime) {		// ������ 6�� �� ����
			deleteArrows.emplace_back(itr);
		}
	}
	for (const auto& itr : deleteArrows) {
		arrows.erase(itr);
	}

	// ȭ��� Ÿ�� �浹 ó�� -> ��� Ÿ�ϰ� ��� ȭ���� �浹 ó��
	for (const auto& t : tiles) {
		deleteArrows.clear();	// ���� �ڷᱸ���� �����ϰ�
		for (auto itr = player.arrows.begin(); itr != player.arrows.end(); ++itr) {
			if (t.isCollide(*itr)) {
				deleteArrows.emplace_back(itr);	// �浹�� ȭ�� ���� ����
				MySound::getInstance().playShootWallSound();
			}
		}
		for (const auto& itr : deleteArrows) {
			itr->onHit();						// �浹 �ð� ������ �ְ�
			arrows.emplace_back(*itr);			// ���� �߰��� �ְ�
			player.arrows.erase(itr);			// �÷��̾�Լ� �����ش�
		}
	}

	// ��� ���� �̵�
	cloudPosXf -= 100.f * elapsedTime;
	if (cloudPosXf < 0.f) {
		cloudPosXf += W_WIDTH;
	}

}

void SceneBase::draw(HDC hdc) const
{
	// ��ũ�Ѹ� ����
	int windowLeft = player.getPosInt().x - W_WIDTH / 2;
	windowLeft = my_clamp(windowLeft, 0, M_WIDTH - W_WIDTH);

	background.MyDraw(hdc, RECT{ 0, 0, W_WIDTH, W_HEIGHT });

	// cloudPosXf �� 1200 ~ 0
	{	// �������� ��� (dstRect�� srcRect �̿�)
		float value = 1.f - cloudPosXf / float(W_WIDTH);
		int imgWidth = cloud.getWidth();
		int imgHeight = cloud.getHeight();
		cloud.MyDraw(hdc, RECT{ 0, 0, int(cloudPosXf), W_HEIGHT }, RECT{ int(value * imgWidth), 0, imgWidth, imgHeight }, false, false, 0x7f);
		cloud.MyDraw(hdc, RECT{ int(cloudPosXf), 0, W_WIDTH, W_HEIGHT }, RECT{ 0, 0, int(value * imgWidth), imgHeight }, false, false, 0x7f);
	}
	//{	// ���� ������ �� �Ǵ� ��� (ȭ�� �ٱ����� ���� �׸���)
	//	int pivot = W_WIDTH - int(cloudPosXf);
	//	cloud.MyDraw(hdc, RECT{ -pivot, 0, W_WIDTH - pivot, W_HEIGHT });
	//	cloud.MyDraw(hdc, RECT{ int(cloudPosXf), 0, W_WIDTH + int(cloudPosXf), W_HEIGHT });
	//}

	for (const auto& tile : tiles)
		tile.draw(hdc, windowLeft);

	for (const auto& tile : nonBlockTiles)
		tile.draw(hdc, windowLeft);

	for (const auto& item : items)
		item.draw(hdc, windowLeft);

	player.draw(hdc, windowLeft);

	for (const auto& arrow : arrows)
		arrow.draw(hdc, windowLeft);

	// ���� ���� �׸���
	RECT rc{ 970, 837, 1180, 885 };
	scoreBackground.MyDraw(hdc, rc);

	// �÷��̾� ���� ȭ�鿡 �׷��ֱ�
	SetTextColor(hdc, RGB(243, 97, 220));
	HFONT oldFont = (HFONT)SelectObject(hdc, scoreFont);
	std::string str = std::to_string(playerScore);
	rc.right -= 20;
	DrawTextA(hdc, str.c_str(), int(str.size()), &rc, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
	SelectObject(hdc, oldFont);
	SetTextColor(hdc, 0);		// ���󺹱�
}

bool SceneBase::getPlayerDead() const
{
	return player.getIsDead();
}

void SceneBase::processWindowMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
		MessageBoxA(hWnd, "Wrong Window Message On SceneBase", nullptr, MB_OK);
		break;
	}
}

void SceneBase::setPlayerScore(int score)
{
	playerScore = score;
}

int SceneBase::getPlayerScore()
{
	return playerScore;
}
