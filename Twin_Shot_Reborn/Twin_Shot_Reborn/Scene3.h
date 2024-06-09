#pragma once

#include "SceneBase.h"
#include "BossObject.h"

class Scene3 : public SceneBase
{
private:
	BossObject boss;

public:
	Scene3();
	virtual ~Scene3();

	virtual void initialize() override;
	virtual void update(float elapsedTime) override;
	virtual void draw(HDC hdc) const override;
	virtual void destroy() override;

	virtual bool onClear() const override;

	virtual void processWindowMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

};

