#pragma once

#define MY_KEY_UP		0x01
#define MY_KEY_DOWN		0x02
#define MY_KEY_LEFT		0x04
#define MY_KEY_RIGHT	0x08
#define MY_KEY_SPACE	0x10

#include "GameObject.h"

#include <vector>
#include <unordered_map>

#include "MyImage.h"

class PlayerObject : public GameObject
{
private:
	std::unordered_map<std::string, std::vector<MyImage>> images;
	float framePerSecond;	// 초당 몇장 돌릴건지
	float nowFrameIdxF;		// 현재 프레임 인덱스 (int로 변환 후 사용)

	std::string animState;

	unsigned int keyState;

	int dirX;

	POINTFLOAT velocity;		// x, y 방향 속도
	POINTFLOAT maxSpeed;		// x, y 방향 최대 속도
	POINTFLOAT acceleration;	// x, y(중력) 방향 가속도

public:
	PlayerObject();
	virtual ~PlayerObject();

	virtual void update(float elapsedTime) override;
	virtual void draw(HDC hdc) override;

	void sendKeyMsg(UINT message, WPARAM wParam);
};

