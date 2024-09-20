//
// Created by seekerses on 06.06.2024.
//

#include <random>
#include "Random.h"
#include "Colors.h"
#include "Engine.h"
#include "RectangleShape.h"
#include "Ball.h"
#include "RenderManager.h"

Ball::Ball(const Id& name, DirectX::SimpleMath::Vector3 initVelocity, float accelerationFactor)
: GameObject(name), _initVelocity(initVelocity), _velocity(initVelocity), _accelerationFactor(accelerationFactor)
{
	auto* rectangleShape = new RectangleShape(Id(L"BallSceneComponent"));
	rectangleShape->SetColor({WHITE});
	rectangleShape->SetScale(DirectX::XMFLOAT4 {.05, .05, 1, 1 });
	SetSceneComponent(rectangleShape);
	SetCollision(DirectX::XMFLOAT4 {1.f, 1.f, 1.f, 1.f });
}

void Ball::FixedUpdate(float deltaTime)
{
	GameObject::FixedUpdate(deltaTime);
	GetSceneComponent()->AddPosition(_velocity * deltaTime);
	if (GetSceneComponent()->GetTransform().position.y  + .1f > 1.f
		||
		GetSceneComponent()->GetTransform().position.y - .1f < -1.f)
	{
		_velocity.y = -_velocity.y;
	}
	if (GetSceneComponent()->GetTransform().position.x + .05f > 1.3f)
	{
		Engine::GetGame()->AddScore(0);
		Respawn();
	}
	if (GetSceneComponent()->GetTransform().position.x - .05f < -1.3f)
	{
		Engine::GetGame()->AddScore(1);
		Respawn();
	}

}
void Ball::Respawn()
{
	_velocity = _initVelocity;
	if (randomBoolean()) {
		_velocity.x = -_velocity.x;
	}
	if (randomBoolean()) {
		_velocity.y = -_velocity.y;
	}
	GetSceneComponent()->SetPosition({.0f, .0f, .0f, .0f});
}

void Ball::AccelerateOnUserCollision()
{
	_velocity = _velocity * _accelerationFactor;
}

void Ball::OnCollisionEnter(DirectX::XMFLOAT4 rect)
{
	auto currentTime = std::chrono::steady_clock::now();
	float deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - _lastCollisionTime).count() / 1000000.0f;
	if (deltaTime < 0.1f) {
		return;
	}
	if (rect.x == 1)
	{
		_velocity.x = -_velocity.x;
	}
	else {
		_velocity.y = -_velocity.y;
	}
	AccelerateOnUserCollision();
	_lastCollisionTime = currentTime;
}

// Trying to create circle

//	const UINT resolution = 37;
//	Vertex vertices[resolution];
//	UINT indices[(resolution - 1) * 3];
//	UINT step = 360 / (resolution - 1);
//	vertices[0] = (Vertex{{ .0f, .0f, .0f, .0f }});
//	for (UINT i = 0; i < resolution; i++)
//	{
//		vertices[i+1] = Vertex{{
//			static_cast<float>(.1f * cos(i * step)),
//			static_cast<float>(.1f * sin(i * step)),
//			1.f, 1.f }};
//	}
//	for (UINT i = 0; i < resolution - 1; i++) {
//		indices[i * 3] = 0;
//		indices[i * 3 + 1] = i + 1;
//		indices[i * 3 + 2] = i + 2;
//	}
//	indices[107] = 1;
//	const UINT* _strides = new UINT[]{ sizeof(Vertex) };
//	const UINT* _offsets = new UINT[]{ 0 };
//	auto* mesh = new MeshComponent(
//		renderer,
//		D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
//		vertices, 4,
//		indices, 6,
//		_strides, _offsets);
