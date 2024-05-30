#pragma once

#include <vector>
#include <d3d11.h>
#include "SceneComponent.h"

class Renderer;
class SceneComponent;

class SceneManager
{
 private:
	std::vector<SceneComponent*> scene;
 public:
	SceneManager();
	void AddObject(SceneComponent* obj);
	void RemoveObject(SceneComponent* obj);
	void DrawScene(Renderer* renderer);
};
