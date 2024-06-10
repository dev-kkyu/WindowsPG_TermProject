#include "FireObject.h"

#include <cmath>
#include <limits>

std::array<MyImage, 5> FireObject::images;
bool FireObject::isImageLoaded;

FireObject::FireObject(POINT spawnPos, float dirX, float dirY)
	: dirX{ dirX }, dirY{ dirY }
{
	setPos(spawnPos);

	size = { 111, 78 };

	if (not isImageLoaded) {
		for (int i = 0; i < 5; ++i)
			images[i].Load(L"./Resources/Images/Monster/Boss/1" + std::to_wstring(i + 1) + L".png");
		isImageLoaded = true;
	}

	actionPerSecond = 5.f;
	nowFrameIdxF = 0.f;
}

FireObject::~FireObject()
{
}

void FireObject::update(float elapsedTime)
{
	// 이미지 애니메이션
	nowFrameIdxF += (images.size() * actionPerSecond) * elapsedTime;
	nowFrameIdxF = std::fmod(nowFrameIdxF, float(images.size()));

	float length = std::sqrt(dirX * dirX + dirY * dirY);

	if (length >= std::numeric_limits<float>::epsilon()) {
		float dx = dirX / length;
		float dy = dirY / length;

		float speed = 300.f;

		pos.x += speed * dx * elapsedTime;
		pos.y += speed * dy * elapsedTime;
	}
}

void FireObject::draw(HDC hdc, int windowLeft) const
{
	images[int(nowFrameIdxF)].MyDraw(hdc, getObjectRect(), windowLeft);

	drawDebug(hdc, windowLeft);
}
