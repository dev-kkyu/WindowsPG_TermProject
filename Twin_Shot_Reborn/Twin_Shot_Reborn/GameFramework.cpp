#include "GameFramework.h"

#include <string>
#include <chrono>

#include "MySound.h"

#include "Scene0.h"
#include "Scene1.h"
#include "Scene2.h"
#include "Scene3.h"
#include "Scene4.h"

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

	pScene = std::make_shared<Scene0>();
}

void GameFramework::drawNextFrame()
{
	using namespace std::chrono;
	static steady_clock::time_point last_time = steady_clock::now();
	static steady_clock::duration accm_time;				// 누적 시간
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
		switch (wParam)
		{
		case '0':
			pScene = std::make_shared<Scene0>();
			break;
		case '1':
			pScene = std::make_shared<Scene1>();
			break;
		case '2':
			pScene = std::make_shared<Scene2>();
			break;
		case '3':
			pScene = std::make_shared<Scene3>();
			break;
		case '4':
			pScene = std::make_shared<Scene4>();
			break;
		}
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_F5:
			GameObject::changeDebugMode();
			break;
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
	if (pScene) {
		pScene->update(elapsedTime);

		if (pScene->onClear()) {	// 스테이지 클리어시 다음 스테이지
			auto p0 = dynamic_cast<Scene0*>(pScene.get());
			auto p1 = dynamic_cast<Scene1*>(pScene.get());
			auto p2 = dynamic_cast<Scene2*>(pScene.get());
			auto p3 = dynamic_cast<Scene3*>(pScene.get());
			auto p4 = dynamic_cast<Scene4*>(pScene.get());
			if (p0)
				pScene = std::make_shared<Scene1>();
			else if (p1)
				pScene = std::make_shared<Scene2>();
			else if (p2)
				pScene = std::make_shared<Scene3>();
			else if (p3)
				pScene = std::make_shared<Scene4>();
			else {	// 처음부터 시작
				pScene->setPlayerScore(0);
				pScene = std::make_shared<Scene0>();
			}
		}
		else if (pScene->getPlayerDead()) {		// 플레이어 사망시 다시 시작
			// 점수 반토막
			pScene->setPlayerScore(pScene->getPlayerScore() / 2);

			auto p1 = dynamic_cast<Scene1*>(pScene.get());
			auto p2 = dynamic_cast<Scene2*>(pScene.get());
			auto p3 = dynamic_cast<Scene3*>(pScene.get());
			if (p1)
				pScene = std::make_shared<Scene1>();
			else if (p2)
				pScene = std::make_shared<Scene2>();
			else if (p3)
				pScene = std::make_shared<Scene3>();
		}
	}

	// 사운드 업데이트
	MySound::getInstance().update();
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
