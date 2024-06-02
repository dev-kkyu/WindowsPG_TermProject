#pragma once

#include "GameObject.h"

class PlayerObject : public GameObject
{

public:
	PlayerObject();
	virtual ~PlayerObject();

	virtual void update(float elapsedTime) override;
	virtual void draw(HDC hdc) override;
};

