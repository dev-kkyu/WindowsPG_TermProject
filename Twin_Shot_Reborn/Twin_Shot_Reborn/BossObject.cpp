#include "BossObject.h"

#include "PlayerObject.h"

#include <cmath>

BossObject::BossObject()
{
	size = { 400, 290 };

	actionPerSecond = 2.125f;
	nowFrameIdxF = 0.f;

	hp = 20;

	lastFireTime = std::chrono::steady_clock::now();
	lastHitTime = lastFireTime - std::chrono::seconds(1);

	cloudImage.Load(L"./Resources/Images/Monster/Boss/cloud.png");
	chairImage.Load(L"./Resources/Images/Monster/Boss/chair.png");
	images.resize(5);
	for (int i = 0; i < 5; ++i) {
		images[i].Load(L"./Resources/Images/Monster/Boss/" + std::to_wstring(i + 1) + L".png");
	}
}

BossObject::~BossObject()
{
}

void BossObject::update(float elapsedTime)
{
	// �̹��� �ִϸ��̼�
	nowFrameIdxF += (images.size() * actionPerSecond) * elapsedTime;
	nowFrameIdxF = std::fmod(nowFrameIdxF, float(images.size()));

	// ���� ����
	if (targetPlayer) {
		auto nowTime = std::chrono::steady_clock::now();
		if (lastFireTime + std::chrono::milliseconds{ 2000 } <= nowTime) {	// ���� �ð�����
			lastFireTime = nowTime;

			POINTFLOAT playerPos = targetPlayer->getPos();
			POINTFLOAT myPos = getPos();
			fires.emplace_back(getPosInt(), playerPos.x - myPos.x, playerPos.y - myPos.y);	// �÷��̾�� ����
		}
	}

	// �� ���� ������Ʈ
	for (auto& fire : fires)
		fire.update(elapsedTime);
}

void BossObject::draw(HDC hdc, int windowLeft) const
{
	// �� ���� �׷��ֱ�
	for (const auto& fire : fires)
		fire.draw(hdc, windowLeft);

	// �ǰݽ� ���
	bool isDraw = true;
	auto nowTime = std::chrono::steady_clock::now();
	if (lastHitTime + std::chrono::milliseconds{ 1000 } > nowTime) {	// ���ݹް� 1�ʵ���
		auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(nowTime - lastHitTime).count();
		if ((ms / 100) & 1)		// 100ms���� �������ش�
			isDraw = false;
	}
	if (isDraw) {
		POINT myPos = getPosInt();
		myPos.y -= 150;
		chairImage.MyDraw(hdc, RECT{ myPos.x - 53, myPos.y - 152, myPos.x + 53 ,myPos.y - 40 }, windowLeft);
		images[int(nowFrameIdxF)].MyDraw(hdc, RECT{ myPos.x - 50, myPos.y - 140, myPos.x + 94 ,myPos.y - 80 }, windowLeft);
		cloudImage.MyDraw(hdc, RECT{ myPos.x - 210, myPos.y - 200, myPos.x + 210 ,myPos.y + 200 }, windowLeft);
	}

	drawDebug(hdc, windowLeft);
}

void BossObject::setTargetPlayer(const PlayerObject& target)
{
	targetPlayer = &target;
}

void BossObject::onHit()
{
	--hp;

	lastHitTime = std::chrono::steady_clock::now();

}
