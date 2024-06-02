#pragma once

#include <atlimage.h>
#include <string>

class MyImage : public CImage
{

public:
	MyImage();
	virtual ~MyImage();

	HRESULT Load(std::wstring filename);
	void MyDraw(HDC hdc, const RECT& dstRect, bool reverseX = false, bool reverseY = false);
};
