#include "MonsterObject.h"

#include <cmath>

bool MonsterObject::isImageLoaded;
std::array<std::vector<MyImage>, 3> MonsterObject::monsterImages;

MonsterObject::MonsterObject(POINT iPos, int idx, SIZE size, int min, int max)
{
	if (not isImageLoaded) {
		monsterImages[0].resize(10);
		for (int i = 0; i < 10; ++i) {
			monsterImages[0][i].Load(L"./Resources/Images/Monster/Stage1/" + std::to_wstring(i + 1) + L".png");
		}

		monsterImages[1].resize(4);
		for (int i = 0; i < 4; ++i) {
			monsterImages[1][i].Load(L"./Resources/Images/Monster/Stage2/" + std::to_wstring(i + 1) + L".png");
		}

		monsterImages[2].resize(7);
		for (int i = 0; i < 7; ++i) {
			monsterImages[2][i].Load(L"./Resources/Images/Monster/Stage2/" + std::to_wstring(i + 6) + L".png");
		}
		isImageLoaded = true;
	}

	setPos(iPos);
	imageIndex = idx;
	setSize(size);

	actionPerSecond = 1.25f;
	nowFrameIdxF = 0.f;

	dirX = 1;

	rangeXMin = min;
	rangeXMax = max;
}

MonsterObject::~MonsterObject()
{
}

void MonsterObject::update(float elapsedTime)
{
	// 이미지 애니메이션
	nowFrameIdxF += (monsterImages[imageIndex].size() * actionPerSecond) * elapsedTime; 
	nowFrameIdxF = std::fmod(nowFrameIdxF, float(monsterImages[imageIndex].size())); 

	// 이동 

	if (imageIndex == 0 and nowFrameIdxF > 3 || imageIndex == 1 || imageIndex == 2) {

		if (dirX == 1) {
			if (getPosInt().x < rangeXMax)
				move(POINT{ 1, 0 }, 100.f * elapsedTime);
			else
				dirX = -1;
		}
		else {
			if (getPosInt().x > rangeXMin)
				move(POINT{ -1, 0 }, 100.f * elapsedTime);
			else
				dirX = 1;
		}
	}

}

void MonsterObject::draw(HDC hdc, int windowLeft) const
{
	if (1 == dirX)
		monsterImages[imageIndex][int(nowFrameIdxF)].MyDraw(hdc, getObjectRect(), windowLeft, true);
	else
		monsterImages[imageIndex][int(nowFrameIdxF)].MyDraw(hdc, getObjectRect(), windowLeft);

	drawDebug(hdc, windowLeft);
}
