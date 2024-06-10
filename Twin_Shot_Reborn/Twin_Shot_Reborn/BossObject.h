#pragma once

#include "GameObject.h"
#include "MyImage.h"
#include "FireObject.h"

#include <list>
#include <vector>
#include <chrono>

class PlayerObject;
class BossObject : public GameObject
{
private:
	MyImage cloudImage;
	MyImage chairImage;
	std::vector<MyImage> images;

	float actionPerSecond;	// �ʴ� �׼��� �ݺ� Ƚ�� (�׼� : ���� �ִϸ��̼��� �̹��� ����)
	float nowFrameIdxF;		// ���� ������ �ε��� (int�� ��ȯ �� ���)

	int hp;

	const PlayerObject* targetPlayer = nullptr;
	std::chrono::steady_clock::time_point lastFireTime;

public:
	std::list<FireObject> fires;

public:
	BossObject();
	virtual ~BossObject();

	virtual void update(float elapsedTime) override;
	virtual void draw(HDC hdc, int windowLeft = 0) const override;

	void setTargetPlayer(const PlayerObject& target);

	void onHit();

};

