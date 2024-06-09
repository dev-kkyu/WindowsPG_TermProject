#include "ArrowObject.h"

MyImage ArrowObject::image;
bool ArrowObject::isImageLoaded;

ArrowObject::ArrowObject(POINT spawnPos, int dirX)
	: dirX{ dirX }
{
	setPos(spawnPos);
	size = { 106, 22 };

	if (not isImageLoaded) {
		image.Load(L"./Resources/Images/Character/Arrow.png");
		isImageLoaded = true;
	}

	isHit = false;
}

ArrowObject::~ArrowObject()
{
}

void ArrowObject::update(float elapsedTime)
{
	pos.x += 1000.f * elapsedTime * dirX;
}

void ArrowObject::draw(HDC hdc, int windowLeft) const
{
	bool isDraw = true;
	if (isHit) {
		auto nowTime = std::chrono::steady_clock::now();
		auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(nowTime - hitTime).count();
		if (ms > 5000) {
			if ((ms / 100) & 1)		// 100ms¸¶´Ù ±ôºý¿©ÁØ´Ù
				isDraw = false;
		}
	}

	if (isDraw) {
		if (dirX > 0) {
			image.MyDraw(hdc, getObjectRect(), windowLeft, true);
		}
		else if (dirX < 0) {
			image.MyDraw(hdc, getObjectRect(), windowLeft);
		}
	}

	drawDebug(hdc, windowLeft);
}

void ArrowObject::onHit()
{
	hitTime = std::chrono::steady_clock::now();
	isHit = true;
}

std::chrono::steady_clock::time_point ArrowObject::getHitTime() const
{
	return hitTime;
}
