#pragma once

#include "GameObject.h"
#include "MyImage.h"

#include <array>
#include <vector>
#include <chrono>

class ArrowObject;
class MonsterObject : public GameObject
{
private:
	int imageIndex;

	float actionPerSecond;	// 초당 액션의 반복 횟수 (액션 : 현재 애니메이션의 이미지 개수)
	float nowFrameIdxF;		// 현재 프레임 인덱스 (int로 변환 후 사용)

	int dirX;

	int rangeXMin;			// 몬스터 AI 왕복 범위
	int rangeXMax;

	bool isDead;			// 화살에 피격시 사망
	int deadDirX;
	float deadVelocity;
	std::chrono::steady_clock::time_point deadTime;

private:		// static 변수 -> 이미지를 한 번만 로드할 수 있도록 설정
	static bool isImageLoaded;
	static std::array<std::vector<MyImage>, 3> monsterImages;

public:
	MonsterObject(POINT iPos, int idx, SIZE size, int min, int max);
	virtual ~MonsterObject();

	virtual void update(float elapsedTime) override;
	virtual void draw(HDC hdc, int windowLeft = 0) const override;

	void onHit(const ArrowObject& other);
	bool getIsDead() const;
	std::chrono::steady_clock::time_point getDeadTime() const;

};

