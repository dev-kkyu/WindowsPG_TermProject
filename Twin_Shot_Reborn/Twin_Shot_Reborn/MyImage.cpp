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

	// Alpha ä���� ���� ���
	if (32 == CImage::GetBPP()) {
		// �¿�/���� ���� ȿ���� ���� �߰� �޸� DC ����
		HDC mDC = ::CreateCompatibleDC(hdc);
		HBITMAP hBitmap = ::CreateCompatibleBitmap(hdc, imgWidth, imgHeight);
		::SelectObject(mDC, hBitmap);

		// �¿�, ���� ������ ���� �޸� DC�� �����Ѵ�.
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

		// ������ �̹����� ȭ�鿡 �׸���
		BLENDFUNCTION blend;
		blend.BlendOp = AC_SRC_OVER;		// ����
		blend.BlendFlags = 0;				// ����
		blend.SourceConstantAlpha = 0xff;	// 0(����) ~ 255(������)	// �⺻������ ���� ä�� ����� ���� �ݿ��ȴ�.
		blend.AlphaFormat = AC_SRC_ALPHA;	// AC_SRC_ALPHA -> 32��Ʈ ��Ʈ���� ��
		::AlphaBlend(hdc, dstRect.left, dstRect.top, dstRect.right - dstRect.left, dstRect.bottom - dstRect.top, mDC, 0, 0, imgWidth, imgHeight, blend);

		// ���� ������Ʈ ����
		::DeleteObject(hBitmap);
		::DeleteDC(mDC);
	}
	else {
		// ���� ä���� ���� ��� �ٷ� �׸���
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
