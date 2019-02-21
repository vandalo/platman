#include "pch.h"

#include "Application.h"
#include "CScreenManager.h"
#include "IModuleScreen.h"
#include "CModuleFadeToBlack.h"

CScreenManager::CScreenManager() :
	m_moduleFadeToBlack(*App->GetModule<CModuleFadeToBlack>())
{
}

CScreenManager::~CScreenManager()
{
}

bool CScreenManager::Init()
{
	return false;
}

bool CScreenManager::Update(const float deltaTime)
{
	if (!m_stackScreen.empty())
	{
		m_stackScreen.top()->Update(deltaTime);
	}
	return false;
}

bool CScreenManager::CleanUp()
{
	return false;
}

void CScreenManager::AddScreen(IModuleScreen * screen)
{
	if (screen->GetScreenType() == ScreenType::SCREEN && !m_stackScreen.empty() && !m_moduleFadeToBlack.isFading())
	{
		while (m_stackScreen.size() > 1)
		{
			delete m_stackScreen.top();
			m_stackScreen.pop();
		}
		m_moduleFadeToBlack.FadeToBlack(screen, m_stackScreen.top(), 3.0);
		delete m_stackScreen.top();
		m_stackScreen.pop();
	}
	m_stackScreen.push(screen);
}
