#include "RenderManager.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")


void RenderManager::Init(Window* window)
{
	D3D_FEATURE_LEVEL featureLevel[] = { D3D_FEATURE_LEVEL_11_1 };
	HWND hWnd = window->getHWnd();

	DXGI_SWAP_CHAIN_DESC swapDesc = {};
	swapDesc.BufferCount = 2;
	swapDesc.BufferDesc.Width = window->getWidth();
	swapDesc.BufferDesc.Height = window->getHeight();
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.OutputWindow = hWnd;
	swapDesc.Windowed = true;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	swapDesc.SampleDesc.Count = 1;
	swapDesc.SampleDesc.Quality = 0;

	auto res = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		D3D11_CREATE_DEVICE_DEBUG,
		featureLevel,
		1,
		D3D11_SDK_VERSION,
		&swapDesc,
		&_swapChain,
		&_device,
		nullptr,
		&_context);

	if(FAILED(res))
	{
		MessageBox(hWnd,
			"Failed to create DirectX Device and Swap Chain",
			"RenderManager fatal error",
			MB_OK);
	}

	ID3D11Texture2D* backTex;

	res = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backTex);
	res |= _device->CreateRenderTargetView(backTex, nullptr, &_rtv);
	backTex->Release();
	if(FAILED(res))
	{
		MessageBox(hWnd,
			"Failed to obtain Swap Chain back buffer",
			"RenderManager fatal error",
			MB_OK);
	}

	CD3D11_RASTERIZER_DESC rastDesc = {};
	rastDesc.CullMode = D3D11_CULL_NONE;
	rastDesc.FillMode = D3D11_FILL_SOLID;

	res = _device->CreateRasterizerState(&rastDesc, &_rasterizerState);
	if(FAILED(res))
	{
		MessageBox(hWnd,
			"Failed to crete rasterizer state",
			"RenderManager fatal error",
			MB_OK);
	}

	_context->RSSetState(_rasterizerState);
	_window = window;
	_instance = this;
}

void RenderManager::Release()
{
	_rasterizerState->Release();
	_rtv->Release();
	_swapChain->Release();
	_context->Release();
	_device->Release();
	delete _window;
}

RenderManager* RenderManager::Get()
{
	return _instance;
}

void RenderManager::Draw(Renderable* scene)
{
	_context->ClearState();

	_context->RSSetState(_rasterizerState);

	D3D11_VIEWPORT viewport = {};
	viewport.Width = static_cast<float>(_window->getWidth());
	viewport.Height = static_cast<float>(_window->getHeight());
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1.0f;

	_context->RSSetViewports(1, &viewport);

	_context->OMSetRenderTargets(1, &_rtv, nullptr);
	_context->ClearRenderTargetView(_rtv, _cleanColor);

	scene->Draw();

	_context->OMSetRenderTargets(0, nullptr, nullptr);
	_swapChain->Present(1, /*DXGI_PRESENT_DO_NOT_WAIT*/ 0);
}

void RenderManager::SetClearColor(Color color)
{
	_cleanColor[0] = color.x;
	_cleanColor[1] = color.y;
	_cleanColor[2] = color.z;
	_cleanColor[3] = color.w;
}

RenderManager* RenderManager::_instance;
