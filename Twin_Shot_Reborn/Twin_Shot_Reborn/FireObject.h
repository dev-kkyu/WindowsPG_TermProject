#pragma once

#include "GameObject.h"
#include "MyImage.h"

#include <array>

class FireObject : public GameObject
{
private:
	float dirX, dirY;

	float actionPerSecond;	// �ʴ� �׼��� �ݺ� Ƚ�� (�׼� : ���� �ִϸ��̼��� �̹��� ����)
	float nowFrameIdxF;		// ���� ������ �ε��� (int�� ��ȯ �� ���)

private:
	static std::array<MyImage, 5> images;
	static bool isImageLoaded;

public:
	FireObject(POINT spawnPos, float dirX, float dirY);
	virtual ~FireObject();

	virtual void update(float elapsedTime) override;
	virtual void draw(HDC hdc, int windowLeft = 0) const override;


};

