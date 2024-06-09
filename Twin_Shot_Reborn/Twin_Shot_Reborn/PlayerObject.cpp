#include "PlayerObject.h"

#include <cmath>
#include <limits>

template <class T>
static inline constexpr T my_clamp(T val, T min_val, T max_val)
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
	images["Shoot"].resize(7);
	for (int i = 0; i < 7; ++i) {
		images["Shoot"][i].Load(L"./Resources/Images/Character/Shoot/" + std::to_wstring(i + 1) + L".png");
	}
	images["Hit"].resize(1);
	images["Hit"][0].Load(L"./Resources/Images/Character/Hit.png");

	actionPerSecond = 2.125f;
	nowFrameIdxF = 0.f;

	animState = "Idle";

	keyState = 0;

	dirX = 1;	// 오른쪽을 보고 있다.

	velocity.x = 0.f;			// 오른쪽 혹은 왼쪽의 속도
	maxSpeed.x = 600.f;			// 최대 x 속도 제한
	acceleration.x = 1800.f;	// 초당 증가하는 x 속도

	velocity.y = 0.f;			// 낙하 속도
	maxSpeed.y = 750.f;			// 최대 낙하 속도 제한
	acceleration.y = 1800.f;	// 초당 감소하는 y 속도 (아래 방향으로만 작용한다)

	isFly = false;				// 공중에 떠 있는지 여부
	isShootReady = false;

	hp = 3;
}

PlayerObject::~PlayerObject()
{
}

void PlayerObject::update(float elapsedTime)
{
	// 화살 오브젝트 업데이트
	for (auto& arrow : arrows)
		arrow.update(elapsedTime);

	if (isHit) {
		pos.y -= velocity.y * elapsedTime;		// velocity가 양수면 위로 올라가야 한다 (window 좌표계)
		// velocity가 maxSpeed 이내의 값을 가지도록 조정
		velocity.y -= acceleration.y * elapsedTime;
		// velocity에 따른 캐릭터 위치 조정
		velocity.y = my_clamp(velocity.y, -maxSpeed.y, maxSpeed.y);

		pos.x += 600.f * elapsedTime;

		return;
	}

	// 애니메이션 정하기
	if ("Shoot" == animState) {
		nowFrameIdxF += (images[animState].size() * actionPerSecond * 1.5f) * elapsedTime;
		if (nowFrameIdxF >= 3.f) {				// 5번째 그림이 재생될 때
			if (isShootReady) {					// 아직 실제로 발사하지 않은 상태이면
				POINT spawnPos = getPosInt();
				spawnPos.y -= 23;
				arrows.emplace_back(spawnPos, dirX);	// 발사
				isShootReady = false;
			}
		}
		if (nowFrameIdxF >= images[animState].size()) {	// 한바퀴를 다 돌면 애니메이션 종료
			animState = "Idle";
			nowFrameIdxF = 0.f;
		}
	}
	else {
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
		// 이미지 애니메이션
		nowFrameIdxF += (images[animState].size() * actionPerSecond) * elapsedTime;
		nowFrameIdxF = std::fmod(nowFrameIdxF, float(images[animState].size()));
	}

	// 좌우 모두 누르고 있거나 안누르고 있을 때는 속도를 감소시킨다.
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
	// velocity가 maxSpeed 이내의 값을 가지도록 조정
	velocity.x = my_clamp(velocity.x, -maxSpeed.x, maxSpeed.x);
	// velocity에 따른 캐릭터 위치 조정
	pos.x += velocity.x * elapsedTime;

	// 점프 중이면
	if (isFly) {
		pos.y -= velocity.y * elapsedTime;		// velocity가 양수면 위로 올라가야 한다 (window 좌표계)
		// velocity가 maxSpeed 이내의 값을 가지도록 조정
		velocity.y -= acceleration.y * elapsedTime;
		// velocity에 따른 캐릭터 위치 조정
		velocity.y = my_clamp(velocity.y, -maxSpeed.y, maxSpeed.y);
	}
}

void PlayerObject::draw(HDC hdc, int windowLeft) const
{
	if (1 == dirX)
		images.at(animState)[int(nowFrameIdxF)].MyDraw(hdc, getObjectRect(), windowLeft, true);
	else
		images.at(animState)[int(nowFrameIdxF)].MyDraw(hdc, getObjectRect(), windowLeft);

	// 화살 오브젝트 그리기
	for (auto& arrow : arrows)
		arrow.draw(hdc, windowLeft);

	drawDebug(hdc, windowLeft);
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
			// 점프 시켜준다
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
			fireArrow();
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

void PlayerObject::setVelocityX(float valX)
{
	velocity.x = valX;
}

void PlayerObject::setVelocityY(float valY)
{
	velocity.y = valY;
}

void PlayerObject::fireArrow()
{
	if ("Shoot" != animState) {		// 현재 발사중이 아닐때만 발동
		animState = "Shoot";
		nowFrameIdxF = 0.f;

		isShootReady = true;
	}
}

void PlayerObject::onHit()
{
	isHit = true;
	animState = "Hit";
	nowFrameIdxF = 0.f;
	velocity.y = maxSpeed.y;
	velocity.x = 0.f;

	--hp;
}

void PlayerObject::setHit(bool hit)
{
	isHit = hit;
}

bool PlayerObject::getHit() const
{
	return isHit;
}
