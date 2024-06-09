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
					if (newPos.y < t.getTop() + 25) {	// ����� Ÿ�� ���� �ö���� ���� ����
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

	// ���� ����
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

	// ȭ�� ���ҽ� ȸ��
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

	// ȭ��� Ÿ�� �浹 ó�� -> ��� Ÿ�ϰ� ��� ȭ���� �浹 ó��
	for (const auto& t : tiles) {
		deleteArrows.clear();	// ���� �ڷᱸ���� �����ϰ�
		for (auto itr = player.arrows.begin(); itr != player.arrows.end(); ++itr) {
			if (t.isCollide(*itr)) {
				deleteArrows.emplace_back(itr);	// �浹�� ȭ�� ���� ����
			}
		}
		for (const auto& itr : deleteArrows) {
			arrows.emplace_back(*itr);			// ���� �߰��� �ְ�
			player.arrows.erase(itr);			// �÷��̾�Լ� �����ش�
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
