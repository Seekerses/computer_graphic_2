#pragma once

#include <vector>
#include <d3d11.h>
#include "Renderable.h"
#include "SceneComponent.h"

class SceneManager : public Renderable
{
 private:
	std::vector<SceneComponent*> scene;
 public:
	SceneManager();
	void AddObject(SceneComponent* obj);
	void RemoveObject(SceneComponent* obj);
	void Draw() override;
};
