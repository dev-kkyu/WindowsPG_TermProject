#include "TileObject.h"

bool TileObject::isImageLoaded;
std::array<MyImage, 8> TileObject::tileImages;

TileObject::TileObject(POINT iPos)
{
	if (not isImageLoaded) {
		for (int i = 0; i < 8; ++i) {
			tileImages[i].Load(L"./Resources/Images/Tile/" + std::to_wstring(i + 1) + L".png");
		}
		isImageLoaded = true;
	}

	imageIndex = rand() % 8;

	setPos(iPos);
	size = { 50, 50 };
}

TileObject::~TileObject()
{
}

void TileObject::update(float elapsedTime)
{
}

void TileObject::draw(HDC hdc)
{
	tileImages[imageIndex].MyDraw(hdc, getObjectRect());
}
