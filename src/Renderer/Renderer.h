#pragma once

#include <windows.h>
#include <d3d11.h>
#include <wrl.h>
#include "Window.h"
#include "SceneManager.h"
#include "SMath.h"

class Window;
class SceneManager;

class Renderer
{
 private:
	ID3D11Device* device;
	ID3D11DeviceContext* context;
	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* rtv;
	ID3D11RasterizerState* rasterizerState;
	Window* window;
	FLOAT cleanColor[4] {.0f, .0f, .0f, 1.f};

 public:
	explicit Renderer(Window* window);
	~Renderer();
	ID3D11Device* GetDevice() { return device; };
	ID3D11DeviceContext* GetContext() { return context; };
	Window* GetWindow() { return window; };
	void Draw(SceneManager* scene);
};
