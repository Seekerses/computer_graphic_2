#include "Triangle.h"
#include "AssetManager.h"

Triangle::Triangle(Id name)
	: SceneComponent(name)
{
	SetRenderComponent(new RenderComponent(
			new MeshComponent(AssetManager::Get()->GetMeshAsset(Id(L"Triangle.mesh"))),
			new ShaderComponent(AssetManager::Get()->GetShaderAsset(Id(L"DumbShader.hlsl")))
		)
	);
}