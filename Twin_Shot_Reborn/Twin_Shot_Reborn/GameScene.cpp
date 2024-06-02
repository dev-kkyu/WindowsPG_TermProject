#include "GameScene.h"

GameScene::GameScene()
{
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
	player.draw(hdc);
}

void GameScene::destroy()
{
}

void GameScene::processWindowMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Scene::processWindowMessage(hWnd, message, wParam, lParam);
}
