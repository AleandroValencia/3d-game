#ifndef _CONTROLLER_H__
#define _CONTROLLER_H__
#pragma once

#include <SDL.h>

class Controller
{
public:
	Controller();
	~Controller();

private:
	const int JOYSTICK_DEAD_ZONE = 8000;

	SDL_Joystick* gGameController = nullptr;
	SDL_Haptic* gControllerHaptic = nullptr;

	enum EPLAYER
	{
		PLAYER_ONE = 0,
		PLAYER_TWO,
		PLAYER_THREE,
		PLAYER_FOUR,
		MAX_NUMBER_PLAYERS
	};

	enum EAXIS
	{
		LEFT_X_AXIS = 0,
		LEFT_Y_AXIS,
		LEFT_Z_AXIS,
		RIGHT_X_AXIS,
		RIGHT_Y_AXIS,
		RIGHT_Z_AXIS
	};

	enum EXBOXBUTTONS
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
		XBOX_RSTICK
	};

	int disconnectedPlayers[MAX_NUMBER_PLAYERS] = { -1, -1, -1, -1 };
	int connectedPlayers = 0;
	int instanceID = 0;
};

#endif // !_CONTROLLER_H__
