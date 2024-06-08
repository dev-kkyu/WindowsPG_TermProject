#pragma once

#define MY_KEY_UP		0x01
#define MY_KEY_DOWN		0x02
#define MY_KEY_LEFT		0x04
#define MY_KEY_RIGHT	0x08
#define MY_KEY_SPACE	0x10

#include "GameObject.h"

#include <vector>
#include <unordered_map>

#include "MyImage.h"

class PlayerObject : public GameObject
{
private:
	std::unordered_map<std::string, std::vector<MyImage>> images;
	float actionPerSecond;	// �ʴ� �׼��� �ݺ� Ƚ�� (�׼� : ���� �ִϸ��̼��� �̹��� ����)
	float nowFrameIdxF;		// ���� ������ �ε��� (int�� ��ȯ �� ���)

	std::string animState;

	unsigned int keyState;

	int dirX;

	POINTFLOAT velocity;		// x, y ���� �ӵ�
	POINTFLOAT maxSpeed;		// x, y ���� �ִ� �ӵ�
	POINTFLOAT acceleration;	// x, y(�߷�) ���� ���ӵ�

	bool isFly;					// ���߿� �� �ִ��� ����

public:
	PlayerObject();
	virtual ~PlayerObject();

	virtual void update(float elapsedTime) override;
	virtual void draw(HDC hdc) override;

	void sendKeyMsg(UINT message, WPARAM wParam);

	void setFly(bool bFly);
	bool getFly() const;

	void setVelocityX(float valX);
	void setVelocityY(float valY);

};

