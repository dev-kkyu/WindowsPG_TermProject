#pragma once

#include <Windows.h>

#include "MyImage.h"

class Scene
{
protected:
	MyImage background;

public:
	Scene();
	virtual ~Scene();

	virtual void initialize() = 0;
	virtual void update(float elapsedTime) = 0;
	virtual void draw(HDC hdc) = 0;
	virtual void destroy() = 0;

	virtual void processWindowMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

