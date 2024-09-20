//
// Created by seekerses on 06.06.2024.
//

#include "Plank.h"
#include "Colors.h"
#include "Keys.h"
#include "Engine.h"
#include "RectangleShape.h"
#include "RenderManager.h"

Plank::Plank(
	const Id& name,
	UINT player,
	DirectX::SimpleMath::Vector3 velocity)
	: GameObject(name), player(player), velocity(velocity)
{
	auto* rectangleShape = new RectangleShape(Id( L"PlankShape"));
	rectangleShape->SetColor({ WHITE});
	rectangleShape->SetScale(DirectX::XMFLOAT4(0.02f, 0.25f, 0.1f, 0.1f));
	SetSceneComponent(rectangleShape);

	SetCollision(DirectX::XMFLOAT4 {1.f, 1.f, 0.1f, 1.f});
}

void Plank::FixedUpdate(float deltaTime)
{
	if (
		player == 0
		&& Engine::GetInputDevice()->IsKeyDown(Keys::Up)
		&& GetSceneComponent()->GetTransform().position.y < .75f)
	{
		GetSceneComponent()->AddPosition({.0f, velocity.y * deltaTime, .0f});
	}
	if (
		player == 0
		&& Engine::GetInputDevice()->IsKeyDown(Keys::Down)
		&& GetSceneComponent()->GetTransform().position.y > -.75f)
	{
		GetSceneComponent()->AddPosition({.0f, - velocity.y * deltaTime, .0f});
	}
	if (
		player == 1
		&& Engine::GetInputDevice()->IsKeyDown(Keys::NumPad8)
		&& GetSceneComponent()->GetTransform().position.y < .75f)
	{
		GetSceneComponent()->AddPosition({.0f, velocity.y * deltaTime, .0f});
	}
	if (
		player == 1
		&& Engine::GetInputDevice()->IsKeyDown(Keys::NumPad2)
		&& GetSceneComponent()->GetTransform().position.y > -.75f)
	{
		GetSceneComponent()->AddPosition({.0f, - velocity.y * deltaTime, .0f});
	}
}
