#pragma once

#include <Windows.h>
#include <vector>

#include "MyImage.h"
#include "TileObject.h"
#include "PlayerObject.h"

class SceneBase
{
protected:
	MyImage background;
	std::vector<TileObject> tiles;

	PlayerObject player;

public:
	SceneBase();
	virtual ~SceneBase();

	virtual void initialize() = 0;
	virtual void update(float elapsedTime) = 0;
	virtual void draw(HDC hdc) const = 0;
	virtual void destroy() = 0;

	virtual void processWindowMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

