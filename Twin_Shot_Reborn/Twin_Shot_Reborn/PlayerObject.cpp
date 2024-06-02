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

	keyState = 0;

	dirX = 1;	// 오른쪽을 보고 있다.
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
	if (1 == dirX)
		images["Idle"][int(nowFrameIdxF)].MyDraw(hdc, getObjectRect(), true);
	else
		images["Idle"][int(nowFrameIdxF)].MyDraw(hdc, getObjectRect());
}

void PlayerObject::sendKeyMsg(UINT message, WPARAM wParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_UP:
			keyState |= MY_KEY_UP;
			break;
		case VK_DOWN:
			keyState |= MY_KEY_DOWN;
			break;
		case VK_LEFT:
			keyState |= MY_KEY_LEFT;
			dirX = -1;
			break;
		case VK_RIGHT:
			keyState |= MY_KEY_RIGHT;
			dirX = 1;
			break;
		case VK_SPACE:
			keyState |= MY_KEY_SPACE;
			break;
		}
		break;
	case WM_KEYUP:
		switch (wParam)
		{
		case VK_UP:
			keyState &= ~MY_KEY_UP;
			break;
		case VK_DOWN:
			keyState &= ~MY_KEY_DOWN;
			break;
		case VK_LEFT:
			keyState &= ~MY_KEY_LEFT;
			break;
		case VK_RIGHT:
			keyState &= ~MY_KEY_RIGHT;
			break;
		case VK_SPACE:
			keyState &= ~MY_KEY_SPACE;
			break;
		}
		break;
	}
}
