#include "Globals.h"
#include "Application.h"
#include "Animation.h"
#include "CFlashScreen.h"
#include "CModuleTexture.h"
#include "CModuleRender.h"
#include "CScreenManager.h"
#include "CLevelTestScreen.h"
#include "CPauseScreen.h"

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
	LOG("Loading Flash intro");
	m_background = m_moduleTexture.Load("sprites/backgrounds.png");
	m_moduleRender.m_camera.x = m_moduleRender.m_camera.y = 50;
	return true;
}

bool CFlashScreen::Update(float deltaTime)
{
	////////////////////////
	//To debug move camera//
	////////////////////////
	if (m_moduleInput.GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		m_moduleRender.m_camera.y += 1;

	if (m_moduleInput.GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		m_moduleRender.m_camera.y -= 1;

	if (m_moduleInput.GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		m_moduleRender.m_camera.x += 1;

	if (m_moduleInput.GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		m_moduleRender.m_camera.x -= 1;

	/////////////////////////

	if (m_moduleInput.GetGameControllerButton(SDL_CONTROLLER_BUTTON_A) == KEY_DOWN)
	{
		m_screenManager.Add<CLevelTestScreen>(SCREEN);
	}

	if (m_moduleInput.GetGameControllerButton(SDL_CONTROLLER_BUTTON_B) == KEY_DOWN)
	{
		m_screenManager.Add<CPauseScreen>(POPUP);
	}

	return true;
}

bool CFlashScreen::PostUpdate(float deltaTime)
{
	m_moduleRender.Blit(m_background, 0, 0);
	return true;
}

bool CFlashScreen::CleanUp()
{
	LOG("Unloading Flash scene");
	return true;
}