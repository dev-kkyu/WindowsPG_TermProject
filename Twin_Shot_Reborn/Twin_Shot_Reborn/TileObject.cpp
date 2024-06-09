#include "TileObject.h"

bool TileObject::isImageLoaded;
std::array<MyImage, 17> TileObject::tileImages;

TileObject::TileObject(POINT iPos)
{
	if (not isImageLoaded) {
		for (int i = 0; i < 17; ++i) {
			tileImages[i].Load(L"./Resources/Images/Tile/" + std::to_wstring(i + 1) + L".png");
		}
		isImageLoaded = true;
	}

	imageIndex = rand() % 8; 

	setPos(iPos);
	size = { 50, 50 };
}

TileObject::TileObject(POINT iPos, int idx)
	: TileObject{ iPos }
{
	imageIndex = idx;
}

TileObject::~TileObject()
{
}

void TileObject::update(float elapsedTime)
{
}

void TileObject::draw(HDC hdc, int windowLeft) const
{
	tileImages[imageIndex].MyDraw(hdc, getObjectRect(), windowLeft);
}
