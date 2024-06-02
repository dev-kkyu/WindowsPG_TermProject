#include "GameScene.h"

#include "Define.h"

GameScene::GameScene()
{
	background.Load(L"./Resources/Images/Background/Stage1.png");
}

GameScene::~GameScene()
{
}

void GameScene::initialize()
{
}

void GameScene::update(float elapsedTime)
{
	player.update(elapsedTime);
}

void GameScene::draw(HDC hdc)
{
	background.MyDraw(hdc, RECT{ 0, 0, W_WIDTH, W_HEIGHT });
	player.draw(hdc);
}

void GameScene::destroy()
{
}

void GameScene::processWindowMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Scene::processWindowMessage(hWnd, message, wParam, lParam);
}
