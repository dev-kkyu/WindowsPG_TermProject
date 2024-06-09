#pragma once

#include "GameObject.h"
#include "MyImage.h"

class ArrowObject : public GameObject
{
private:

private:
	static MyImage image;
	static bool isImageLoaded;

	int dirX;

public:
	ArrowObject(POINT spawnPos, int dirX);
	virtual ~ArrowObject();

	virtual void update(float elapsedTime) override;
	virtual void draw(HDC hdc, int windowLeft = 0) const override;

};

