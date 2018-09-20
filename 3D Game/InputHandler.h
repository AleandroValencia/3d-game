#ifndef _INPUTHANDLER_H__
#define _INPUTHANDLER_H__
#pragma once

#include "glm\glm.hpp"
#include "Dependencies\glew\glew.h"
#include "Dependencies\sdl\include\SDL.h"
#include "Dependencies\Dear_ImGui\imgui.h"
#include "Dependencies\Dear_ImGui\imgui_impl_sdl_gl3.h"

#define KEYBOARD_SIZE 284

class InputHandler
{
public:
	InputHandler();
	~InputHandler();

	void Update(bool& _closeApplication);

	void UpdateKeyStates() { m_currentKeyStates = SDL_GetKeyboardState(nullptr); }

	bool GetKeyPress(SDL_Scancode _key) const;
	bool GetKeyUp(SDL_Scancode _key) const;
	static bool GetKeyHold(SDL_Scancode _key);
	bool isMouseMoving() const { return m_mouseMove; }
	void MouseMove(SDL_Event& _e);

	static GLfloat GetXOffset() { return m_xOffset; }
	static GLfloat GetYOffset() { return m_yOffset; }
	bool MouseMove() const { return m_mouseMove; }

private:
	static const Uint8* m_currentKeyStates;
	static GLfloat m_xOffset;
	static GLfloat m_yOffset;
	GLfloat m_sensitivity;

	bool m_mouseMove;
	bool m_keyPress[KEYBOARD_SIZE];
	bool m_keyUp[KEYBOARD_SIZE];

	SDL_Event e;
};

#endif // !_INPUTHANDLER_H__

