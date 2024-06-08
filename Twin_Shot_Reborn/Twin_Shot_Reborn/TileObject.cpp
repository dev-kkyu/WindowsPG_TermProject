#include "TileObject.h"

TileObject::TileObject(POINT iPos)
{
	int randIdx = rand() % 8 + 1;		// 1 ~ 8;
	tileImage.Load(L"./Resources/Images/Tile/" + std::to_wstring(randIdx) + L".png");

	setPos(iPos);
	size = { 50, 50 };
}

TileObject::~TileObject()
{
}

TileObject::TileObject(TileObject&& other) noexcept
	: GameObject{ std::move(other) }, tileImage{ std::move(other.tileImage) }
{
}

TileObject& TileObject::operator=(TileObject&& other) noexcept
{
	if (this != &other) {
		GameObject::operator=(std::move(other));
		tileImage = std::move(other.tileImage);
	}
	return *this;
}

void TileObject::update(float elapsedTime)
{
}

void TileObject::draw(HDC hdc)
{
	tileImage.MyDraw(hdc, getObjectRect());
}
