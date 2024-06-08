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
	// 방향 벡터의 크기(길이)를 계산
	double length = std::sqrt(dir.x * dir.x + dir.y * dir.y);

	// 방향 벡터를 정규화 (길이를 1로 만듦)
	if (length >= std::numeric_limits<double>::epsilon()) {
		float normX = static_cast<float>(dir.x / length);
		float normY = static_cast<float>(dir.y / length);

		// 이동할 거리를 곱하여 새로운 위치 계산
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

RECT GameObject::getObjectRect() const
{
	return RECT{ getLeft(), getTop(), getRight(), getBottom() };	// 피벗을 중앙 하단으로 둔다.
}

bool GameObject::isCollide(const GameObject& other) const
{
	RECT rc;
	const RECT myRect = getObjectRect();
	const RECT otherRect = other.getObjectRect();
	return static_cast<bool>(IntersectRect(&rc, &myRect, &otherRect));
}

bool GameObject::isSelected(const POINT& point) const
{
	const RECT myRect = getObjectRect();
	return static_cast<bool>(PtInRect(&myRect, point));
}

LONG GameObject::getLeft() const
{
	return static_cast<LONG>(pos.x - size.cx / 2.f);
}

LONG GameObject::getTop() const
{
	return static_cast<LONG>(pos.y - size.cy);
}

LONG GameObject::getRight() const
{
	return static_cast<LONG>(pos.x + size.cx / 2.f);
}

LONG GameObject::getBottom() const
{
	return static_cast<LONG>(pos.y);
}
