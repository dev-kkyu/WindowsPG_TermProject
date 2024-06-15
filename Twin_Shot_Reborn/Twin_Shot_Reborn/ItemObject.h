#pragma once

#include "GameObject.h"
#include "MyImage.h"

#include <array>
#include <vector>

class ItemObject : public GameObject
{
public:
	enum ItemType { HP, S_COIN, G_COIN };

private:
	static bool isImageLoaded;
	static std::array<std::vector<MyImage>, 3> images;

private:
	ItemType itemType;

	float actionPerSecond;	// 초당 액션의 반복 횟수 (액션 : 현재 애니메이션의 이미지 개수)
	float nowFrameIdxF;		// 현재 프레임 인덱스 (int로 변환 후 사용)

public:
	ItemObject(POINT iPos);
	virtual ~ItemObject();

	virtual void update(float elapsedTime);
	virtual void draw(HDC hdc, int windowLeft = 0) const;

	ItemType getItemType() const;

};

