#include "ShaderAsset.h"

ShaderAsset::ShaderAsset(ID3D11VertexShader* vertexShader, ID3D11PixelShader* pixelShader, ID3D11InputLayout* inputLayout)
	:
	_vertexShader(vertexShader),
	_pixelShader(pixelShader),
	_inputLayout(inputLayout)
{
}
