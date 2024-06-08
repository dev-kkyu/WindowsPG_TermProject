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
	static std::array<MyImage, 8> tileImages;

public:
	TileObject(POINT iPos);
	virtual ~TileObject();

	virtual void update(float elapsedTime);
	virtual void draw(HDC hdc);

};

