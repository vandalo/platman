#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "CModuleFadeToBlack.h"
#include "CModuleRender.h"
#include "SDL/include/SDL.h"

CModuleFadeToBlack::CModuleFadeToBlack(bool start_enabled) : 
	m_moduleRenderer(*App->GetModule<CModuleRender>())
	, m_startTime(0)
	, m_totalTime(0)
	, m_fadingIn(true)
	, m_moduleOn(nullptr)
	, m_moduleOff(nullptr)
{}

CModuleFadeToBlack::~CModuleFadeToBlack()
{}

// Load assets
bool CModuleFadeToBlack::Init()
{
	LOG("Preparing Fade Screen");
	SDL_SetRenderDrawBlendMode(m_moduleRenderer.m_renderer, SDL_BLENDMODE_BLEND);
	return true;
}

// Update: draw background
bool CModuleFadeToBlack::Update(const float deltaTime)
{
	if (m_startTime > 0)
	{
		float now = SDL_GetTicks() - m_startTime;
		float normalized = (float)now / (float)m_totalTime;

		if (normalized > 1.0f)
			normalized = 1.0f;

		if (m_fadingIn == false)
			normalized = 1.0f - normalized;

		SDL_SetRenderDrawColor(m_moduleRenderer.m_renderer, 0, 0, 0, (Uint8)(normalized * 255.0f));
		SDL_RenderFillRect(m_moduleRenderer.m_renderer, NULL);

		if (m_moduleOff == nullptr && m_moduleOn != nullptr)
		{
			m_moduleOn->Enable();
			m_moduleOn = nullptr;
		}

		if (now >= m_totalTime)
		{
			if (m_fadingIn == true)
			{
				if (m_moduleOff != nullptr)
					m_moduleOff->Disable();
				m_moduleOn->Enable();

				m_totalTime += m_totalTime;
				m_startTime = static_cast<float>(SDL_GetTicks());
				m_fadingIn = false;
			}
			else
			{
				m_startTime = 0;
			}
		}
	}

	return true;
}

// Fade to black. At mid point deactivate one module, then activate the other
void CModuleFadeToBlack::FadeToBlack(IModule* m_moduleOn, IModule* m_moduleOff, float time)
{
	m_fadingIn = (m_moduleOff != nullptr) ? true : false;
	m_startTime = static_cast<float>(SDL_GetTicks());
	m_totalTime = time  * 0.5f * 1000.0f;

	this->m_moduleOn = m_moduleOn;
	this->m_moduleOff = m_moduleOff;
}

bool CModuleFadeToBlack::isFading() const
{
	return m_startTime > 0;
}