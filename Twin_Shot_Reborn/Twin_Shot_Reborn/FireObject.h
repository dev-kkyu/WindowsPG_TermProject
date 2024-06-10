#pragma once

#include "GameObject.h"
#include "MyImage.h"

#include <array>

class FireObject : public GameObject
{
private:
	float dirX, dirY;

	float actionPerSecond;	// 초당 액션의 반복 횟수 (액션 : 현재 애니메이션의 이미지 개수)
	float nowFrameIdxF;		// 현재 프레임 인덱스 (int로 변환 후 사용)

private:
	static std::array<MyImage, 5> images;
	static bool isImageLoaded;

public:
	FireObject(POINT spawnPos, float dirX, float dirY);
	virtual ~FireObject();

	virtual void update(float elapsedTime) override;
	virtual void draw(HDC hdc, int windowLeft = 0) const override;


};

