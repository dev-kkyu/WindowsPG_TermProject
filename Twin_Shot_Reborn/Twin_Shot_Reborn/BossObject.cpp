#include "BossObject.h"

#include <cmath>

BossObject::BossObject()
{
	size = { 400, 300 };

	actionPerSecond = 2.125f;
	nowFrameIdxF = 0.f;

	dirX = 1;

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
}

void BossObject::draw(HDC hdc, int windowLeft) const
{
	POINT myPos = getPosInt();
	chairImage.MyDraw(hdc, RECT{ myPos.x - 53, myPos.y - 302, myPos.x + 53 ,myPos.y - 190 }, windowLeft);
	images[int(nowFrameIdxF)].MyDraw(hdc, RECT{ myPos.x - 50, myPos.y - 290, myPos.x + 94 ,myPos.y - 230 }, windowLeft);
	cloudImage.MyDraw(hdc, RECT{ myPos.x - 210, myPos.y - 350, myPos.x + 210 ,myPos.y + 50 }, windowLeft);

	drawDebug(hdc, windowLeft);
}
