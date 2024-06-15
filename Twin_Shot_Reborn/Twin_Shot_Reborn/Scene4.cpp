#include "Scene4.h"

#include "Define.h"

#include "MySound.h"

Scene4::Scene4()
{
	isNext = false;

	background.Load(L"./Resources/Images/Background/Stage1.png");
	cloud.Load(L"./Resources/Images/Background/Cloud1.png");

	title.Load(L"./Resources/Images/title/Title.png");

	LOGFONTA logFont{};
	logFont.lfWeight = FW_BOLD;
	strcpy_s(logFont.lfFaceName, "궁서");

	logFont.lfHeight = 120;
	titleFont[0] = CreateFontIndirectA(&logFont);
	logFont.lfHeight = 40;
	titleFont[1] = CreateFontIndirectA(&logFont);

	MySound::getInstance().playLobbyBGM();
}

Scene4::~Scene4()
{
	DeleteObject(titleFont[0]);
	DeleteObject(titleFont[1]);
}

void Scene4::initialize()
{
}

void Scene4::update(float elapsedTime)
{
	// 배경 구름 이동
	cloudPosXf -= 100.f * elapsedTime;
	if (cloudPosXf < 0.f) {
		cloudPosXf += W_WIDTH;
	}
}

void Scene4::draw(HDC hdc) const
{
	background.MyDraw(hdc, RECT{ 0, 0, W_WIDTH, W_HEIGHT });

	float value = 1.f - cloudPosXf / float(W_WIDTH);
	int imgWidth = cloud.getWidth();
	int imgHeight = cloud.getHeight();
	cloud.MyDraw(hdc, RECT{ 0, 0, int(cloudPosXf), W_HEIGHT }, RECT{ int(value * imgWidth), 0, imgWidth, imgHeight }, false, false, 0x7f);
	cloud.MyDraw(hdc, RECT{ int(cloudPosXf), 0, W_WIDTH, W_HEIGHT }, RECT{ 0, 0, int(value * imgWidth), imgHeight }, false, false, 0x7f);

	title.MyDraw(hdc, RECT{ 200, 250, 200 + 810, 250 + 348 });		// 405, 174

	{	// 최종 점수 출력
		SetTextColor(hdc, RGB(255, 64, 0));
		HFONT oldFont = (HFONT)SelectObject(hdc, titleFont[0]);
		RECT rc{ 100, 100, 1100, 200 };
		std::string str = "SCORE : " + std::to_string(playerScore);
		DrawTextA(hdc, str.c_str(), int(str.size()), &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		SelectObject(hdc, oldFont);
		SetTextColor(hdc, 0);		// 원상복구
	}

	{	// 안내문
		SetTextColor(hdc, RGB(243, 64, 127));
		HFONT oldFont = (HFONT)SelectObject(hdc, titleFont[1]);
		RECT rc{ 300, 650, 900, 750 };
		std::string str = "Press Any Key To ReStart";
		DrawTextA(hdc, str.c_str(), int(str.size()), &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		SelectObject(hdc, oldFont);
		SetTextColor(hdc, 0);		// 원상복구
	}
}

void Scene4::destroy()
{
}

bool Scene4::onClear() const
{
	return isNext;
}

void Scene4::processWindowMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
		MessageBoxA(hWnd, "Wrong Window Message On Scene4", nullptr, MB_OK);
		break;
	}
}
