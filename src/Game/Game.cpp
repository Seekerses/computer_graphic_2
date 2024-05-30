#include "Game.h"
#include "../Utils/Colors.h"
#include "../Renderer/Vertex.h"
#include "../Object/Primitives/Triangle.h"
#include "../Object/Primitives/Rectangle.h"

Game* game = nullptr;

Game* GetGame() {
	return game;
}

Game::Game(const std::string& window_name, uint16_t width, uint16_t height)
{
	game = this;
	this->renderer = new Renderer(new Window(window_name.c_str(), width, height));
	this->inputDevice = new InputDevice(this);
	this->scene = new SceneManager();

	this->running = true;
	this->lastMs = std::chrono::steady_clock::now();
	this->frameCount = 0;
	this->totalTime = 0;
	this->deltaTime = 0;
}

void Game::RunLoop()
{
	auto currentTime = std::chrono::steady_clock::now();
	deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - lastMs).count() / 1000000.0f;
	lastMs = currentTime;

	totalTime += deltaTime;
	frameCount++;

	if (totalTime > 1.0f) {
		float fps = static_cast<float>(frameCount) / totalTime;

		totalTime -= 1.0f;

		WCHAR text[256];
		swprintf_s(text, TEXT(L"FPS: %f"), fps);
		SetWindowTextW(renderer->GetWindow()->getHWnd(), reinterpret_cast<LPCWSTR>(text));

		frameCount = 0;
	}

	renderer->Draw(scene);
}

void Game::Start()
{
	Load();

	while(running) {
		HandleInput();
		RunLoop();
	}
	CleanUp();
}

void Game::CleanUp()
{

}

void Game::HandleInput()
{
	MSG msg = {};
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT) {
			running = false;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

Game::~Game()
{
	delete inputDevice;
	delete renderer;
	delete scene;
}

void Game::Load()
{
	// loading basic shader
	D3D11_INPUT_ELEMENT_DESC inputElements[] = {
		D3D11_INPUT_ELEMENT_DESC{
			"POSITION",
			0,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			0,
			0,
			D3D11_INPUT_PER_VERTEX_DATA,
			0 },
		D3D11_INPUT_ELEMENT_DESC{
			"COLOR",
			0,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,
			D3D11_INPUT_PER_VERTEX_DATA,
			0 }
	};
	auto* basicShader = new ShaderComponent(renderer, L"Resources/DumbShader.hlsl", inputElements, UINT(2));

	// creating triangle
	Vertex vertices[3] = {
		Vertex {DirectX::XMFLOAT4 {.5f, .0f, 1.f, 1.f}, RED },
		Vertex {DirectX::XMFLOAT4 {.5f, .1f, 1.f, 1.f}, WHITE },
		Vertex {DirectX::XMFLOAT4 {1.f, .5f, 1.f, 1.f}, GRAY }
	};
	auto* firstTriangle = new Triangle(new std::wstring(L"something"), renderer, vertices, basicShader);

	//creating rectangle
	Vertex recVertices[4] = {
		Vertex {DirectX::XMFLOAT4 {-.5f, -.75f, 1.f, 1.f}, RED },
		Vertex {DirectX::XMFLOAT4 {-.25f, .75f, 1.f, 1.f}, GREEN },
		Vertex {DirectX::XMFLOAT4 {-.5f, .75f, 1.f, 1.f}, BLUE },
		Vertex {DirectX::XMFLOAT4 {-.25f, -.75f, 1.f, 1.f}, BLACK }
	};
	auto* firstRectangle = new class Rectangle(new std::wstring(L"base"), renderer, recVertices, basicShader);

	//creating second rectangle
	Vertex secVertices[4] = {
		Vertex {DirectX::XMFLOAT4 {-.4f, -.65f, 1.f, 1.f}, BLUE },
		Vertex {DirectX::XMFLOAT4 {-.15f, .65f, 1.f, 1.f}, RED },
		Vertex {DirectX::XMFLOAT4 {-.4f, .65f, 1.f, 1.f}, GREEN },
		Vertex {DirectX::XMFLOAT4 {-.15f, -.65f, 1.f, 1.f}, WHITE }
	};
	auto* secRectangle = new class Rectangle(new std::wstring(L"square"), renderer, secVertices, basicShader);

	//creating third rectangle
	Vertex thirdVertices[4] = {
		Vertex {DirectX::XMFLOAT4 {-.3f, -.55f, 1.f, 1.f}, GREEN },
		Vertex {DirectX::XMFLOAT4 {-.05f, .55f, 1.f, 1.f}, BLUE },
		Vertex {DirectX::XMFLOAT4 {-.3f, .55f, 1.f, 1.f}, RED },
		Vertex {DirectX::XMFLOAT4 {-.05f, -.55f, 1.f, 1.f}, BLACK }
	};
	auto* thirdRectangle = new class Rectangle(new std::wstring(L"Statue of Freedom"), renderer, thirdVertices, basicShader);

	firstRectangle->AddChild(firstTriangle);
	firstRectangle->AddChild(secRectangle);
	secRectangle->AddChild(thirdRectangle);
	firstRectangle->RemoveChild(firstRectangle);

	firstRectangle->PrintHierarchy(0);
	scene->AddObject(firstRectangle);
}
