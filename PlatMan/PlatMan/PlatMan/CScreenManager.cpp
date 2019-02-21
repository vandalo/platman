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
	if (!m_listScreen.empty())
	{
		for (IModuleScreen* screen : m_listScreen)
		{
			screen->Update(deltaTime);
		}
	}

	if (m_moduleFadeToBlack.isFading())
	{
		if (m_screenOut)
		{
			if (!m_screenOut->IsEnabled())
			{
				delete m_screenOut;
				m_listScreen.pop_back();
				m_listScreen.push_back(m_screenIn);
			}
		}		
	}

	return true;
}

bool CScreenManager::CleanUp()
{
	return false;
}

void CScreenManager::AddScreen(IModuleScreen * screen)
{
	if (screen->GetScreenType() == ScreenType::SCREEN && !m_moduleFadeToBlack.isFading() && !m_listScreen.empty())
	{
		while (m_listScreen.size() > 1)
		{
			delete m_listScreen.back();
			m_listScreen.pop_back();
		}
		m_screenOut = m_listScreen.empty() ? nullptr : m_listScreen.front();
		m_screenIn = screen;
		m_moduleFadeToBlack.FadeToBlack(screen, m_screenOut, 3.0);
	}
	else
	{
		m_listScreen.push_back(screen);
	}
}
