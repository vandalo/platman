#include "CScreanManager.h"
#include "IModuleScreen.h"

CScreanManager::CScreanManager()
{
}

CScreanManager::~CScreanManager()
{
}

bool CScreanManager::Init()
{
	return false;
}

bool CScreanManager::Update(const float deltaTime)
{
	if (!m_stackScreen.empty())
	{
		m_stackScreen.top()->Update(deltaTime);
	}
	return false;
}

bool CScreanManager::CleanUp()
{
	return false;
}

void CScreanManager::AddScreen(IModuleScreen * screen)
{
	if (screen->GetScreenType() == ScreenType::SCREEN && !m_stackScreen.empty())
	{
		while (m_stackScreen.size() > 1)
		{
			delete m_stackScreen.top();
		}
		delete m_stackScreen.top();
	}
	m_stackScreen.push(screen);
}
