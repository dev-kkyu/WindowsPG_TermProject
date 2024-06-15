#pragma once

#include "GameObject.h"
#include "MyImage.h"

#include <array>
#include <vector>

class ItemObject : public GameObject
{
public:
	enum ItemType { HP, S_COIN, G_COIN };

private:
	static bool isImageLoaded;
	static std::array<std::vector<MyImage>, 3> images;

private:
	ItemType itemType;

	float actionPerSecond;	// �ʴ� �׼��� �ݺ� Ƚ�� (�׼� : ���� �ִϸ��̼��� �̹��� ����)
	float nowFrameIdxF;		// ���� ������ �ε��� (int�� ��ȯ �� ���)

public:
	ItemObject(POINT iPos);
	virtual ~ItemObject();

	virtual void update(float elapsedTime);
	virtual void draw(HDC hdc, int windowLeft = 0) const;

	ItemType getItemType() const;

};

