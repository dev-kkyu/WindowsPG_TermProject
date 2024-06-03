#include "PlayerObject.h"

#include <cmath>
#include <limits>

static inline constexpr float my_clamp(float val, float min_val, float max_val)
{
	if (val < min_val)
		return min_val;
	if (val > max_val)
		return max_val;
	return val;
}

PlayerObject::PlayerObject()
{
	pos = { 600, 450 };
	size = { 100, 100 };
	// 이미지 로드
	images["Idle"].resize(4);
	for (int i = 0; i < 4; ++i) {
		images["Idle"][i].Load(L"./Resources/Images/Character/Idle/" + std::to_wstring(i + 1) + L".png");
	}
	images["Walk"].resize(6);
	for (int i = 0; i < 6; ++i) {
		images["Walk"][i].Load(L"./Resources/Images/Character/Walk/" + std::to_wstring(i + 1) + L".png");
	}

	framePerSecond = 8.5f;
	nowFrameIdxF = 0.f;

	animState = "Idle";

	keyState = 0;

	dirX = 1;	// 오른쪽을 보고 있다.

	velocity = 0.f;			// 속도는 오른쪽 혹은 왼쪽
	maxSpeed = 600.f;		// 최대 속도 제한
	acceleration = 1800.f;	// 초당 증가하는 속도
}

PlayerObject::~PlayerObject()
{
}

void PlayerObject::update(float elapsedTime)
{
	if (keyState & MY_KEY_LEFT or keyState & MY_KEY_RIGHT) {
		animState = "Walk";
	}
	else {
		animState = "Idle";
	}
	// 이미지 애니메이션
	nowFrameIdxF += framePerSecond * elapsedTime;
	nowFrameIdxF = std::fmod(nowFrameIdxF, float(images[animState].size()));

	// 좌우 모두 누르고 있거나 안누르고 있을 때는 속도를 감소시킨다.
	if ((keyState & MY_KEY_LEFT and keyState & MY_KEY_RIGHT) or
		(not (keyState & MY_KEY_LEFT) and not (keyState & MY_KEY_RIGHT))) {
		if (std::abs(velocity) >= std::numeric_limits<float>::epsilon()) {
			if (std::abs(velocity) <= 10.f) {
				velocity = 0.f;
			}
			else {
				velocity -= std::copysign(acceleration * elapsedTime, velocity);
			}
		}
	}
	else if (keyState & MY_KEY_LEFT) {
		velocity -= acceleration * elapsedTime;
	}
	else if (keyState & MY_KEY_RIGHT) {
		velocity += acceleration * elapsedTime;
	}
	// velocity가 maxSpeed 이내의 값을 가지도록 조정
	velocity = my_clamp(velocity, -maxSpeed, maxSpeed);
	// velocity에 따른 캐릭터 위치 조정
	pos.x += velocity * elapsedTime;
}

void PlayerObject::draw(HDC hdc)
{
	if (1 == dirX)
		images[animState][int(nowFrameIdxF)].MyDraw(hdc, getObjectRect(), true);
	else
		images[animState][int(nowFrameIdxF)].MyDraw(hdc, getObjectRect());
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
