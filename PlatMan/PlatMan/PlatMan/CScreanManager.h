#pragma once

#include "pch.h"

#include <stack>

#include "IModule.h"

#include "SDL/include/SDL.h"

class IModuleScreen;

class CScreanManager
{
public:
	CScreanManager();
	~CScreanManager();

	bool Init();
	bool Update(const float deltaTime);
	bool CleanUp();

	void AddScreen(IModuleScreen* screen);


public:
	std::stack<IModuleScreen*> m_stackScreen;
};