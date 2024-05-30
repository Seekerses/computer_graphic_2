#pragma once

#include <vector>
#include <d3d11.h>
#include "../Object/Components/Scene/SceneComponent.h"

class RenderComponent;
class SceneComponent;

class SceneManager
{
 private:
	std::vector<SceneComponent*> scene;
 public:
	SceneManager();
	void AddObject(SceneComponent* obj);
	void RemoveObject(SceneComponent* obj);
	void DrawScene(ID3D11DeviceContext* context);
};
