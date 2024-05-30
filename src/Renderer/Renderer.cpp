#include "Renderer.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")


Renderer::Renderer(Window* window)
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
		&swapChain,
		&device,
		nullptr,
		&context);

	if(FAILED(res))
	{
		MessageBox(hWnd,
			"Failed to create DirectX Device and Swap Chain",
			"Renderer fatal error",
			MB_OK);
	}

	ID3D11Texture2D* backTex;

	res = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backTex);
	res |= device->CreateRenderTargetView(backTex, nullptr, &rtv);
	backTex->Release();
	if(FAILED(res))
	{
		MessageBox(hWnd,
			"Failed to obtain Swap Chain back buffer",
			"Renderer fatal error",
			MB_OK);
	}

	CD3D11_RASTERIZER_DESC rastDesc = {};
	rastDesc.CullMode = D3D11_CULL_NONE;
	rastDesc.FillMode = D3D11_FILL_SOLID;

	res = device->CreateRasterizerState(&rastDesc, &rasterizerState);
	if(FAILED(res))
	{
		MessageBox(hWnd,
			"Failed to crete rasterizer state",
			"Renderer fatal error",
			MB_OK);
	}

	context->RSSetState(rasterizerState);
	this->window = window;
}

void Renderer::Draw(SceneManager* scene)
{
	context->ClearState();

	context->RSSetState(rasterizerState);

	D3D11_VIEWPORT viewport = {};
	viewport.Width = static_cast<float>(window->getWidth());
	viewport.Height = static_cast<float>(window->getHeight());
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1.0f;

	context->RSSetViewports(1, &viewport);

	context->OMSetRenderTargets(1, &rtv, nullptr);
	context->ClearRenderTargetView(rtv, cleanColor);

	scene->DrawScene(context);

	context->OMSetRenderTargets(0, nullptr, nullptr);
	swapChain->Present(1, /*DXGI_PRESENT_DO_NOT_WAIT*/ 0);
}
Renderer::~Renderer()
{
	delete window;
}
