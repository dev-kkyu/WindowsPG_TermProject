#pragma once

#include "SceneBase.h"
#include "MonsterObject.h"

#include <list>

class Scene1 : public SceneBase
{
private:
	std::list<MonsterObject> monsters;

public:
	Scene1();
	virtual ~Scene1();

	virtual void initialize() override;
	virtual void update(float elapsedTime) override;
	virtual void draw(HDC hdc) const override;
	virtual void destroy() override;

	virtual bool onClear() const override;

	virtual void processWindowMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

};

