#ifndef _COMMAND_H__
#define _COMMAND_H__
#pragma once

#include "GameObject.h"

class Command
{
public:
	virtual ~Command() {}
	virtual void Execute(GameObject& _object) = 0;
};

class CmdMoveForward : public Command
{
public:
	virtual void Execute(GameObject& _object) { _object.MoveForward(); }
};

class CmdMoveBackward : public Command
{
public:
	virtual void Execute(GameObject& _object) { _object.MoveBackward(); }
};

class CmdMoveLeft : public Command
{
public:
	virtual void Execute(GameObject& _object) { _object.MoveLeft(); }
};

class CmdMoveRight : public Command
{
public:
	virtual void Execute(GameObject& _object) { _object.MoveRight(); }
};

#endif // !_COMMAND_H__