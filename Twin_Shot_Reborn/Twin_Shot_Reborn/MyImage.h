#pragma once

#include <atlimage.h>
#include <string>
#include <memory>

class MyImage
{
private:
	std::unique_ptr<CImage> image;

public:
	MyImage();
	~MyImage();

	MyImage(const MyImage& other) = delete;
	MyImage& operator=(const MyImage& other) = delete;
	MyImage(MyImage&& other) noexcept;
	MyImage& operator=(MyImage&& other) noexcept;

	HRESULT Load(std::wstring filename);
	void MyDraw(HDC hdc, const RECT& dstRect, const RECT& srcRect, bool reverseX = false, bool reverseY = false, BYTE bSrcAlpha = 0xff) const;
	void MyDraw(HDC hdc, const RECT& dstRect, const RECT& srcRect, int windowLeft, bool reverseX = false, bool reverseY = false, BYTE bSrcAlpha = 0xff) const;
	void MyDraw(HDC hdc, const RECT& dstRect, bool reverseX = false, bool reverseY = false, BYTE bSrcAlpha = 0xff) const;
	void MyDraw(HDC hdc, const RECT& dstRect, int windowLeft, bool reverseX = false, bool reverseY = false, BYTE bSrcAlpha = 0xff) const;	// 스크롤링 전용

	int getWidth() const;
	int getHeight() const;
};

