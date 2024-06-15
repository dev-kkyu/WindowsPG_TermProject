#pragma once

#include <Windows.h>

class GameObject
{
private:
	static bool isCollisionDebugMode;

protected:
	POINTFLOAT pos;	// float�� ����.. �ε巯�� Ÿ�̸� �ִϸ��̼��� ���Ͽ�
	SIZE size;

public:
	GameObject();
	virtual ~GameObject();

	virtual void update(float elapsedTime) = 0;
	virtual void draw(HDC hdc, int windowLeft = 0) const = 0;
	void drawDebug(HDC hdc, int windowLeft = 0) const;

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

public:
	static void changeDebugMode();
};

