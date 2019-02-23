#pragma once

#include "pch.h"

#include "IModule.h"
#include "CModuleInput.h"

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


public:

protected:
	CModuleInput& m_moduleInput;
	CScreenManager& m_screenManager;
	ScreenType m_screenType;
};