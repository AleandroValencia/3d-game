#include "InputHandler.h"
#include <stdio.h>

InputHandler::InputHandler()
	: m_xOffset(0.0f)
	, m_yOffset(0.0f)
	, m_sensitivity(0.1f)
	, m_mouseMove(false)
{
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
		//glm::vec3 rotation = glm::vec3(m_input->GetYOffset(), m_input->GetXOffset(), 0.0f);
		//camera->Rotate(rotation);
	}
}

bool InputHandler::GetKeyPress(SDL_Scancode _key) const
{
	return m_keyPress[_key];
}

bool InputHandler::GetKeyUp(SDL_Scancode _key) const
{
	return m_keyUp[_key];
}

bool InputHandler::GetKeyHold(SDL_Scancode _key) const
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
