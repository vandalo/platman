#include "pch.h"
#include "Log.h"

#include <stdio.h>
#include <stdlib.h>
#include <memory>

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )

#include "Application.h"

enum main_states
{
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};

Application* App = nullptr;

int main(int argc, char ** argv)
{
	main_states state = MAIN_CREATION;

	while (state != MAIN_EXIT)
	{
		switch (state)
		{
		case MAIN_CREATION:
			App = new Application();
			state = MAIN_START;
			break;
		case MAIN_START:
			if (App->Init() == false)
			{
				LOG("Application Init exits with error -----");
				state = MAIN_EXIT;
			}
			else
			{
				state = MAIN_UPDATE;
			}
			break;
		case MAIN_UPDATE:
			if (App->Update() == false)
			{
				state = MAIN_FINISH;
			}
			break;
		case MAIN_FINISH:
			state = MAIN_EXIT;
			break;
		case MAIN_EXIT:
			break;
		default:
			LOG("Main state not controled");
			SDL_assert(true);
		}
	}

	delete App;
	LOG("Program closed");
	return 0;
}
