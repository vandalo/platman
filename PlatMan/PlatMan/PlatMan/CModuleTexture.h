#pragma once

#include<list>
#include "IModule.h"
#include "Globals.h"

struct SDL_Texture;
class CModuleRender;

class CModuleTexture : public IModule
{
public:
	CModuleTexture();
	~CModuleTexture();

	bool Init() override;
	bool CleanUp() override;

	SDL_Texture* const Load(const char* path);
	void Unload(SDL_Texture* texture);

private:
	CModuleRender& m_moduleRenderer;

	std::list<SDL_Texture*> m_textures;
};