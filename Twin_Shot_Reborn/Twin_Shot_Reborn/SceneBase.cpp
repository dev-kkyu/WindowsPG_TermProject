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
	cloudPosXf = W_WIDTH / 2.f;		// 구름 초기값 중앙

	// 공용으로 사용하는 점수 뒷판 이미지
	scoreBackground.Load(L"./Resources/Images/Character/Score.png");

	LOGFONTA logFont{};
	logFont.lfHeight = 33;
	logFont.lfWeight = FW_BOLD;
	//strcpy_s(logFont.lfFaceName, "돋움");

	scoreFont = CreateFontIndirectA(&logFont);
}

SceneBase::~SceneBase()
{
	DeleteObject(scoreFont);
}

void SceneBase::update(float elapsedTime)
{
	const POINTFLOAT befPos = player.getPos();	// 업데이트 전 플레이어 위치

	player.update(elapsedTime);

	bool flagVX = false;		// X방향 가속도를 초기화 할 것인지
	// 좌우 충돌
	POINTFLOAT newPos = player.getPos();
	for (const auto& t : tiles) {
		if (t.isCollide(player)) {	// 플레이어와 충돌시
			if (t.getBottom() >= player.getBottom()) {	// 상승시 충돌 범위를 줄여준다
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
					if (newPos.y < t.getTop() + 25) {	// 충분히 타일 위에 올라왔을 때만 적용
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
	// 상하 충돌 (씬에 존재하는 화살에 대하여)
	for (const auto& arrow : arrows) {
		if (arrow.isCollide(player)) {	// 플레이어와 충돌시
			if (arrow.getTop() < player.getBottom() and arrow.getBottom() > player.getTop()) {	// 상하에 대하여 충돌이면
				if (newPos.y > befPos.y) {					// 낙하 중에만 적용한다. (상승중에는 충돌X)
					if (newPos.y < arrow.getTop() + 10) {	// 충분히 타일 위에 올라왔을 때만 적용
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

	// 낙하 판정
	if (not player.getFly()) {		// 점프 중이 아닐때
		TileObject tempObj{ POINT{int(newPos.x), int(newPos.y + 10)} };		// 임시 객체 만들기
		tempObj.setSize({ 100, 100 });		// 플레이어 사이즈로 조정

		bool isOnTile = false;
		for (const auto& t : tiles) {
			if (t.isCollide(tempObj)) {		// 타일과 임시 객체 충돌시
				if (newPos.y <= t.getTop()) {
					isOnTile = true;			// 플레이어는 타일 위에 있다.
					break;
				}
			}
		}
		for (const auto& arrow : arrows) {
			if (arrow.isCollide(tempObj)) {	// 화살과 임시 객체 충돌시
				if (newPos.y <= (arrow.getTop() + arrow.getBottom()) / 2.f) {
					isOnTile = true;			// 플레이어는 타일(화살) 위에 있다.
					break;
				}
			}
		}
		if (not isOnTile) {		// 현재 타일 위에 있지 않을때
			player.setFly(true);
			player.setVelocityY(0.f);
		}
	}

	// 아이템 업데이트 (애니메이션)
	for (auto& item : items)
		item.update(elapsedTime);

	// 아이템 낙하
	for (auto& i : items) {
		const POINTFLOAT bef_pos = i.getPos();
		POINTFLOAT newPos = bef_pos;
		newPos.y += elapsedTime * 300.f;
		for (const auto& t : tiles) {
			if (i.isCollide(t)) {			// 타일과 아이템 충돌
				newPos.y = bef_pos.y;
				break;
			}
		}
		i.setPos(newPos);
	}

	// 아이템 충돌 처리
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

	// 화살 리소스 관리
	std::vector<std::list<ArrowObject>::iterator> deleteArrows;
	// 플레이어 화살 리소스 회수
	deleteArrows.clear();
	for (auto itr = player.arrows.begin(); itr != player.arrows.end(); ++itr) {
		POINT arrowPos = itr->getPosInt();
		SIZE arrowSize = itr->getSize();
		if (arrowPos.x <= -arrowSize.cx / 2 or arrowPos.x >= M_WIDTH + arrowSize.cx / 2) {
			deleteArrows.emplace_back(itr);							// 맵 밖으로 나가면 제거
		}
	}
	for (const auto& itr : deleteArrows) {
		player.arrows.erase(itr);
	}
	// 씬 화살 리소스 회수
	deleteArrows.clear();
	auto nowTime = std::chrono::steady_clock::now();
	for (auto itr = arrows.begin(); itr != arrows.end(); ++itr) {
		auto hitTime = itr->getHitTime();
		if (hitTime + std::chrono::seconds{ 6 } <= nowTime) {		// 벽에서 6초 뒤 제거
			deleteArrows.emplace_back(itr);
		}
	}
	for (const auto& itr : deleteArrows) {
		arrows.erase(itr);
	}

	// 화살과 타일 충돌 처리 -> 모든 타일과 모든 화살의 충돌 처리
	for (const auto& t : tiles) {
		deleteArrows.clear();	// 먼저 자료구조를 리셋하고
		for (auto itr = player.arrows.begin(); itr != player.arrows.end(); ++itr) {
			if (t.isCollide(*itr)) {
				deleteArrows.emplace_back(itr);	// 충돌된 화살 따로 관리
				MySound::getInstance().playShootWallSound();
			}
		}
		for (const auto& itr : deleteArrows) {
			itr->onHit();						// 충돌 시간 설정해 주고
			arrows.emplace_back(*itr);			// 씬에 추가해 주고
			player.arrows.erase(itr);			// 플레이어에게서 지워준다
		}
	}

	// 배경 구름 이동
	cloudPosXf -= 100.f * elapsedTime;
	if (cloudPosXf < 0.f) {
		cloudPosXf += W_WIDTH;
	}

}

void SceneBase::draw(HDC hdc) const
{
	// 스크롤링 적용
	int windowLeft = player.getPosInt().x - W_WIDTH / 2;
	windowLeft = my_clamp(windowLeft, 0, M_WIDTH - W_WIDTH);

	background.MyDraw(hdc, RECT{ 0, 0, W_WIDTH, W_HEIGHT });

	// cloudPosXf 는 1200 ~ 0
	{	// 정석적인 방법 (dstRect와 srcRect 이용)
		float value = 1.f - cloudPosXf / float(W_WIDTH);
		int imgWidth = cloud.getWidth();
		int imgHeight = cloud.getHeight();
		cloud.MyDraw(hdc, RECT{ 0, 0, int(cloudPosXf), W_HEIGHT }, RECT{ int(value * imgWidth), 0, imgWidth, imgHeight }, false, false, 0x7f);
		cloud.MyDraw(hdc, RECT{ int(cloudPosXf), 0, W_WIDTH, W_HEIGHT }, RECT{ 0, 0, int(value * imgWidth), imgHeight }, false, false, 0x7f);
	}
	//{	// 좋진 않지만 잘 되는 방법 (화면 바깥으로 많이 그린다)
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

	// 점수 뒷판 그리기
	RECT rc{ 970, 837, 1180, 885 };
	scoreBackground.MyDraw(hdc, rc);

	// 플레이어 점수 화면에 그려주기
	SetTextColor(hdc, RGB(243, 97, 220));
	HFONT oldFont = (HFONT)SelectObject(hdc, scoreFont);
	std::string str = std::to_string(playerScore);
	rc.right -= 20;
	DrawTextA(hdc, str.c_str(), int(str.size()), &rc, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
	SelectObject(hdc, oldFont);
	SetTextColor(hdc, 0);		// 원상복구
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
