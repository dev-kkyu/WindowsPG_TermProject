#pragma once

#include "GameObject.h"
#include "MyImage.h"

#include <array>
#include <vector>

class MonsterObject : public GameObject
{
private:
	int imageIndex;

	float actionPerSecond;	// �ʴ� �׼��� �ݺ� Ƚ�� (�׼� : ���� �ִϸ��̼��� �̹��� ����)
	float nowFrameIdxF;		// ���� ������ �ε��� (int�� ��ȯ �� ���)

	int dirX;

	int rangeXMin;
	int rangeXMax;

private:		// static ���� -> �̹����� �� ���� �ε��� �� �ֵ��� ����
	static bool isImageLoaded;
	static std::array<std::vector<MyImage>, 3> monsterImages;

public:
	MonsterObject(POINT iPos, int idx, SIZE size, int min, int max);
	virtual ~MonsterObject();

	virtual void update(float elapsedTime) override;
	virtual void draw(HDC hdc, int windowLeft = 0) const override;

};

