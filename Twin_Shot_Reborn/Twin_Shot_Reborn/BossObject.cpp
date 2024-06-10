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

	isDead = false;
	deadVelocity = 600.f;

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
	// 이미지 애니메이션
	nowFrameIdxF += (images.size() * actionPerSecond) * elapsedTime;
	nowFrameIdxF = std::fmod(nowFrameIdxF, float(images.size()));

	if (not isDead) {
		auto nowTime = std::chrono::steady_clock::now();

		// 죽음 판정
		if (hp <= 0) {
			isDead = true;
			deadTime = nowTime;
		}
		// 공격 패턴
		else if (targetPlayer) {
			if (lastFireTime + std::chrono::milliseconds{ 2000 } <= nowTime) {	// 일정 시간마다
				lastFireTime = nowTime;

				POINTFLOAT playerPos = targetPlayer->getPos();
				POINTFLOAT myPos = getPos();
				fires.emplace_back(getPosInt(), playerPos.x - myPos.x, playerPos.y - myPos.y);	// 플레이어에게 공격
			}
		}
	}
	else {	// 죽었을 시, 낙하
		pos.x += 300.f * elapsedTime;
		pos.y -= deadVelocity * elapsedTime;
		deadVelocity -= 1000.f * elapsedTime;
	}

	// 불 공격 업데이트
	for (auto& fire : fires)
		fire.update(elapsedTime);
}

void BossObject::draw(HDC hdc, int windowLeft) const
{
	// 불 공격 그려주기
	for (const auto& fire : fires)
		fire.draw(hdc, windowLeft);

	// 피격시 모션
	bool isDraw = true;
	auto nowTime = std::chrono::steady_clock::now();
	if (lastHitTime + std::chrono::milliseconds{ 1000 } > nowTime) {	// 공격받고 1초동안
		auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(nowTime - lastHitTime).count();
		if ((ms / 100) & 1)		// 100ms마다 깜빡여준다
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
	if (not isDead) {
		--hp;

		lastHitTime = std::chrono::steady_clock::now();
	}
}

bool BossObject::getIsOut() const
{
	if (isDead) {	// 죽고 나서 3초 뒤
		if (deadTime + std::chrono::seconds{ 3 } <= std::chrono::steady_clock::now())
			return true;
	}
	return false;
}
