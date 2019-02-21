#include "Globals.h"
#include "Application.h"
#include "CModuleRender.h"
#include "CModuleWindow.h"
//#include "ModuleInput.h"
//#include "ModuleFont.h"
#include "SDL/include/SDL.h"

//#include "SDL_gfx/include/sdl2_gfxprimitives.h"

//#pragma comment( lib, "SDL_gfx/libx86/SDL2_gfx.lib" )

CModuleRender::CModuleRender() :
	m_moduleWindow(*App->GetModule<CModuleWindow>())
{
	m_camera.x = m_camera.y = 0;
	m_camera.w = SCREEN_WIDTH * SCREEN_SIZE;
	m_camera.h = SCREEN_HEIGHT * SCREEN_SIZE;
}

// Destructor
CModuleRender::~CModuleRender()
{}

// Called before render is available
bool CModuleRender::Init()
{
	LOG("Creating Renderer context");
	bool ret = true;
	Uint32 flags = 0;

	if (VSYNC == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

	m_renderer = SDL_CreateRenderer(m_moduleWindow.m_window, -1, flags);

	if (m_renderer == nullptr)
	{
		LOG("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool CModuleRender::PreUpdate(float deltaTime)
{
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(m_renderer);
	return true;
}

bool CModuleRender::Update(const float deltaTime)
{
	// debug camera
	/*int speed = 1;

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->renderer->camera.y += speed;

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->renderer->camera.y -= speed;

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->renderer->camera.x += speed;

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->renderer->camera.x -= speed;*/

	return true;
}

bool CModuleRender::PostUpdate(float deltaTime)
{
	SDL_RenderPresent(m_renderer);
	return true;
}

bool CModuleRender::CleanUp()
{
	LOG("Destroying renderer");

	//Destroy window
	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
	}

	return true;
}

bool CModuleRender::Blit(SDL_Texture* texture, int x, int y)
{
	return Blit(texture, x, y, nullptr);
}

bool CModuleRender::Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section)
{
	bool ret = true;
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;

	if (section != NULL)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}

	if (SDL_RenderCopy(m_renderer, texture, section, &rect) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

/*bool CModuleRender::Print(unsigned int idFont, const char * text, int x, int y, float speed, bool center)
{
	bool ret = true;

	/*SDL_Rect leter;
	SDL_Rect position;
	Font font = App->font->fonts[idFont];
	if (center) {
		position.y = y - (font.heigth / 2);
		position.x = x - (strlen(text) * font.width / 2) - font.width;
	}

	else {
		position.x = x;
		position.y = y;
	}


	for (int i = 0; text[i] != '\0'; i++) {
		int value = font.fontMap.find(text[i])->second;
		leter.h = font.heigth;
		leter.w = font.width;
		leter.x = value;
		leter.y = font.y;
		position.w = leter.w;
		position.h = leter.h;
		position.x += font.width;
		if (SDL_RenderCopy(renderer, font.surface, &leter, &position) != 0)
		{
			LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
			ret = false;
		}
	}
	return ret;
}*/