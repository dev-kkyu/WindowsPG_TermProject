#include "ArrowObject.h"

ArrowObject::ArrowObject(POINT spawnPos, int dirX)
	: dirX{ dirX }
{
	setPos(spawnPos);

	image.Load(L"./Resources/Images/Character/Arrow.png");

}

ArrowObject::~ArrowObject()
{
}

void ArrowObject::update(float elapsedTime)
{
	pos.x += 600.f * elapsedTime * dirX;
}

void ArrowObject::draw(HDC hdc, int windowLeft) const
{
	if (dirX > 0) {
		image.MyDraw(hdc, getObjectRect(), windowLeft, true);
	}
	else if (dirX < 0) {
		image.MyDraw(hdc, getObjectRect(), windowLeft);
	}
}
