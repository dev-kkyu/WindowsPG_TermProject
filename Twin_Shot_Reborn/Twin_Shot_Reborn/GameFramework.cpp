#include "GameFramework.h"

#include <chrono>

#include "GameScene.h"

void GameFramework::initialize(HWND hMainWnd)
{
	hWnd = hMainWnd;
	GetClientRect(hWnd, &clientArea);
	HDC hDC = GetDC(hWnd);
	hDCFrameBuffer = CreateCompatibleDC(hDC);
	hBitmapFrameBuffer = CreateCompatibleBitmap(hDC, clientArea.right, clientArea.bottom);
	SelectObject(hDCFrameBuffer, hBitmapFrameBuffer);
	ReleaseDC(hWnd, hDC);
	SetBkMode(hDCFrameBuffer, TRANSPARENT);				// 백그라운드 투명
	SetStretchBltMode(hDCFrameBuffer, HALFTONE);		// 비트맵 축소, 확대시 보간

	pScene = std::make_shared<GameScene>();
}

void GameFramework::drawNextFrame()
{
	using namespace std::chrono;
	static steady_clock::time_point last_time = steady_clock::now();
	steady_clock::time_point now_time = steady_clock::now();
	float elapsedTime = duration_cast<nanoseconds>(now_time - last_time).count() / 1'000'000'000.f;
	last_time = now_time;

	updateFrameBuffer(elapsedTime);			// 오브젝트 업데이트

	clearFrameBuffer(RGB(255, 255, 255));	// 흰색으로 모두 채우기
	drawFrameBuffer();						// 후면 버퍼(메모리DC)에 그리기
	presentFrameBuffer();					// 후면 버퍼를 전면 버퍼로 스왑
}

void GameFramework::destroy()
{
	DeleteObject(hBitmapFrameBuffer);
	DeleteDC(hDCFrameBuffer);
}

void GameFramework::processWindowMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (pScene)
		pScene->processWindowMessage(hWnd, message, wParam, lParam);

	switch (message)
	{
	case WM_CHAR:
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		default:
			break;
		}
		break;
	case WM_KEYUP:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MOUSEMOVE:
		break;
	default:
		MessageBoxA(hWnd, "Wrong Window Message On GameFramework", nullptr, MB_OK);
		break;
	}
}

void GameFramework::updateFrameBuffer(float elapsedTime)
{
	if (pScene)
		pScene->update(elapsedTime);
}

void GameFramework::drawFrameBuffer()
{
	if (pScene)
		pScene->draw(hDCFrameBuffer);
}

void GameFramework::clearFrameBuffer(COLORREF color)
{
	HPEN hPen = CreatePen(PS_SOLID, 0, color);
	HPEN hOldPen = (HPEN)SelectObject(hDCFrameBuffer, hPen);
	HBRUSH hBrush = CreateSolidBrush(color);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDCFrameBuffer, hBrush);
	// 인자의 색상으로 프레임버퍼를 모두 채운다
	Rectangle(hDCFrameBuffer, clientArea.left, clientArea.top, clientArea.right, clientArea.bottom);
	SelectObject(hDCFrameBuffer, hOldBrush);
	SelectObject(hDCFrameBuffer, hOldPen);
	DeleteObject(hBrush);
	DeleteObject(hPen);
}

void GameFramework::presentFrameBuffer()
{
	HDC hDC = GetDC(hWnd);
	BitBlt(hDC, 0, 0, clientArea.right, clientArea.bottom, hDCFrameBuffer, 0, 0, SRCCOPY);
	ReleaseDC(hWnd, hDC);
}
