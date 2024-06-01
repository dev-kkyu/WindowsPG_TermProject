#pragma once

#include <Windows.h>
#include <memory>

#define W_WIDTH		1200
#define W_HEIGHT	900

class Scene;
class GameFramework
{
private:
	HWND hWnd;
	RECT clientArea;
	HDC hDCFrameBuffer;
	HBITMAP hBitmapFrameBuffer;

	std::shared_ptr<Scene> pScene;

public:
	void initialize(HWND hMainWnd);
	void drawNextFrame();
	void destroy();

	void processWindowMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	void updateFrameBuffer(float elapsedTime);
	void drawFrameBuffer();
	void clearFrameBuffer(COLORREF color);
	void presentFrameBuffer();

};

