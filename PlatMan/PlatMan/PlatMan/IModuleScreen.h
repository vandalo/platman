#pragma once

#include "pch.h"

#include "IModule.h"
#include "CModuleInput.h"
#include "IGameObject.h"

#include <list>

#include "SDL/include/SDL.h"

class IModuleScreen : public IModule
{

public:
	IModuleScreen(ScreenType screenType) : m_screenType(screenType)
	, m_moduleInput(*App->GetModule<CModuleInput>())
	, m_screenManager(*App->GetScreenManager()) {};

	~IModuleScreen() {};

	bool Init() override { return true; };
	bool Update(const float deltaTime) { return true; };
	bool CleanUp() override { return true; };
	ScreenType GetScreenType() { return m_screenType; };

	void AddGameObject(IGameObject* gameObject)
	{
		m_gameObjects.push_back(gameObject);
	}

	template<class T>
	T* Add()
	{
		T* gameObject = new T();
		AddGameObject(gameObject);
		return gameObject;
	}

protected:
	bool Close()
	{
		return m_screenManager.CloseScreen();
	};

	std::list<IGameObject*> m_gameObjects;
	CModuleInput& m_moduleInput;
	CScreenManager& m_screenManager;
	ScreenType m_screenType;

};