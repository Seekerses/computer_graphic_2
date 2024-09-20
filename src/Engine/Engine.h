#pragma once

#include "InputDevice.h"
#include "Game.h"

class Engine
{
 private:
	static InputDevice* _inputDevice;
	static Game* _game;
 public:
	void InitSubsystems();
	static InputDevice* GetInputDevice() { return _inputDevice; }
	static Game* GetGame() { return _game; }
};