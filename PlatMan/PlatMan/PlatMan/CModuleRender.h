#pragma once

#include "pch.h"

#include "IModule.h"
#include "Globals.h"

#include "SDL/include/SDL_rect.h"

struct SDL_Texture;
struct SDL_Renderer;

class CModuleWindow;

class CModuleRender : public IModule
{
public:
	CModuleRender();
	~CModuleRender();

	bool Init() override;
	bool PreUpdate(float deltaTime) override;
	bool Update(float deltaTime) override;
	bool PostUpdate(float deltaTime) override;
	bool CleanUp() override;

	bool Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section);
	bool Blit(SDL_Texture* texture, int x, int y);
	//bool Print(unsigned int idFont, const char* text, int x, int y, float speed = 1.0f, bool center = true);

public:
	SDL_Renderer* m_renderer = nullptr;
	SDL_Rect m_camera;

private:
	CModuleWindow& m_moduleWindow;
};