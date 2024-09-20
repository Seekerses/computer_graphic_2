#include "Engine.h"
#include "RenderManager.h"
#include "AssetManager.h"
#include "Game.h"

void Engine::InitSubsystems()
{
	RenderManager renderManager;
	renderManager.Init(new Window("Lab 2", 800L, 600L));

	AssetManager assetManager;
	assetManager.Init();

	Engine::_inputDevice = new InputDevice();

	Engine::_game = new Game{};
	Engine::_game->Start();
	delete Engine::_game;

	delete Engine::_inputDevice;
	assetManager.Release();
	renderManager.Release();
}

InputDevice* Engine::_inputDevice;
Game* Engine::_game;