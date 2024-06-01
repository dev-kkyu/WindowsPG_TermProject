#pragma once

#include "Scene.h"

class GameScene : public Scene
{
private:

public:
	GameScene();
	virtual ~GameScene();

	virtual void initialize() override;
	virtual void update(float elapsedTime) override;
	virtual void draw(HDC hdc) override;
	virtual void destroy() override;

	virtual void processWindowMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

