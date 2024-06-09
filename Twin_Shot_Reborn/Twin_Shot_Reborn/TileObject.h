#pragma once

#include "GameObject.h"
#include "MyImage.h"

#include <array>

class TileObject : public GameObject
{
private:
	int imageIndex;

private:		// static 변수 -> 이미지를 한 번만 로드할 수 있도록 설정
	static bool isImageLoaded;
	static std::array<MyImage, 32> tileImages;

public:
	TileObject(POINT iPos);
	TileObject(POINT iPos, int idx);
	TileObject(POINT iPos, int idx, SIZE size);
	virtual ~TileObject();

	virtual void update(float elapsedTime) override;
	virtual void draw(HDC hdc, int windowLeft = 0) const override;

};

