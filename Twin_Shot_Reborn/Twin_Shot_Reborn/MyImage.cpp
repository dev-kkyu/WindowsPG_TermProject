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

	// Alpha ä���� ���� ���
	if (32 == image->GetBPP()) {
		// �¿�/���� ���� ȿ���� ���� �߰� �޸� DC ����
		HDC mDC = ::CreateCompatibleDC(hdc);
		HBITMAP hBitmap = ::CreateCompatibleBitmap(hdc, imgWidth, imgHeight);
		::SelectObject(mDC, hBitmap);

		// �¿�, ���� ������ ���� �޸� DC�� �����Ѵ�.
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

		// ������ �̹����� ȭ�鿡 �׸���
		BLENDFUNCTION blend;
		blend.BlendOp = AC_SRC_OVER;			// ����
		blend.BlendFlags = 0;					// ����
		blend.SourceConstantAlpha = bSrcAlpha;	// 0(����) ~ 255(������)	// �⺻������ ���� ä�� ����� ���� �ݿ��ȴ�.
		blend.AlphaFormat = AC_SRC_ALPHA;		// AC_SRC_ALPHA -> 32��Ʈ ��Ʈ���� ��
		::AlphaBlend(hdc, dstRect.left, dstRect.top, dstRect.right - dstRect.left, dstRect.bottom - dstRect.top, mDC, 0, 0, imgWidth, imgHeight, blend);

		// ���� ������Ʈ ����
		::DeleteObject(hBitmap);
		::DeleteDC(mDC);
	}
	else {
		// ���� ä���� ���� ��� �ٷ� �׸���
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

	// Alpha ä���� ���� ���
	if (32 == image->GetBPP()) {
		// �¿�/���� ���� ȿ���� ���� �߰� �޸� DC ����
		HDC mDC = ::CreateCompatibleDC(hdc);
		HBITMAP hBitmap = ::CreateCompatibleBitmap(hdc, imgWidth, imgHeight);
		::SelectObject(mDC, hBitmap);

		// �¿�, ���� ������ ���� �޸� DC�� �����Ѵ�.
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

		// ������ �̹����� ȭ�鿡 �׸���
		BLENDFUNCTION blend;
		blend.BlendOp = AC_SRC_OVER;			// ����
		blend.BlendFlags = 0;					// ����
		blend.SourceConstantAlpha = bSrcAlpha;	// 0(����) ~ 255(������)	// �⺻������ ���� ä�� ����� ���� �ݿ��ȴ�.
		blend.AlphaFormat = AC_SRC_ALPHA;		// AC_SRC_ALPHA -> 32��Ʈ ��Ʈ���� ��
		::AlphaBlend(hdc, dstRect.left, dstRect.top, dstRect.right - dstRect.left, dstRect.bottom - dstRect.top, mDC, 0, 0, imgWidth, imgHeight, blend);

		// ���� ������Ʈ ����
		::DeleteObject(hBitmap);
		::DeleteDC(mDC);
	}
	else {
		// ���� ä���� ���� ��� �ٷ� �׸���
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
