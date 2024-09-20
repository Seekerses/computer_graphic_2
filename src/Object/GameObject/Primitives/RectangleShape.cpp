#include "RectangleShape.h"
#include "AssetManager.h"

RectangleShape::RectangleShape(const Id& name)
	: SceneComponent(name)
{
	SetRenderComponent(new RenderComponent(
			new MeshComponent(AssetManager::Get()->GetMeshAsset(Id(L"Square.mesh"))),
			new ShaderComponent(AssetManager::Get()->GetShaderAsset(Id(L"DumbShader.hlsl")))
		)
	);
}