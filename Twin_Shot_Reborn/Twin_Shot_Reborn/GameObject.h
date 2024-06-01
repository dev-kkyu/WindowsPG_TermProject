#pragma once

#include <Windows.h>

class GameObject
{
protected:
	POINTFLOAT pos;	// float�� ����.. �ε巯�� Ÿ�̸� �ִϸ��̼��� ���Ͽ�
	int size;

public:
	GameObject();
	virtual ~GameObject();

	virtual void update(float elapsedTime) = 0;
	virtual void draw(HDC hdc) = 0;

	void move(const POINT& dir, float value);

	void setPos(const POINTFLOAT& fPos);
	void setPos(const POINT& iPos);

	POINTFLOAT getPos() const;
	POINT getPosInt() const;

	void setSize(int size);
	int getSize() const;

	RECT getCollisionRect() const;
};

