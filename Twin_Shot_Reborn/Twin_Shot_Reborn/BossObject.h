#pragma once

#include "GameObject.h"
#include "MyImage.h"

#include <vector>

class BossObject : public GameObject
{
private:
	MyImage cloudImage;
	MyImage chairImage;
	std::vector<MyImage> images;

	float actionPerSecond;	// �ʴ� �׼��� �ݺ� Ƚ�� (�׼� : ���� �ִϸ��̼��� �̹��� ����)
	float nowFrameIdxF;		// ���� ������ �ε��� (int�� ��ȯ �� ���)

	int dirX;

public:
	BossObject();
	virtual ~BossObject();

	virtual void update(float elapsedTime) override;
	virtual void draw(HDC hdc, int windowLeft = 0) const override;

};

