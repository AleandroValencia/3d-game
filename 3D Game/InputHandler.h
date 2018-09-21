#ifndef _INPUTHANDLER_H__
#define _INPUTHANDLER_H__
#pragma once

#include <map>

#include "glm\glm.hpp"
#include "Dependencies\glew\glew.h"
#include "Dependencies\sdl\include\SDL.h"
#include "Dependencies\Dear_ImGui\imgui.h"
#include "Dependencies\Dear_ImGui\imgui_impl_sdl_gl3.h"

#define KEYBOARD_SIZE 284
#define MAX_AXIS_VALUE 32767
#define MIN_AXIS_VALUE -32768

enum EPLAYER
{
	PLAYER_ONE = 0,
	PLAYER_TWO,
	PLAYER_THREE,
	PLAYER_FOUR,
	MAX_NUMBER_PLAYERS
};

enum JOYAXIS
{
	LEFT_X_AXIS = 0,
	LEFT_Y_AXIS,
	LEFT_Z_AXIS,
	RIGHT_X_AXIS,
	RIGHT_Y_AXIS,
	RIGHT_Z_AXIS,
	MAX_NUMBER_AXES
};

enum XBOXBUTTON
{
	XBOX_A = 0,
	XBOX_B,
	XBOX_X,
	XBOX_Y,
	XBOX_LB,
	XBOX_RB,
	XBOX_BACK,
	XBOX_START,
	XBOX_LSTICK,
	XBOX_RSTICK,
	MAX_NUMBER_BUTTONS
};

enum JOYDIRECTIONPAD
{
	CENTERED = 0,
	UP = 1,
	RIGHT = 2,
	RIGHT_UP = 3,
	DOWN = 4,
	RIGHT_DOWN = 6,
	LEFT = 8,
	LEFT_UP = 9,
	LEFT_DOWN = 12,
	MAX_NUMBER_PAD_DIRECTIONS = 13
};

class InputHandler
{
public:
	InputHandler();
	~InputHandler();

	void Update(bool& _closeApplication);

	void UpdateKeyStates() { m_currentKeyStates = SDL_GetKeyboardState(nullptr); }

	static bool GetKeyPress(SDL_Scancode _key);
	static bool GetKeyUp(SDL_Scancode _key);
	static bool GetKeyHold(SDL_Scancode _key);
	bool isMouseMoving() const { return m_mouseMove; }
	void MouseMove(SDL_Event& _e);

	static GLfloat GetXOffset() { return m_xOffset; }
	static GLfloat GetYOffset() { return m_yOffset; }
	bool MouseMove() const { return m_mouseMove; }

	static float GetJoyAxis(JOYAXIS _whichAxis);
	static bool GetJoyButtonPress(XBOXBUTTON _button);
	static bool GetJoyButtonHold(XBOXBUTTON _button);

private:
	static const Uint8* m_currentKeyStates;
	static GLfloat m_xOffset;
	static GLfloat m_yOffset;
	GLfloat m_sensitivity;

	bool m_mouseMove;
	static bool m_keyPress[KEYBOARD_SIZE];
	static bool m_keyUp[KEYBOARD_SIZE];

	const float JOYSTICK_DEAD_ZONE = 0.25f;
	SDL_Joystick* m_gameController;
	SDL_Haptic* m_controllerHaptic;
	int m_disconnectedPlayers[MAX_NUMBER_PLAYERS] = { -1, -1, -1, -1 };
	int m_playerID = 0;
	int m_connectedPlayers = 0;
	static float m_joystickAxis[MAX_NUMBER_AXES];
	static bool m_joystickButtonPress[MAX_NUMBER_BUTTONS];
	static bool m_joystickButtonHold[MAX_NUMBER_BUTTONS];
	static bool m_joystickDirectionPad[MAX_NUMBER_PAD_DIRECTIONS];

	SDL_Event e;
};

#endif // !_INPUTHANDLER_H__

