#pragma once

#include <windows.h>
#include <d3d11.h>
#include <wrl.h>
#include "SingletonManager.h"
#include "Window.h"
#include "Renderable.h"
#include "Types.h"

class RenderManager : public SingletonManager
{
 private:
	static RenderManager* _instance;
	ID3D11Device* _device = nullptr;
	ID3D11DeviceContext* _context = nullptr;
	IDXGISwapChain* _swapChain = nullptr;
	ID3D11RenderTargetView* _rtv = nullptr;
	ID3D11RasterizerState* _rasterizerState = nullptr;
	Window* _window = nullptr;
	FLOAT _cleanColor[4] =  {.0f, .0f, .0f, 1.f};

 public:
	RenderManager() = default;
	~RenderManager() override = default;
	void Init(Window* window);
	void Release() override;
	static RenderManager* Get();
	ID3D11Device* GetDevice() { return _device; };
	ID3D11DeviceContext* GetContext() { return _context; };
	Window* GetWindow() { return _window; };
	void SetClearColor(Color color);
	void Draw(Renderable* scene);
};
