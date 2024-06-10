#pragma once

#include "GameObject.h"
#include "MyImage.h"
#include "FireObject.h"

#include <list>
#include <vector>
#include <chrono>

class PlayerObject;
class BossObject : public GameObject
{
private:
	MyImage cloudImage;
	MyImage chairImage;
	std::vector<MyImage> images;

	float actionPerSecond;	// 초당 액션의 반복 횟수 (액션 : 현재 애니메이션의 이미지 개수)
	float nowFrameIdxF;		// 현재 프레임 인덱스 (int로 변환 후 사용)

	int hp;

	const PlayerObject* targetPlayer = nullptr;
	std::chrono::steady_clock::time_point lastFireTime;

public:
	std::list<FireObject> fires;

public:
	BossObject();
	virtual ~BossObject();

	virtual void update(float elapsedTime) override;
	virtual void draw(HDC hdc, int windowLeft = 0) const override;

	void setTargetPlayer(const PlayerObject& target);

	void onHit();

};

