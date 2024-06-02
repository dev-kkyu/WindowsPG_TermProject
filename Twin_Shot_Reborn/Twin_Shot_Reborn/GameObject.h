#pragma once

#include <Windows.h>
#include <vector>
#include <unordered_map>

#include "MyImage.h"

class GameObject
{
protected:
	POINTFLOAT pos;	// float로 관리.. 부드러운 타이머 애니메이션을 위하여
	SIZE size;

	std::unordered_map<std::string, std::vector<MyImage>> images;
	float framePerSecond;	// 초당 몇장 돌릴건지
	float nowFrameIdxF;		// 현재 프레임 인덱스 (int로 변환 후 사용)

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

	void setSize(SIZE size);
	SIZE getSize() const;

	RECT getObjectRect() const;

	bool isCollide(const GameObject& other) const;
	bool isSelected(const POINT& point) const;
};

