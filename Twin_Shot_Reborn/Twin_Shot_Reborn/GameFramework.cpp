#include "GameFramework.h"

#include <string>
#include <chrono>

#include "Scene1.h"

void GameFramework::initialize(HWND hMainWnd)
{
	hWnd = hMainWnd;
	GetClientRect(hWnd, &clientArea);
	HDC hDC = GetDC(hWnd);
	hDCFrameBuffer = CreateCompatibleDC(hDC);
	hBitmapFrameBuffer = CreateCompatibleBitmap(hDC, clientArea.right, clientArea.bottom);
	SelectObject(hDCFrameBuffer, hBitmapFrameBuffer);
	ReleaseDC(hWnd, hDC);
	SetBkMode(hDCFrameBuffer, TRANSPARENT);				// ��׶��� ����
	SetStretchBltMode(hDCFrameBuffer, HALFTONE);		// ��Ʈ�� ���, Ȯ��� ����

	pScene = std::make_shared<Scene1>();
}

void GameFramework::drawNextFrame()
{
	using namespace std::chrono;
	static steady_clock::time_point last_time = steady_clock::now();
	static steady_clock::duration accm_time;				// ���� �ð�
	static int fps;
	steady_clock::time_point now_time = steady_clock::now();
	steady_clock::duration duration_time = now_time - last_time;
	last_time = now_time;
	accm_time += duration_time;
	++fps;
	if (accm_time >= 1s) {
		accm_time -= 1s;
		std::string text = "Twin Shot Reborn (" + std::to_string(fps) + " FPS)";
		SetWindowTextA(hWnd, text.c_str());
		fps = 0;
	}

	float elapsedTime = duration_cast<nanoseconds>(duration_time).count() / 1'000'000'000.f;

	updateFrameBuffer(elapsedTime);			// ������Ʈ ������Ʈ

	clearFrameBuffer(RGB(255, 255, 255));	// ������� ��� ä���
	drawFrameBuffer();						// �ĸ� ����(�޸�DC)�� �׸���
	presentFrameBuffer();					// �ĸ� ���۸� ���� ���۷� ����
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
	// ������ �������� �����ӹ��۸� ��� ä���
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
