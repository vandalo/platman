#include "Globals.h"
#include "Application.h"
#include "Animation.h"
#include "CFlashScreen.h"
#include "CModuleTexture.h"
#include "CModuleRender.h"

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
	return true;
}

bool CFlashScreen::CleanUp()
{
	LOG("Unloading space scene");
	return true;
}