#pragma once

#include "IModule.h"
#include "Globals.h"

class CModuleRender;

class CModuleFadeToBlack : public IModule
{
public:
	CModuleFadeToBlack(bool start_enabled = true);
	~CModuleFadeToBlack();

	bool Init() override;
	bool Update(const float deltaTime) override;
	void FadeToBlack(IModule* module_on, IModule* module_off = nullptr, float time = 1.0f);
	bool isFading() const;

private:
	CModuleRender& m_moduleRenderer;

	float m_startTime;
	float m_totalTime;
	bool m_fadingIn;
	IModule* m_moduleOn;
	IModule* m_moduleOff;
};
