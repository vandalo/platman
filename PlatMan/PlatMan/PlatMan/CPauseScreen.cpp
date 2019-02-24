#include "Globals.h"
#include "Application.h"
#include "Animation.h"
#include "CPauseScreen.h"
#include "CModuleTexture.h"
#include "CModuleRender.h"
#include "CScreenManager.h"

CPauseScreen::CPauseScreen(ScreenType screenType) :
	IModuleScreen(screenType)
	, m_moduleRender(*App->GetModule<CModuleRender>())
	, m_moduleTexture(*App->GetModule<CModuleTexture>())
{
	Init();
}

CPauseScreen::~CPauseScreen()
{}

bool CPauseScreen::Init()
{
	LOG("Loading Pause intro");
	return true;
}

bool CPauseScreen::Update(float deltaTime)
{
	if (m_moduleInput.GetGameControllerButton(SDL_CONTROLLER_BUTTON_Y) == KEY_DOWN)
	{
		Close();
	}

	return true;
}

bool CPauseScreen::CleanUp()
{
	LOG("Unloading Pause scene");
	return true;
}