#pragma once

#include "SceneBase.h"

class Scene4 : public SceneBase
{
private:
	bool isNext;
	MyImage title;

	HFONT titleFont[2];

public:
	Scene4();
	virtual ~Scene4();

	virtual void initialize() override;
	virtual void update(float elapsedTime) override;
	virtual void draw(HDC hdc) const override;
	virtual void destroy() override;

	virtual bool onClear() const override;

	virtual void processWindowMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

