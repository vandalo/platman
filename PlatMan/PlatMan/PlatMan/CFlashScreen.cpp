#include "Globals.h"
#include "Application.h"
#include "Animation.h"
#include "CFlashScreen.h"
#include "CModuleTexture.h"
#include "CModuleRender.h"
#include "CScreenManager.h"
#include "CLevelTestScreen.h"

CFlashScreen::CFlashScreen(ScreenType screenType) :
	IModuleScreen(screenType)
	, m_moduleRender(*App->GetModule<CModuleRender>())
	, m_moduleTexture(*App->GetModule<CModuleTexture>())
{
	Init();
}

CFlashScreen::~CFlashScreen()
{}

bool CFlashScreen::Init()
{
	LOG("Loading space intro");
	m_background = m_moduleTexture.Load("sprites/backgrounds.png");
	return true;
}

bool CFlashScreen::Update(float deltaTime)
{
	m_moduleRender.Blit(m_background, 0, 0);

	if (m_moduleInput.GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		CLevelTestScreen* levelTestScreen = new CLevelTestScreen(SCREEN);
		//CFlashScreen* levelTestScreen = new CFlashScreen(SCREEN);
		m_screenManager.AddScreen(levelTestScreen);
	}
	return true;
}

bool CFlashScreen::CleanUp()
{
	LOG("Unloading space scene");
	return true;
}