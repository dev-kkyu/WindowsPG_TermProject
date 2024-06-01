#pragma once

#include <Windows.h>

class Scene
{
protected:

public:
	Scene();
	virtual ~Scene();

	virtual void initialize() = 0;
	virtual void update(float elapsedTime) = 0;
	virtual void draw(HDC hdc) = 0;
	virtual void destroy() = 0;

	virtual void processWindowMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

