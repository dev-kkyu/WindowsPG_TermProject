#pragma once

#include "SceneBase.h"
#include "MonsterObject.h"

#include <list>

class Scene2 : public SceneBase
{
private:
	std::list<MonsterObject> monsters;

public:
	Scene2();
	virtual ~Scene2();

	virtual void initialize() override;
	virtual void update(float elapsedTime) override;
	virtual void draw(HDC hdc) const override;
	virtual void destroy() override;

	virtual void processWindowMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

};

