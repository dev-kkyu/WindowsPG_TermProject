#pragma once

#include "SceneBase.h"

class Scene3 : public SceneBase
{
private:

public:
	Scene3();
	virtual ~Scene3();

	virtual void initialize() override;
	virtual void update(float elapsedTime) override;
	virtual void draw(HDC hdc) const override;
	virtual void destroy() override;

	virtual void processWindowMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

};

