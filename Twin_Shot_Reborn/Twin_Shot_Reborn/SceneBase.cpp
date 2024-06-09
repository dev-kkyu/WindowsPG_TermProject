#include "SceneBase.h"

#include "Define.h"

SceneBase::SceneBase()
{
}

SceneBase::~SceneBase()
{
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
					if (newPos.y < t.getTop() + 25) {	// 충분히 타일 위에 올라왔을 때만 적용
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

	// 낙하 판정
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

	// 화살 리소스 회수
	std::vector<std::list<ArrowObject>::iterator> deleteArrows;
	for (auto itr = player.arrows.begin(); itr != player.arrows.end(); ++itr) {
		POINT arrowPos = itr->getPosInt();
		SIZE arrowSize = itr->getSize();
		if (arrowPos.x <= -arrowSize.cx / 2 or arrowPos.x >= M_WIDTH + arrowSize.cx / 2) {
			deleteArrows.emplace_back(itr);
		}
	}
	for (const auto& itr : deleteArrows) {
		player.arrows.erase(itr);
	}

	// 화살과 타일 충돌 처리 -> 모든 타일과 모든 화살의 충돌 처리
	for (const auto& t : tiles) {
		deleteArrows.clear();	// 먼저 자료구조를 리셋하고
		for (auto itr = player.arrows.begin(); itr != player.arrows.end(); ++itr) {
			if (t.isCollide(*itr)) {
				deleteArrows.emplace_back(itr);	// 충돌된 화살 따로 관리
			}
		}
		for (const auto& itr : deleteArrows) {
			arrows.emplace_back(*itr);			// 씬에 추가해 주고
			player.arrows.erase(itr);			// 플레이어에게서 지워준다
		}
	}
}

void SceneBase::processWindowMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
		break;
	default:
		MessageBoxA(hWnd, "Wrong Window Message On SceneBase", nullptr, MB_OK);
		break;
	}
}
