#pragma once

#include "GameObject.h"
#include "MyImage.h"

#include <chrono>

class MonsterObject;
class ArrowObject : public GameObject
{
	friend MonsterObject;
private:
	int dirX;
	std::chrono::steady_clock::time_point hitTime;
	bool isHit;

private:
	static MyImage image;
	static bool isImageLoaded;

public:
	ArrowObject(POINT spawnPos, int dirX);
	virtual ~ArrowObject();

	virtual void update(float elapsedTime) override;
	virtual void draw(HDC hdc, int windowLeft = 0) const override;

	void onHit();
	std::chrono::steady_clock::time_point getHitTime() const;

};

