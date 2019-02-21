#include "Globals.h"
#include "Application.h"
#include "CModuleRender.h"
#include "CModuleTexture.h"
#include "SDL/include/SDL.h"

#include "SDL_image/include/SDL_image.h"
//#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )

using namespace std;

CModuleTexture::CModuleTexture() :
	m_moduleRenderer(*App->GetModule<CModuleRender>())
{
}

// Destructor
CModuleTexture::~CModuleTexture()
{
	IMG_Quit();
}

// Called before render is available
bool CModuleTexture::Init()
{
	LOG("Init Image library");
	bool ret = true;

	// load support for the PNG image format
	int flags = IMG_INIT_PNG;
	int init = IMG_Init(flags);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize Image lib. IMG_Init: %s", IMG_GetError());
		ret = false;
	}

	return ret;
}

// Called before quitting
bool CModuleTexture::CleanUp()
{
	LOG("Freeing texture and Image library");

	for (list<SDL_Texture*>::iterator it = m_textures.begin(); it != m_textures.end(); ++it)
		SDL_DestroyTexture(*it);

	m_textures.clear();
	return true;
}

// Load new texture from file path
SDL_Texture* const CModuleTexture::Load(const char* path)
{
	SDL_Texture* texture = nullptr;
	SDL_Surface* surface = IMG_Load(path);

	if (surface == nullptr)
	{
		LOG("Could not load surface with path: %s. IMG_Load: %s", path, IMG_GetError());
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(m_moduleRenderer.m_renderer, surface);

		if (texture == nullptr)
		{
			LOG("Unable to create texture from surface! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			m_textures.push_back(texture);
		}

		SDL_FreeSurface(surface);
	}

	return texture;
}

// Free texture from memory
void CModuleTexture::Unload(SDL_Texture* texture)
{
	for (list<SDL_Texture*>::iterator it = m_textures.begin(); it != m_textures.end(); ++it)
	{
		if (*it == texture)
		{
			SDL_DestroyTexture(*it);
			m_textures.erase(it);
			break;
		}
	}
}