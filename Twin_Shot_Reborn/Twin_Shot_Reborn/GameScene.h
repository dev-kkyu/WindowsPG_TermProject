#pragma once

#include "Scene.h"

#include "PlayerObject.h"

class GameScene : public Scene
{
private:
	PlayerObject player;

public:
	GameScene();
	virtual ~GameScene();

	virtual void initialize() override;
	virtual void update(float elapsedTime) override;
	virtual void draw(HDC hdc) const override;
	virtual void destroy() override;

	virtual void processWindowMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

