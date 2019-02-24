#pragma once

#include "IModuleScreen.h"

class CModuleRender;
class CModuleTexture;

class CPauseScreen : public IModuleScreen
{
public:
	CPauseScreen(ScreenType screenType);
	~CPauseScreen();

	bool Init() override;
	bool Update(const float deltaTime) override;
	bool CleanUp() override;

private:
	CModuleRender& m_moduleRender;
	CModuleTexture& m_moduleTexture;
};
