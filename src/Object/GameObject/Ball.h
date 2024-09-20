#pragma once

#include <chrono>
#include "SimpleMath.h"
#include "Types.h"
#include "GameObject.h"

class Ball : public GameObject
{
 private:
	DirectX::SimpleMath::Vector3 _velocity;
	DirectX::SimpleMath::Vector3 _initVelocity;
	float _accelerationFactor = 1;
	std::chrono::time_point<std::chrono::steady_clock> _lastCollisionTime;

	void Respawn();
 public:
	Ball(const Id& name, DirectX::SimpleMath::Vector3 initVelocity, float accelerationFactor = 1);
	void FixedUpdate(float deltaTime) override;
	void AccelerateOnUserCollision();
	void SetAccelerationFactor(float accelerationFactor) { this->_accelerationFactor = accelerationFactor; }
	void OnCollisionEnter(DirectX::XMFLOAT4 rect) override;
};
