#pragma once

#include "GameObject.h"
#include "MyImage.h"

#include <array>

class TileObject : public GameObject
{
private:
	int imageIndex;

private:		// static ���� -> �̹����� �� ���� �ε��� �� �ֵ��� ����
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

