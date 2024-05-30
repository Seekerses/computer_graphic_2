#include "SceneComponent.h"

SceneComponent::SceneComponent(std::wstring* name) : Component(name)
{

}

void SceneComponent::PrintHierarchy(int depth)
{
	for (int i = 0; i < depth; i++){
		std::cout << "-";
	}
	std::wcout << *GetName() << std::endl;
	int nextStepDepth = ++depth;
	for (auto children : child) {
		children->PrintHierarchy(nextStepDepth);
	}
}

void SceneComponent::Draw()
{
	render->Draw();
	for (auto children: child) {
		children->Draw();
	}
}

void SceneComponent::AddChild(SceneComponent* children)
{
	this->child.emplace_back(children);
}

void SceneComponent::RemoveChild(SceneComponent* children)
{
	auto it = std::find(child.begin(), child.end(), children);
	if (it != child.end()) {
		child.erase(it);
	}
}
