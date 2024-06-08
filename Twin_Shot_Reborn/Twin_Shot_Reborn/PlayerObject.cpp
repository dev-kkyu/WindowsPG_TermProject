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
	images["Walk"].resize(7);
	for (int i = 0; i < 7; ++i) {
		images["Walk"][i].Load(L"./Resources/Images/Character/Walk/" + std::to_wstring(i + 1) + L".png");
	}
	images["Jump"].resize(2);
	for (int i = 0; i < 2; ++i) {
		images["Jump"][i].Load(L"./Resources/Images/Character/Jump/" + std::to_wstring(i + 1) + L".png");
	}
	images["Fall"].resize(2);
	for (int i = 0; i < 2; ++i) {
		images["Fall"][i].Load(L"./Resources/Images/Character/Fall/" + std::to_wstring(i + 1) + L".png");
	}

	actionPerSecond = 2.125f;
	nowFrameIdxF = 0.f;

	animState = "Idle";

	keyState = 0;

	dirX = 1;	// �������� ���� �ִ�.

	velocity.x = 0.f;			// ������ Ȥ�� ������ �ӵ�
	maxSpeed.x = 600.f;			// �ִ� x �ӵ� ����
	acceleration.x = 1800.f;	// �ʴ� �����ϴ� x �ӵ�

	isFly = false;				// ���߿� �� �ִ��� ����
	velocity.y = 0.f;			// ���� �ӵ�
	maxSpeed.y = 750.f;			// �ִ� ���� �ӵ� ����
	acceleration.y = 1800.f;	// �ʴ� �����ϴ� y �ӵ� (�Ʒ� �������θ� �ۿ��Ѵ�)
}

PlayerObject::~PlayerObject()
{
}

void PlayerObject::update(float elapsedTime)
{
	// �ִϸ��̼� ���ϱ�
	if (isFly) {
		if (velocity.y > 0.f)
			animState = "Jump";
		else
			animState = "Fall";
	}
	else if (keyState & MY_KEY_LEFT or keyState & MY_KEY_RIGHT) {
		animState = "Walk";
	}
	else {
		animState = "Idle";
	}
	// �̹��� �ִϸ��̼�
	nowFrameIdxF += (images[animState].size() * actionPerSecond) * elapsedTime;
	nowFrameIdxF = std::fmod(nowFrameIdxF, float(images[animState].size()));

	// �¿� ��� ������ �ְų� �ȴ����� ���� ���� �ӵ��� ���ҽ�Ų��.
	if ((keyState & MY_KEY_LEFT and keyState & MY_KEY_RIGHT) or
		(not (keyState & MY_KEY_LEFT) and not (keyState & MY_KEY_RIGHT))) {
		if (std::abs(velocity.x) >= std::numeric_limits<float>::epsilon()) {
			if (std::abs(velocity.x) <= 10.f) {
				velocity.x = 0.f;
			}
			else {
				velocity.x -= std::copysign(acceleration.x * elapsedTime, velocity.x);
			}
		}
	}
	else if (keyState & MY_KEY_LEFT) {
		velocity.x -= acceleration.x * elapsedTime;
	}
	else if (keyState & MY_KEY_RIGHT) {
		velocity.x += acceleration.x * elapsedTime;
	}
	// velocity�� maxSpeed �̳��� ���� �������� ����
	velocity.x = my_clamp(velocity.x, -maxSpeed.x, maxSpeed.x);
	// velocity�� ���� ĳ���� ��ġ ����
	pos.x += velocity.x * elapsedTime;

	// ���� ���̸�
	if (isFly) {
		pos.y -= velocity.y * elapsedTime;		// velocity�� ����� ���� �ö󰡾� �Ѵ� (window ��ǥ��)
		// velocity�� maxSpeed �̳��� ���� �������� ����
		velocity.y -= acceleration.y * elapsedTime;
		// velocity�� ���� ĳ���� ��ġ ����
		velocity.y = my_clamp(velocity.y, -maxSpeed.y, maxSpeed.y);
	}
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
			// ���� �����ش�
			if (not isFly) {
				isFly = true;
				velocity.y = maxSpeed.y;
			}
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

void PlayerObject::setFly(bool bFly)
{
	isFly = bFly;
}

bool PlayerObject::getFly() const
{
	return isFly;
}
