#pragma once

#include "Game.h"
#include "Types.h"

class Plank : public GameObject
{
 private:
	DirectX::SimpleMath::Vector3 velocity;
	UINT player;
 public:
	Plank(const Id& name, UINT player, DirectX::SimpleMath::Vector3 velocity);
	void FixedUpdate(float deltaTime) override;
};
