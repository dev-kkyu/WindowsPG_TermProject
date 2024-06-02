#include "MyImage.h"

MyImage::MyImage()
{
}

MyImage::~MyImage()
{
}

HRESULT MyImage::Load(std::wstring filename)
{
	return CImage::Load(filename.c_str());
}

void MyImage::MyDraw(HDC hdc, const RECT& dstRect, bool reverseX, bool reverseY)
{
	const int imgWidth = CImage::GetWidth();
	const int imgHeight = CImage::GetHeight();

	// Alpha 채널을 가진 경우
	if (32 == CImage::GetBPP()) {
		// 좌우/상하 반전 효과를 위한 중간 메모리 DC 생성
		HDC mDC = ::CreateCompatibleDC(hdc);
		HBITMAP hBitmap = ::CreateCompatibleBitmap(hdc, imgWidth, imgHeight);
		::SelectObject(mDC, hBitmap);

		// 좌우, 상하 반전을 위해 메모리 DC에 복사한다.
		if (reverseX and reverseY) {
			CImage::StretchBlt(mDC, RECT{ 0, 0, imgWidth, imgHeight }, RECT{ imgWidth, imgHeight, 0, 0 }, SRCCOPY);
		}
		else if (reverseX) {
			CImage::StretchBlt(mDC, RECT{ 0, 0, imgWidth, imgHeight }, RECT{ imgWidth, 0, 0, imgHeight }, SRCCOPY);
		}
		else if (reverseY) {
			CImage::StretchBlt(mDC, RECT{ 0, 0, imgWidth, imgHeight }, RECT{ 0, imgHeight, imgWidth, 0 }, SRCCOPY);
		}
		else {
			CImage::BitBlt(mDC, 0, 0, SRCCOPY);
		}

		// 복사한 이미지를 화면에 그린다
		BLENDFUNCTION blend;
		blend.BlendOp = AC_SRC_OVER;		// 유일
		blend.BlendFlags = 0;				// 유일
		blend.SourceConstantAlpha = 0xff;	// 0(투명) ~ 255(불투명)	// 기본적으로 투명 채널 존재시 투명도 반영된다.
		blend.AlphaFormat = AC_SRC_ALPHA;	// AC_SRC_ALPHA -> 32비트 비트맵일 때
		::AlphaBlend(hdc, dstRect.left, dstRect.top, dstRect.right - dstRect.left, dstRect.bottom - dstRect.top, mDC, 0, 0, imgWidth, imgHeight, blend);

		// 만든 오브젝트 삭제
		::DeleteObject(hBitmap);
		::DeleteDC(mDC);
	}
	else {
		// 알파 채널이 없는 경우 바로 그린다
		if (reverseX and reverseY) {
			CImage::StretchBlt(hdc, dstRect, RECT{ imgWidth, imgHeight, 0, 0 }, SRCCOPY);
		}
		else if (reverseX) {
			CImage::StretchBlt(hdc, dstRect, RECT{ imgWidth, 0, 0, imgHeight }, SRCCOPY);
		}
		else if (reverseY) {
			CImage::StretchBlt(hdc, dstRect, RECT{ 0, imgHeight, imgWidth, 0 }, SRCCOPY);
		}
		else {
			CImage::StretchBlt(hdc, dstRect, SRCCOPY);
		}
	}
}
