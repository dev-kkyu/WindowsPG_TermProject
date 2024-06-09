#pragma once

#include "GameObject.h"
#include "MyImage.h"

#include <array>
#include <vector>
#include <chrono>

class ArrowObject;
class MonsterObject : public GameObject
{
private:
	int imageIndex;

	float actionPerSecond;	// �ʴ� �׼��� �ݺ� Ƚ�� (�׼� : ���� �ִϸ��̼��� �̹��� ����)
	float nowFrameIdxF;		// ���� ������ �ε��� (int�� ��ȯ �� ���)

	int dirX;

	int rangeXMin;			// ���� AI �պ� ����
	int rangeXMax;

	bool isDead;			// ȭ�쿡 �ǰݽ� ���
	int deadDirX;
	float deadVelocity;
	std::chrono::steady_clock::time_point deadTime;

private:		// static ���� -> �̹����� �� ���� �ε��� �� �ֵ��� ����
	static bool isImageLoaded;
	static std::array<std::vector<MyImage>, 3> monsterImages;

public:
	MonsterObject(POINT iPos, int idx, SIZE size, int min, int max);
	virtual ~MonsterObject();

	virtual void update(float elapsedTime) override;
	virtual void draw(HDC hdc, int windowLeft = 0) const override;

	void onHit(const ArrowObject& other);
	bool getIsDead() const;
	std::chrono::steady_clock::time_point getDeadTime() const;

};

