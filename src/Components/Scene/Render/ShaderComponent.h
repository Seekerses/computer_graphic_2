#pragma once

#include <string>
#include <d3d11.h>
#include <d3dcompiler.h>
#include "ShaderAsset.h"

class ShaderComponent
{
 private:
	ShaderAsset* _shaderAsset;

 public:
	explicit ShaderComponent(ShaderAsset* shaderAsset);
	void SwapContext();
};
