#include "pch.h"

#include "Application.h"
#include "CScreenManager.h"
#include "CModuleFadeToBlack.h"
#include "IModuleScreen.h"

CScreenManager::CScreenManager() :
	m_moduleFadeToBlack(*App->GetModule<CModuleFadeToBlack>())
	, m_screenIn(nullptr)
	, m_screenOut(nullptr)
	, m_swapingScreen(false)
{
}

CScreenManager::~CScreenManager()
{
}

bool CScreenManager::Init()
{
	return false;
}

bool CScreenManager::Update(float deltaTime)
{
	if (!m_moduleFadeToBlack.isFading())
	{
		m_listScreen.back()->Update(deltaTime);
	}
	
	return true;
}

bool CScreenManager::PostUpdate(float deltaTime)
{
	if (!m_listScreen.empty())
	{
		for (IModuleScreen* screen : m_listScreen)
		{
			screen->PostUpdate(deltaTime);
		}
	}

	FadingOut();

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
			CloseScreen();
		}
		m_screenOut = m_listScreen.empty() ? nullptr : m_listScreen.front();
		m_screenIn = screen;
		m_moduleFadeToBlack.FadeToBlack(screen, m_screenOut, 3.0f);
	}
	else
	{
		m_moduleFadeToBlack.FadeToBlack(screen, nullptr, 0.0f);
		m_listScreen.push_back(screen);
		m_swapingScreen = false;
	}
}

void CScreenManager::FadingOut()
{
	if (m_moduleFadeToBlack.isFading())
	{
		if (m_screenOut)
		{
			if (!m_screenOut->IsEnabled())
			{
				CloseScreen();
				m_listScreen.push_back(m_screenIn);
				m_swapingScreen = false;
			}
		}
	}
}

bool CScreenManager::CloseScreen()
{
	delete m_listScreen.back();
	m_listScreen.pop_back();
	return true;
}
