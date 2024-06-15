#pragma once

#include "SceneBase.h"

class Scene0 : public SceneBase
{
private:
	bool isNext;
	MyImage title;
	MyImage Play;

public:
	Scene0();
	virtual ~Scene0();

	virtual void initialize() override;
	virtual void update(float elapsedTime) override;
	virtual void draw(HDC hdc) const override;
	virtual void destroy() override;

	virtual bool onClear() const override;

	virtual void processWindowMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

};

