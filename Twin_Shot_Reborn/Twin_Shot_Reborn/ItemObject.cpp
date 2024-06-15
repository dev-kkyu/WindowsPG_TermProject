#include "ItemObject.h"

#include <cmath>

bool ItemObject::isImageLoaded;
std::array<std::vector<MyImage>, 3> ItemObject::images;

ItemObject::ItemObject(POINT iPos)
{
	if (not isImageLoaded) {
		images[0].resize(1);
		images[0][0].Load(L"./Resources/Images/Item/HP.png");

		images[1].resize(7);
		for (int i = 0; i < 7; ++i) {
			images[1][i].Load(L"./Resources/Images/Item/Silver/" + std::to_wstring(i + 1) + L".png");
		}

		images[2].resize(7);
		for (int i = 0; i < 7; ++i) {
			images[2][i].Load(L"./Resources/Images/Item/Gold/" + std::to_wstring(i + 1) + L".png");
		}
	}

	actionPerSecond = 2.125f;
	nowFrameIdxF = 0.f;

	itemType = ItemType::HP;
	switch (rand() % 3)
	{
	case 0:
		itemType = ItemType::HP;
		setSize({ 50, 50 });
		break;
	case 1:
		itemType = ItemType::S_COIN;
		setSize({ 35, 35 });
		break;
	case 2:
		itemType = ItemType::G_COIN;
		setSize({ 35, 35 });
		break;
	}

	setPos(iPos);
}

ItemObject::~ItemObject()
{
}

void ItemObject::update(float elapsedTime)
{
	switch (itemType)
	{
	case ItemType::S_COIN:
		// 이미지 애니메이션
		nowFrameIdxF += (images[1].size() * actionPerSecond) * elapsedTime;
		nowFrameIdxF = std::fmod(nowFrameIdxF, float(images[1].size()));
		break;
	case ItemType::G_COIN:
		// 이미지 애니메이션
		nowFrameIdxF += (images[2].size() * actionPerSecond) * elapsedTime;
		nowFrameIdxF = std::fmod(nowFrameIdxF, float(images[2].size()));
		break;
	}
}

void ItemObject::draw(HDC hdc, int windowLeft) const
{
	switch (itemType)
	{
	case ItemType::HP:
		images[0][0].MyDraw(hdc, getObjectRect(), windowLeft);
		break;
	case ItemType::S_COIN:
		images[1][int(nowFrameIdxF)].MyDraw(hdc, getObjectRect(), windowLeft);
		break;
	case ItemType::G_COIN:
		images[2][int(nowFrameIdxF)].MyDraw(hdc, getObjectRect(), windowLeft);
		break;
	}
}

ItemObject::ItemType ItemObject::getItemType() const
{
	return itemType;
}
