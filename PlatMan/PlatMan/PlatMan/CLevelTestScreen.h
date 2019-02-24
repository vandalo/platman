#pragma once

#include "IModuleScreen.h"

class CModuleRender;
class CModuleTexture;
class CPlayer;

class CLevelTestScreen : public IModuleScreen
{
public:
	CLevelTestScreen(ScreenType screenType);
	~CLevelTestScreen();

	bool Init() override;
	bool Update(const float deltaTime) override;
	bool CleanUp() override;

private:
	CModuleRender& m_moduleRender;
	CModuleTexture& m_moduleTexture;
	CPlayer* m_player;
};
