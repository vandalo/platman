#pragma once

#include "pch.h"

#include <stack>

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
	std::stack<IModuleScreen*> m_stackScreen;
};