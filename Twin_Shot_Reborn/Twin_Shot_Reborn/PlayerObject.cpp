#include "PlayerObject.h"

#include <cmath>

PlayerObject::PlayerObject()
{
	pos = { 600, 450 };
	size = { 100, 100 };
	// 이미지 로드
	images["Idle"].resize(4);
	for (int i = 0; i < 4; ++i) {
		images["Idle"][i].Load(L"./Resources/Images/Character/Idle/" + std::to_wstring(i + 1) + L".png");
	}

	framePerSecond = 8.5f;
	nowFrameIdxF = 0.f;
}

PlayerObject::~PlayerObject()
{
}

void PlayerObject::update(float elapsedTime)
{
	nowFrameIdxF += framePerSecond * elapsedTime;
	nowFrameIdxF = fmod(nowFrameIdxF, float(images["Idle"].size()));
}

void PlayerObject::draw(HDC hdc)
{
	images["Idle"][int(nowFrameIdxF)].MyDraw(hdc, getObjectRect());
}
