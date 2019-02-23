#include "Globals.h"
#include "Application.h"
#include "CModuleInput.h"
#include "SDL/include/SDL.h"
#include "SDL_gamecontroller.h"

#define MAX_KEYS 300

CModuleInput::CModuleInput() : IModule()
{
	m_keyboard = new KeyState[MAX_KEYS];
	memset(m_keyboard, KEY_IDLE, sizeof(KeyState) * MAX_KEYS);
	memset(m_mouse_buttons, KEY_IDLE, sizeof(KeyState) * NUM_MOUSE_BUTTONS);
	memset(m_gamepad_buttons, KEY_IDLE, sizeof(KeyState) * SDL_CONTROLLER_BUTTON_MAX);

	SDL_Init(SDL_INIT_GAMECONTROLLER);

	m_gameController = SDL_GameControllerOpen(0);


}

// Destructor
CModuleInput::~CModuleInput()
{
	RELEASE_ARRAY(m_keyboard);
}

// Called before render is available
bool CModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called before the first frame
bool CModuleInput::Start()
{
	return true;
}

// Called each loop iteration
bool CModuleInput::PreUpdate(float deltaTime)
{
	static SDL_Event event;

	//mouse_motion = { 0, 0 };
	memset(m_windowEvents, false, WE_COUNT * sizeof(bool));

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keys[i] == 1)
		{
			if (m_keyboard[i] == KEY_IDLE)
				m_keyboard[i] = KEY_DOWN;
			else
				m_keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if (m_keyboard[i] == KEY_REPEAT || m_keyboard[i] == KEY_DOWN)
				m_keyboard[i] = KEY_UP;
			else
				m_keyboard[i] = KEY_IDLE;
		}
	}

	for (int i = 0; i < NUM_MOUSE_BUTTONS; ++i)
	{
		if (m_mouse_buttons[i] == KEY_DOWN)
			m_mouse_buttons[i] = KEY_REPEAT;

		if (m_mouse_buttons[i] == KEY_UP)
			m_mouse_buttons[i] = KEY_IDLE;
	}

	for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; ++i)
	{
		if (m_gamepad_buttons[i] == KEY_DOWN)
			m_gamepad_buttons[i] = KEY_REPEAT;

		if (m_gamepad_buttons[i] == KEY_UP)
			m_gamepad_buttons[i] = KEY_IDLE;
	}

	while (SDL_PollEvent(&event) != 0)
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_windowEvents[WE_QUIT] = true;
			break;

		case SDL_WINDOWEVENT:
			switch (event.window.event)
			{
				//case SDL_WINDOWEVENT_LEAVE:
			case SDL_WINDOWEVENT_HIDDEN:
			case SDL_WINDOWEVENT_MINIMIZED:
			case SDL_WINDOWEVENT_FOCUS_LOST:
				m_windowEvents[WE_HIDE] = true;
				break;

				//case SDL_WINDOWEVENT_ENTER:
			case SDL_WINDOWEVENT_SHOWN:
			case SDL_WINDOWEVENT_FOCUS_GAINED:
			case SDL_WINDOWEVENT_MAXIMIZED:
			case SDL_WINDOWEVENT_RESTORED:
				m_windowEvents[WE_SHOW] = true;
				break;
			}
			break;

		case SDL_MOUSEBUTTONDOWN:
			m_mouse_buttons[event.button.button - 1] = KEY_DOWN;
			break;

		case SDL_MOUSEBUTTONUP:
			m_mouse_buttons[event.button.button - 1] = KEY_UP;
			break;

		case SDL_CONTROLLERBUTTONDOWN:
			m_gamepad_buttons[event.cbutton.button] = KEY_DOWN;
			break;

		case SDL_CONTROLLERBUTTONUP:
			m_gamepad_buttons[event.cbutton.button - 1] = KEY_DOWN;
			break;

		case SDL_MOUSEMOTION:
			m_mouseMotion.x = event.motion.xrel / SCREEN_SIZE;
			m_mouseMotion.y = event.motion.yrel / SCREEN_SIZE;
			m_mouse.x = event.motion.x / SCREEN_SIZE;
			m_mouse.y = event.motion.y / SCREEN_SIZE;
			break;
		}
	}

	if (GetWindowEvent(EventWindow::WE_QUIT) == true || GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		return false;

	return true;
}

// Called before quitting
bool CModuleInput::CleanUp()
{
	LOG("Quitting SDL event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}

// ---------
bool CModuleInput::GetWindowEvent(EventWindow ev) const
{
	return m_windowEvents[ev];
}

const iPoint& CModuleInput::GetMousePosition() const
{
	return m_mouse;
}

const iPoint& CModuleInput::GetMouseMotion() const
{
	return m_mouseMotion;
}