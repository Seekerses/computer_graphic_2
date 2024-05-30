#pragma once

#include <windows.h>
#include <d3d11.h>
#include <wrl.h>
#include "../Window/Window.h"
#include "SceneManager.h"
#include <d3d11.h>
#include "../Utils/SMath.h"

class Window;
class ShaderComponent;

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
	IDXGISwapChain* GetSwapChain() { return swapChain; };
	Window* GetWindow() { return window; };
	ID3D11VertexShader* CreateVertexShader(const ShaderComponent& shader);
	ID3D11PixelShader* CreatePixelShader(const ShaderComponent& shader);

	void Draw(SceneManager* scene);
};
