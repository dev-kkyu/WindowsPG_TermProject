#include "GameObject.h"

#include <cmath>
#include <limits>

GameObject::GameObject()
{
	pos.x = pos.y = 0.f;
	size = { 10, 10 };
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
		float normX = static_cast<float>(dir.x / length);
		float normY = static_cast<float>(dir.y / length);

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

void GameObject::setSize(SIZE size)
{
	this->size = size;
}

SIZE GameObject::getSize() const
{
	return size;
}

RECT GameObject::getCollisionRect() const
{
	POINT pos = getPosInt();
	return RECT{ pos.x - size.cx / 2, pos.y - size.cy / 2, pos.x + size.cx / 2, pos.y + size.cy / 2 };
}

bool GameObject::isCollide(const GameObject& other) const
{
	RECT rc;
	const RECT myRect = getCollisionRect();
	const RECT otherRect = other.getCollisionRect();
	return static_cast<bool>(IntersectRect(&rc, &myRect, &otherRect));
}

bool GameObject::isSelected(const POINT& point) const
{
	const RECT myRect = getCollisionRect();
	return static_cast<bool>(PtInRect(&myRect, point));
}
