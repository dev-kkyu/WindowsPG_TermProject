#include "Scene0.h"

#include "Define.h"

Scene0::Scene0()
{
	isNext = false;

	background.Load(L"./Resources/Images/Background/Stage2.png");
	cloud.Load(L"./Resources/Images/Background/Cloud2.png");

	title.Load(L"./Resources/Images/title/Title.png");
}

Scene0::~Scene0()
{
}

void Scene0::initialize()
{
}

void Scene0::update(float elapsedTime)
{
	// 배경 구름 이동
	cloudPosXf -= 100.f * elapsedTime;
	if (cloudPosXf < 0.f) {
		cloudPosXf += W_WIDTH;
	}
}

void Scene0::draw(HDC hdc) const
{
	background.MyDraw(hdc, RECT{ 0, 0, W_WIDTH, W_HEIGHT });

	float value = 1.f - cloudPosXf / float(W_WIDTH);
	int imgWidth = cloud.getWidth();
	int imgHeight = cloud.getHeight();
	cloud.MyDraw(hdc, RECT{ 0, 0, int(cloudPosXf), W_HEIGHT }, RECT{ int(value * imgWidth), 0, imgWidth, imgHeight }, false, false, 0x7f);
	cloud.MyDraw(hdc, RECT{ int(cloudPosXf), 0, W_WIDTH, W_HEIGHT }, RECT{ 0, 0, int(value * imgWidth), imgHeight }, false, false, 0x7f);
	
	title.MyDraw(hdc, RECT{ 200, 50, 200 + 810, 50 + 348 }); // 405, 174

	// 임시 press any key
	std::string str = "Press any key to Start";
	TextOutA(hdc, 500, 520, str.c_str(), int(str.size()));
}

void Scene0::destroy()
{
}

bool Scene0::onClear() const
{
	return isNext;
}

void Scene0::processWindowMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CHAR:
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MOUSEMOVE:
		break;
	default:
		MessageBoxA(hWnd, "Wrong Window Message On Scene0", nullptr, MB_OK);
		break;
	}
}
