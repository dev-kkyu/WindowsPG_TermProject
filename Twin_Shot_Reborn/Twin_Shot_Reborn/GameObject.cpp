#include "GameObject.h"

#include <cmath>
#include <limits>

GameObject::GameObject()
{
	pos.x = pos.y = 0.f;
	size = 10;
}

GameObject::~GameObject()
{
}

void GameObject::move(const POINT& dir, float value)
{
	// ���� ������ ũ��(����)�� ���
	double length = std::sqrt(dir.x * dir.x + dir.y * dir.y);

	// ���� ���͸� ����ȭ (���̸� 1�� ����)
	if (length >= std::numeric_limits<double>::epsilon()) {
		float normX = dir.x / length;
		float normY = dir.y / length;

		// �̵��� �Ÿ��� ���Ͽ� ���ο� ��ġ ���
		pos.x += normX * value;
		pos.y += normY * value;
	}
}

void GameObject::setPos(const POINTFLOAT& fPos)
{
	pos = fPos;
}

void GameObject::setPos(const POINT& iPos)
{
	setPos(POINTFLOAT{ static_cast<FLOAT>(iPos.x), static_cast<FLOAT>(iPos.y) });
}

POINTFLOAT GameObject::getPos() const
{
	return pos;
}

POINT GameObject::getPosInt() const
{
	return { static_cast<LONG>(pos.x), static_cast<LONG>(pos.y) };
}

void GameObject::setSize(int size)
{
	this->size = size;
}

int GameObject::getSize() const
{
	return size;
}

RECT GameObject::getCollisionRect() const
{
	POINT pos = getPosInt();
	return RECT{ pos.x - size / 2, pos.y - size / 2, pos.x + size / 2, pos.y + size / 2 };
}
