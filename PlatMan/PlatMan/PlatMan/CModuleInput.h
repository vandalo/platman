#pragma once

#include "pch.h"

#include "IModule.h"
#include "Point.h"
#include <windows.h>
#include "SDL_GameController.h"

#define NUM_MOUSE_BUTTONS 5

enum EventWindow
{
	WE_QUIT = 0,
	WE_HIDE = 1,
	WE_SHOW = 2,
	WE_COUNT
};

enum KeyState
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

class CModuleInput : public IModule
{

public:

	CModuleInput();

	virtual ~CModuleInput();

	bool Init();
	bool Start();

	bool PreUpdate(float deltaTime);

	bool CleanUp();

	// Check key states (includes mouse and joy buttons)
	KeyState GetKey(int id) const
	{
		return m_keyboard[id];
	}

	KeyState GetGameControllerButton(int id) const
	{
		return m_gamepad_buttons[id];
	}

	KeyState GetMouseButtonDown(int id) const
	{
		return m_keyboard[id - 1];
	}

	// Check for window events last frame
	bool GetWindowEvent(EventWindow code) const;

	//Get mouse / axis position
	const iPoint& GetMouseMotion() const;
	const iPoint& GetMousePosition() const;

private:
	bool m_windowEvents[WE_COUNT];
	KeyState* m_keyboard;
	KeyState m_mouse_buttons[NUM_MOUSE_BUTTONS];
	KeyState m_gamepad_buttons[SDL_CONTROLLER_BUTTON_MAX];
	iPoint m_mouseMotion;
	iPoint m_mouse;
	SDL_GameController* m_gameController;
};