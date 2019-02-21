#pragma once

#include "pch.h"

#include "IModule.h"

#include "SDL/include/SDL.h"

enum ScreenType
{
	SCREEN,
	POPUP
};

class IModuleScreen : public IModule
{

public:
	IModuleScreen(ScreenType screenType) : m_screenType(screenType) {};
	~IModuleScreen() {};

	bool Init() override { return true; };
	bool Update(const float deltaTime) { return true; };
	bool CleanUp() override { return true; };
	ScreenType GetScreenType() { return m_screenType; };


public:

private:
	ScreenType m_screenType;
};