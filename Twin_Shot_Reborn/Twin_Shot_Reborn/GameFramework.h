#pragma once

#include <Windows.h>
#include <memory>

class SceneBase;
class GameFramework
{
private:
	HWND hWnd;
	RECT clientArea;
	HDC hDCFrameBuffer;
	HBITMAP hBitmapFrameBuffer;

	std::unique_ptr<SceneBase> pScene;

public:
	GameFramework();
	~GameFramework();

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

