#include "InputHandler.h"
#include <stdio.h>

const Uint8* InputHandler::m_currentKeyStates = SDL_GetKeyboardState(nullptr);
GLfloat InputHandler::m_xOffset = 0.0f;
GLfloat InputHandler::m_yOffset = 0.0f;
float InputHandler::m_joystickAxis[MAX_NUMBER_AXES]{};
bool InputHandler::m_joystickButtonPress[MAX_NUMBER_BUTTONS]{};
bool InputHandler::m_joystickButtonHold[MAX_NUMBER_BUTTONS]{};
bool InputHandler::m_joystickDirectionPad[MAX_NUMBER_PAD_DIRECTIONS]{};
bool InputHandler::m_keyPress[KEYBOARD_SIZE];
bool InputHandler::m_keyUp[KEYBOARD_SIZE];

InputHandler::InputHandler()
	: m_sensitivity(0.1f)
	, m_mouseMove(false)
{
	if (SDL_NumJoysticks() > 0)
	{
		m_gameController = SDL_JoystickOpen(0);
		m_controllerHaptic = SDL_HapticOpenFromJoystick(m_gameController);
		if (m_controllerHaptic)
		{
			// Controller supports haptic
			SDL_HapticRumbleInit(m_controllerHaptic);
		}
	}
	else
	{
		printf("No Joysticks connected...\n");
	}
}

InputHandler::~InputHandler()
{
}

void InputHandler::Update(bool& _closeApplication)
{
	// Reset key states
	for (int i = 0; i < KEYBOARD_SIZE; ++i)
	{
		m_keyPress[i] = false;
		m_keyUp[i] = false;
	}

	m_xOffset = 0.0f;
	m_yOffset = 0.0f;

	for (int i = 0; i < MAX_NUMBER_BUTTONS; ++i)
	{
		m_joystickButtonPress[i] = false;
	}

	for (int i = 0; i < MAX_NUMBER_PAD_DIRECTIONS; ++i)
	{
		m_joystickDirectionPad[i] = false;
	}

	while (SDL_PollEvent(&e) != 0)
	{
		ImGui_ImplSdlGL3_ProcessEvent(&e);
		if (e.type == SDL_QUIT)
		{
			_closeApplication = true;
		}

		// KeyPress
		if (e.type == SDL_KEYDOWN)
		{
			m_currentKeyStates = SDL_GetKeyboardState(nullptr);
			SDL_Scancode key = e.key.keysym.scancode;
			m_keyPress[key] = true;
		}
		if (e.type == SDL_KEYUP)
		{
			m_currentKeyStates = SDL_GetKeyboardState(nullptr);
			SDL_Scancode key = e.key.keysym.scancode;
			m_keyUp[key] = true;
		}

		// Mouse Movement
		MouseMove(e);

		// Joystick Added/Removed
		if (e.type == SDL_JOYDEVICEADDED)
		{
			m_connectedPlayers++;
			if (m_gameController == nullptr)
			{
				m_playerID++;
				m_gameController = SDL_JoystickOpen(0);
				m_controllerHaptic = SDL_HapticOpenFromJoystick(m_gameController);
			}
		}
		if (e.type == SDL_JOYDEVICEREMOVED)
		{
			m_connectedPlayers--;
			if (m_gameController != nullptr)
			{
				m_gameController = nullptr;
				m_controllerHaptic = nullptr;
			}
		}

		// Joystick Axes
		if (e.type == SDL_JOYAXISMOTION)
		{
			if (e.jaxis.which == m_playerID)
			{
				float value = e.jaxis.value;
				if (e.jaxis.axis != LEFT_Z_AXIS && e.jaxis.axis != RIGHT_Z_AXIS)
				{
					if (value < 0)
					{
						value /= -MIN_AXIS_VALUE;
						m_joystickAxis[e.jaxis.axis] = value < -JOYSTICK_DEAD_ZONE ? value : 0.0f;
					}
					else if (value > 0)
					{
						value /= MAX_AXIS_VALUE;
						m_joystickAxis[e.jaxis.axis] = value > JOYSTICK_DEAD_ZONE ? value : 0.0f;
					}
				}
			}
		}

		if (e.type == SDL_JOYBUTTONDOWN)
		{
			if (e.jbutton.which == m_playerID)
			{
				m_joystickButtonPress[e.jbutton.button] = true;
				m_joystickButtonHold[e.jbutton.button] = true;
			}
		}

		if (e.type == SDL_JOYBUTTONUP)
		{
			if (e.jbutton.which == m_playerID)
			{
				m_joystickButtonHold[e.jbutton.button] = false;
			}
		}

		if (e.type == SDL_JOYHATMOTION)
		{
			if (e.jhat.which == m_playerID)
			{
				m_joystickDirectionPad[e.jhat.value] = true;
			}
		}
	}
}

bool InputHandler::GetKeyPress(SDL_Scancode _key)
{
	return m_keyPress[_key];
}

bool InputHandler::GetKeyUp(SDL_Scancode _key)
{
	return m_keyUp[_key];
}

bool InputHandler::GetKeyHold(SDL_Scancode _key)
{
	return m_currentKeyStates[_key];
}

void InputHandler::MouseMove(SDL_Event & _e)
{
	m_mouseMove = false;
	if (_e.type == SDL_MOUSEMOTION)
	{
		m_mouseMove = true;
		int x, y;
		SDL_GetMouseState(&x, &y);

		m_xOffset = static_cast<GLfloat>(_e.motion.xrel);
		m_yOffset = -static_cast<GLfloat>(_e.motion.yrel);

		m_xOffset *= m_sensitivity;
		m_yOffset *= m_sensitivity;
	}
}

float InputHandler::GetJoyAxis(JOYAXIS _whichAxis)
{
	return m_joystickAxis[_whichAxis];
}

bool InputHandler::GetJoyButtonPress(XBOXBUTTON _button)
{
	return m_joystickButtonPress[_button];
}

bool InputHandler::GetJoyButtonHold(XBOXBUTTON _button)
{
	return m_joystickButtonHold[_button];
}
