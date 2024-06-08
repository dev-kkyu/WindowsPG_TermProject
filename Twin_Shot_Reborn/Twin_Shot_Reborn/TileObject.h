#pragma once

#include "GameObject.h"
#include "MyImage.h"

class TileObject : public GameObject
{
private:
	MyImage tileImage;

public:
	TileObject(POINT iPos);
	virtual ~TileObject();

	TileObject(const TileObject& other) = delete;
	TileObject& operator=(const TileObject& other) = delete;
	TileObject(TileObject&& other) noexcept;
	TileObject& operator=(TileObject&& other) noexcept;

	virtual void update(float elapsedTime);
	virtual void draw(HDC hdc);

};

