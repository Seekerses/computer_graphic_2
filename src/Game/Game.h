#pragma once

#include <windows.h>
#include <string>
#include <winuser.h>
#include <chrono>
#include "GameObject.h"
#include "InputDevice.h"
#include "SceneManager.h"

class Game
{
 private:
	SceneManager* scene = nullptr;
	std::vector<GameObject*> objects;
	bool running;
	std::chrono::time_point<std::chrono::steady_clock> lastFrameMs;
	UINT score[2] = {0, 0};

	void Load();
	void HandleInput();
	void RunLoop();
	void CleanUp();
	void UpdateUI();
	void CalculateCollisions();
 public:
	Game();
	~Game();
	void Start();

	SceneManager* GetSceneManager() { return scene; }
	void AddGameObject(GameObject* gameObject);
	void AddScore(UINT player) { this->score[player]++; };
};
