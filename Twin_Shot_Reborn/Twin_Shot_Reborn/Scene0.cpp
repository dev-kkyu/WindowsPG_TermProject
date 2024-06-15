#include "Scene0.h"

#include "Define.h"

Scene0::Scene0()
{
	isNext = false;

	background.Load(L"./Resources/Images/Background/Stage2.png");
	cloud.Load(L"./Resources/Images/Background/Cloud2.png");

	title.Load(L"./Resources/Images/title/Title.png");

	LOGFONTA logFont{};
	logFont.lfHeight = 40;
	logFont.lfWeight = FW_BOLD;
	strcpy_s(logFont.lfFaceName, "궁서");

	titleFont = CreateFontIndirectA(&logFont);
}

Scene0::~Scene0()
{
	DeleteObject(titleFont);
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

	title.MyDraw(hdc, RECT{ 200, 150, 200 + 810, 150 + 348 });		// 405, 174

	// 안내문
	SetTextColor(hdc, RGB(243, 97, 220));
	HFONT oldFont = (HFONT)SelectObject(hdc, titleFont);
	RECT rc{ 300, 600, 900, 700 };
	std::string str = "Press Any Key To Start";
	DrawTextA(hdc, str.c_str(), int(str.size()), &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	SelectObject(hdc, oldFont);
	SetTextColor(hdc, 0);		// 원상복구
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
		break;
	case WM_KEYDOWN:
		isNext = true;
		break;
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
