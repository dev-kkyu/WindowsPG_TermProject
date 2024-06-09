#include "MonsterObject.h"

#include "ArrowObject.h"

#include <cmath>

bool MonsterObject::isImageLoaded;
std::array<std::vector<MyImage>, 2> MonsterObject::monsterImages;

MonsterObject::MonsterObject(POINT iPos, int idx, SIZE size)
{
	if (not isImageLoaded) {
		monsterImages[0].resize(10);
		for (int i = 0; i < 10; ++i) {
			monsterImages[0][i].Load(L"./Resources/Images/Monster/Stage1/" + std::to_wstring(i + 1) + L".png");
		}
		isImageLoaded = true;
	}

	setPos(iPos);
	imageIndex = idx;
	setSize(size);

	actionPerSecond = 1.25f;
	nowFrameIdxF = 0.f;

	dirX = 1;

	isDead = false;
	deadDirX = 1;
	deadVelocity = 600.f;
}

MonsterObject::~MonsterObject()
{
}

void MonsterObject::update(float elapsedTime)
{
	// 이미지 애니메이션
	nowFrameIdxF += (monsterImages[imageIndex].size() * actionPerSecond) * elapsedTime;
	nowFrameIdxF = std::fmod(nowFrameIdxF, float(monsterImages[imageIndex].size()));

	if (isDead) {
		pos.x += deadDirX * 300.f * elapsedTime;
		pos.y -= deadVelocity * elapsedTime;
		deadVelocity -= 1000.f * elapsedTime;
	}
}

void MonsterObject::draw(HDC hdc, int windowLeft) const
{
	if (1 == dirX)
		monsterImages[imageIndex][int(nowFrameIdxF)].MyDraw(hdc, getObjectRect(), windowLeft, true);
	else
		monsterImages[imageIndex][int(nowFrameIdxF)].MyDraw(hdc, getObjectRect(), windowLeft);

	drawDebug(hdc, windowLeft);
}

void MonsterObject::onHit(const ArrowObject& other)
{
	isDead = true;
	deadDirX = other.dirX;
	deadTime = std::chrono::steady_clock::now();
}

bool MonsterObject::getIsDead() const
{
	return isDead;
}

std::chrono::steady_clock::time_point MonsterObject::getDeadTime() const
{
	return deadTime;
}
