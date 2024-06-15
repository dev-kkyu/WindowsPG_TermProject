#pragma once

#include <Windows.h>
#include <vector>

#include "MyImage.h"
#include "TileObject.h"
#include "PlayerObject.h"
#include "ItemObject.h"

class SceneBase
{
protected:
	static int playerScore;

protected:
	MyImage background;
	MyImage cloud;

	float cloudPosXf;

	std::vector<TileObject> tiles;
	std::vector<TileObject> nonBlockTiles;

	std::list<ItemObject> items;	// 맵에 존재하는 아이템

	PlayerObject player;
	std::list<ArrowObject> arrows;	// 플레이어가 쏜 화살 중 벽에 박힌 화살 (player.arrows 를 단순 복사)

public:
	SceneBase();
	virtual ~SceneBase();

	virtual void initialize() = 0;
	virtual void update(float elapsedTime) = 0;
	virtual void draw(HDC hdc) const = 0;
	virtual void destroy() = 0;

	virtual bool onClear() const = 0;
	bool getPlayerDead() const;

	virtual void processWindowMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;

};

