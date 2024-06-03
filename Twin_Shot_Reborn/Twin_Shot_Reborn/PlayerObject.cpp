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
	// �̹��� �ε�
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

	dirX = 1;	// �������� ���� �ִ�.

	velocity = 0.f;			// �ӵ��� ������ Ȥ�� ����
	maxSpeed = 600.f;		// �ִ� �ӵ� ����
	acceleration = 1800.f;	// �ʴ� �����ϴ� �ӵ�
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
	// �̹��� �ִϸ��̼�
	nowFrameIdxF += framePerSecond * elapsedTime;
	nowFrameIdxF = std::fmod(nowFrameIdxF, float(images[animState].size()));

	// �¿� ��� ������ �ְų� �ȴ����� ���� ���� �ӵ��� ���ҽ�Ų��.
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
	// velocity�� maxSpeed �̳��� ���� �������� ����
	velocity = my_clamp(velocity, -maxSpeed, maxSpeed);
	// velocity�� ���� ĳ���� ��ġ ����
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
