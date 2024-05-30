#pragma once

#include <windows.h>
#include <string>
#include "winuser.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "ShaderComponent.h"
#include "InputDevice.h"
#include <chrono>

class InputDevice;
class SceneManager;
class Renderer;
class Triangle;
class Rectangle;
class MeshComponent;

class Game
{
 private:
	Renderer* renderer = nullptr;
	SceneManager* scene = nullptr;
	InputDevice* inputDevice = nullptr;
	bool running;
	std::chrono::time_point<std::chrono::steady_clock> lastMs;
	UINT frameCount;
	float totalTime;
	float deltaTime;

	void Load();
	void HandleInput();
	void RunLoop();
	void CleanUp();
 public:
	Game(const std::string& window_name, uint16_t width, uint16_t height);
	~Game();
	void Start();

	Renderer* GetRenderer() { return renderer; }
	SceneManager* GetSceneManager() { return scene; }
	InputDevice* GetInputDevice() { return inputDevice; }
};

extern Game* game;
extern Game* GetGame();
