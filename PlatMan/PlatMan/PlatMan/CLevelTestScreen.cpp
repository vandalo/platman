#include "Globals.h"
#include "Application.h"
#include "Animation.h"
#include "CLevelTestScreen.h"
#include "CModuleTexture.h"
#include "CModuleRender.h"
#include "CScreenManager.h"
#include "CPlayer.h"

CLevelTestScreen::CLevelTestScreen(ScreenType screenType) :
	IModuleScreen(screenType)
	, m_moduleRender(*App->GetModule<CModuleRender>())
	, m_moduleTexture(*App->GetModule<CModuleTexture>())
{
	Init();
}

CLevelTestScreen::~CLevelTestScreen()
{}

bool CLevelTestScreen::Init()
{
	m_player = Add<CPlayer>();

	LOG("Loading Test intro");
	return true;
}

bool CLevelTestScreen::Update(float deltaTime)
{
	for (IGameObject* gameObject : m_gameObjects)
	{
		gameObject->Update(deltaTime);
	}
	return true;
}

bool CLevelTestScreen::CleanUp()
{
	LOG("Unloading Test scene");
	return true;
}