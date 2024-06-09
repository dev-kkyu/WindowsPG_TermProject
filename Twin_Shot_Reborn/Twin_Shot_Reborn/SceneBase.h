#pragma once

#include <Windows.h>
#include <vector>

#include "MyImage.h"
#include "TileObject.h"
#include "PlayerObject.h"

class SceneBase
{
protected:
	MyImage background;
	MyImage cloud;

	int cloudPosX = 0;

	std::vector<TileObject> tiles;
	std::vector<TileObject> nonBlockTiles;

	PlayerObject player;
	std::list<ArrowObject> arrows;	// �÷��̾ �� ȭ�� �� ���� ���� ȭ�� (player.arrows �� �ܼ� ����)

public:
	SceneBase();
	virtual ~SceneBase();

	virtual void initialize() = 0;
	virtual void update(float elapsedTime) = 0;
	virtual void draw(HDC hdc) const = 0;
	virtual void destroy() = 0;

	virtual void processWindowMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;

};

