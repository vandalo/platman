#include "pch.h"

#include "Application.h"
#include "IModule.h"

#include "CModuleInput.h"
#include "CModuleWindow.h"
#include "CModuleRender.h"
#include "CModuleTexture.h"
#include "CFlashScreen.h"
#include "CModuleFadeToBlack.h"

Application::Application()
{
	deltaTime = 0;
}

Application::~Application()
{}

bool Application::Init()
{
	CModuleInput* moduleInput = Add<CModuleInput>();
	moduleInput->Init();

	CModuleWindow* moduleWindow = Add<CModuleWindow>();
	moduleWindow->Init();

	CModuleRender* moduleRender = Add<CModuleRender>();
	moduleRender->Init();

	CModuleTexture* moduleTexture = Add<CModuleTexture>();
	moduleTexture->Init();

	CModuleFadeToBlack* moduleFadeToBlack = Add<CModuleFadeToBlack>();
	moduleFadeToBlack->Init();

	m_screanManager = new CScreenManager();

	bool ret = true;

	for (auto& module : m_modules)
	{
		ret = module.second->Start();
	}

	m_screanManager->Add<CFlashScreen>(SCREEN);

	return ret;
}

bool Application::Update()
{
	bool ret = true;
	clock_t now = clock();
	deltaTime += float(now - timer) / CLOCKS_PER_SEC;

	if (deltaTime > 1 / FPS) {
		timer = now;

		for (auto& module : m_modules)
		{
			ret = module.second->PreUpdate(deltaTime);
		}

		//Updates the screans before update modules
		if (m_screanManager)
		{
			m_screanManager->Update(deltaTime);
			m_screanManager->PostUpdate(deltaTime);
		}

		for (auto& module : m_modules)
		{
			ret = module.second->Update(deltaTime);
		}

		for (auto& module : m_modules)
		{
			ret = module.second->PostUpdate(deltaTime);
		}
		deltaTime = 0;
	}

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (auto& module : m_modules)
	{
		delete module.second.get();
	}

	return ret;
}