#include "SceneManager.h"

SceneManager::SceneManager() = default;

void SceneManager::RemoveObject(SceneComponent* obj)
{
	auto it = std::find(scene.begin(), scene.end(), obj);
	if (it != scene.end()) {
		scene.erase(it);
	}
}

void SceneManager::AddObject(SceneComponent* obj)
{
	this->scene.emplace_back(obj);
}

void SceneManager::DrawScene(ID3D11DeviceContext* context)
{
	for (auto obj: scene) {
		obj->Draw();
	}
}
