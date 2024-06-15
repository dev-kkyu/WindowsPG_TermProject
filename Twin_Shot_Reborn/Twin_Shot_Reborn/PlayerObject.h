#pragma once

#define MY_KEY_UP		0x01
#define MY_KEY_DOWN		0x02
#define MY_KEY_LEFT		0x04
#define MY_KEY_RIGHT	0x08
#define MY_KEY_SPACE	0x10

#include "GameObject.h"
#include "ArrowObject.h"

#include <vector>
#include <unordered_map>
#include <list>
#include <chrono>

#include "MyImage.h"

class PlayerObject : public GameObject
{
private:
	std::unordered_map<std::string, std::vector<MyImage>> images;
	float actionPerSecond;	// 초당 액션의 반복 횟수 (액션 : 현재 애니메이션의 이미지 개수)
	float nowFrameIdxF;		// 현재 프레임 인덱스 (int로 변환 후 사용)

	std::string animState;

	unsigned int keyState;

	int dirX;

	POINTFLOAT velocity;			// x, y 방향 속도
	POINTFLOAT maxSpeed;			// x, y 방향 최대 속도
	POINTFLOAT acceleration;		// x, y(중력) 방향 가속도

	bool isFly;						// 공중에 떠 있는지 여부

	bool isShootReady;				// 발사 준비중인지 여부

	int hp;							// 체력
	std::vector<MyImage> hpImages;	// 체력 이미지 

	bool isHit;
	std::chrono::steady_clock::time_point hitTime;

	bool isDead;
	std::chrono::steady_clock::time_point deadTime;

public:
	std::list<ArrowObject> arrows;

public:
	PlayerObject();
	virtual ~PlayerObject();

	virtual void update(float elapsedTime) override;
	virtual void draw(HDC hdc, int windowLeft = 0) const override;

	void sendKeyMsg(UINT message, WPARAM wParam);

	void setFly(bool bFly);
	bool getFly() const;

	void setVelocityX(float valX);
	void setVelocityY(float valY);

	void fireArrow();

	void onHpItem();

	void onHit();
	void setHit(bool hit);
	bool getHit() const;

	bool getIsDead() const;

};

