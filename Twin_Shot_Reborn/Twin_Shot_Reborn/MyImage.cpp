#include "MyImage.h"

MyImage::MyImage()
	: image{ std::make_unique<CImage>() }
{
}

MyImage::~MyImage()
{
}

MyImage::MyImage(MyImage&& other) noexcept
	: image{ std::move(other.image) }
{
}

MyImage& MyImage::operator=(MyImage&& other) noexcept
{
	if (this != &other) {
		image = std::move(other.image);
	}
	return *this;
}

HRESULT MyImage::Load(std::wstring filename)
{
	return image->Load(filename.c_str());
}

void MyImage::MyDraw(HDC hdc, const RECT& dstRect, bool reverseX, bool reverseY, BYTE bSrcAlpha) const
{
	const int imgWidth = image->GetWidth();
	const int imgHeight = image->GetHeight();

	// Alpha 채널을 가진 경우
	if (32 == image->GetBPP()) {
		// 좌우/상하 반전 효과를 위한 중간 메모리 DC 생성
		HDC mDC = ::CreateCompatibleDC(hdc);
		HBITMAP hBitmap = ::CreateCompatibleBitmap(hdc, imgWidth, imgHeight);
		::SelectObject(mDC, hBitmap);

		// 좌우, 상하 반전을 위해 메모리 DC에 복사한다.
		if (reverseX and reverseY) {
			image->StretchBlt(mDC, RECT{ 0, 0, imgWidth, imgHeight }, RECT{ imgWidth, imgHeight, 0, 0 }, SRCCOPY);
		}
		else if (reverseX) {
			image->StretchBlt(mDC, RECT{ 0, 0, imgWidth, imgHeight }, RECT{ imgWidth, 0, 0, imgHeight }, SRCCOPY);
		}
		else if (reverseY) {
			image->StretchBlt(mDC, RECT{ 0, 0, imgWidth, imgHeight }, RECT{ 0, imgHeight, imgWidth, 0 }, SRCCOPY);
		}
		else {
			image->BitBlt(mDC, 0, 0, SRCCOPY);
		}

		// 복사한 이미지를 화면에 그린다
		BLENDFUNCTION blend;
		blend.BlendOp = AC_SRC_OVER;			// 유일
		blend.BlendFlags = 0;					// 유일
		blend.SourceConstantAlpha = bSrcAlpha;	// 0(투명) ~ 255(불투명)	// 기본적으로 투명 채널 존재시 투명도 반영된다.
		blend.AlphaFormat = AC_SRC_ALPHA;		// AC_SRC_ALPHA -> 32비트 비트맵일 때
		::AlphaBlend(hdc, dstRect.left, dstRect.top, dstRect.right - dstRect.left, dstRect.bottom - dstRect.top, mDC, 0, 0, imgWidth, imgHeight, blend);

		// 만든 오브젝트 삭제
		::DeleteObject(hBitmap);
		::DeleteDC(mDC);
	}
	else {
		// 알파 채널이 없는 경우 바로 그린다
		if (reverseX and reverseY) {
			image->StretchBlt(hdc, dstRect, RECT{ imgWidth, imgHeight, 0, 0 }, SRCCOPY);
		}
		else if (reverseX) {
			image->StretchBlt(hdc, dstRect, RECT{ imgWidth, 0, 0, imgHeight }, SRCCOPY);
		}
		else if (reverseY) {
			image->StretchBlt(hdc, dstRect, RECT{ 0, imgHeight, imgWidth, 0 }, SRCCOPY);
		}
		else {
			image->StretchBlt(hdc, dstRect, SRCCOPY);
		}
	}
}

void MyImage::MyDraw(HDC hdc, const RECT& dstRect, int windowLeft, bool reverseX, bool reverseY, BYTE bSrcAlpha) const
{
	MyDraw(hdc, RECT{ dstRect.left - windowLeft , dstRect.top, dstRect.right - windowLeft, dstRect.bottom }, reverseX, reverseY);
}

void MyImage::MyDraw(HDC hdc, const RECT& dstRect, const RECT& srcRect, bool reverseX, bool reverseY, BYTE bSrcAlpha) const
{
	const int imgWidth = srcRect.right - srcRect.left;
	const int imgHeight = srcRect.bottom - srcRect.top;

	// Alpha 채널을 가진 경우
	if (32 == image->GetBPP()) {
		// 좌우/상하 반전 효과를 위한 중간 메모리 DC 생성
		HDC mDC = ::CreateCompatibleDC(hdc);
		HBITMAP hBitmap = ::CreateCompatibleBitmap(hdc, imgWidth, imgHeight);
		::SelectObject(mDC, hBitmap);

		// 좌우, 상하 반전을 위해 메모리 DC에 복사한다.
		if (reverseX and reverseY) {
			image->StretchBlt(mDC, RECT{ 0, 0, imgWidth, imgHeight }, RECT{ srcRect.right,srcRect.bottom, srcRect.left, srcRect.top }, SRCCOPY);
		}
		else if (reverseX) {
			image->StretchBlt(mDC, RECT{ 0, 0, imgWidth, imgHeight }, RECT{ srcRect.right, srcRect.top, srcRect.left, srcRect.bottom }, SRCCOPY);
		}
		else if (reverseY) {
			image->StretchBlt(mDC, RECT{ 0, 0, imgWidth, imgHeight }, RECT{ srcRect.left, srcRect.bottom, srcRect.right, srcRect.top }, SRCCOPY);
		}
		else {
			image->BitBlt(mDC, srcRect.left, srcRect.top, SRCCOPY);
		}

		// 복사한 이미지를 화면에 그린다
		BLENDFUNCTION blend;
		blend.BlendOp = AC_SRC_OVER;			// 유일
		blend.BlendFlags = 0;					// 유일
		blend.SourceConstantAlpha = bSrcAlpha;	// 0(투명) ~ 255(불투명)	// 기본적으로 투명 채널 존재시 투명도 반영된다.
		blend.AlphaFormat = AC_SRC_ALPHA;		// AC_SRC_ALPHA -> 32비트 비트맵일 때
		::AlphaBlend(hdc, dstRect.left, dstRect.top, dstRect.right - dstRect.left, dstRect.bottom - dstRect.top, mDC, 0, 0, imgWidth, imgHeight, blend);

		// 만든 오브젝트 삭제
		::DeleteObject(hBitmap);
		::DeleteDC(mDC);
	}
	else {
		// 알파 채널이 없는 경우 바로 그린다
		if (reverseX and reverseY) {
			image->StretchBlt(hdc, dstRect, RECT{ srcRect.right,srcRect.bottom, srcRect.left, srcRect.top }, SRCCOPY);
		}
		else if (reverseX) {
			image->StretchBlt(hdc, dstRect, RECT{ srcRect.right, srcRect.top, srcRect.left, srcRect.bottom }, SRCCOPY);
		}
		else if (reverseY) {
			image->StretchBlt(hdc, dstRect, RECT{ srcRect.left, srcRect.bottom, srcRect.right, srcRect.top }, SRCCOPY);
		}
		else {
			image->StretchBlt(hdc, dstRect, srcRect, SRCCOPY);
		}
	}
}

void MyImage::MyDraw(HDC hdc, const RECT& dstRect, const RECT& srcRect, int windowLeft, bool reverseX, bool reverseY, BYTE bSrcAlpha) const
{
	MyDraw(hdc, RECT{ dstRect.left - windowLeft , dstRect.top, dstRect.right - windowLeft, dstRect.bottom }, srcRect, reverseX, reverseY);
}

int MyImage::getWidth() const
{
	return image->GetWidth();
}

int MyImage::getHeight() const
{
	return image->GetHeight();
}
