#pragma once

#include <Windows.h>

class GameObject
{
protected:
	POINTFLOAT pos;	// float�� ����.. �ε巯�� Ÿ�̸� �ִϸ��̼��� ���Ͽ�
	SIZE size;

public:
	GameObject();
	virtual ~GameObject();

	virtual void update(float elapsedTime) = 0;
	virtual void draw(HDC hdc) const = 0;

	void move(const POINT& dir, float value);

	void setPos(const POINTFLOAT& fPos);
	void setPos(const POINT& iPos);

	POINTFLOAT getPos() const;
	POINT getPosInt() const;

	void setSize(SIZE size);
	SIZE getSize() const;

	RECT getObjectRect() const;

	bool isCollide(const GameObject& other) const;
	bool isSelected(const POINT& point) const;

	LONG getLeft() const;
	LONG getTop() const;
	LONG getRight() const;
	LONG getBottom() const;
};

