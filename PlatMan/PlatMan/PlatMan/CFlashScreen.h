#pragma once

#include "IModuleScreen.h"

class CModuleRender;
class CModuleTexture;

class CFlashScreen : public IModuleScreen
{
public:
	CFlashScreen(ScreenType screenType);
	~CFlashScreen();

	bool Init() override;
	bool Update(const float deltaTime) override;
	bool CleanUp() override;

private:
	CModuleRender& m_moduleRender;
	CModuleTexture& m_moduleTexture;
	SDL_Texture *m_background = nullptr;
};