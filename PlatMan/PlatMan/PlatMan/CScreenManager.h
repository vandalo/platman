#pragma once

#include "pch.h"

#include <list>

#include "IModule.h"

#include "SDL/include/SDL.h"

class IModuleScreen;
class CModuleFadeToBlack;

class CScreenManager
{
public:
	CScreenManager();
	~CScreenManager();

	bool Init();
	bool Update(const float deltaTime);
	bool CleanUp();

	void AddScreen(IModuleScreen* screen);



public:
	CModuleFadeToBlack& m_moduleFadeToBlack;
	std::list<IModuleScreen*> m_listScreen;

	template<class T>
	void Add(ScreenType type)
	{
		if (!m_swapingScreen)
		{
			m_swapingScreen = true;
			T* screen = new T(type);
			AddScreen(screen);
		}

	}

private:
	IModuleScreen* m_screenIn;
	IModuleScreen* m_screenOut;

	bool m_swapingScreen;
};