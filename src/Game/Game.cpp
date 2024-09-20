#include "Game.h"
#include "Ball.h"
#include "Plank.h"
#include "CollisionUtils.h"
#include "Colors.h"
#include "RenderManager.h"

Game::Game()
{
	this->scene = new SceneManager();
	this->running = true;
	this->lastFrameMs = std::chrono::steady_clock::now();
}

void Game::RunLoop()
{
	auto currentTime = std::chrono::steady_clock::now();
	float deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - lastFrameMs).count() / 1000000.0f;
	lastFrameMs = currentTime;

	RenderManager::Get()->Draw(scene);
	for (const auto& item : objects) {
		item->FixedUpdate(deltaTime);
	}
}

void Game::Start()
{
	Load();

	while(running) {
		HandleInput();
		CalculateCollisions();
		RunLoop();
		UpdateUI();
	}
	CleanUp();
}

void Game::CleanUp()
{

}

void Game::HandleInput()
{
	MSG msg = {};
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT) {
			running = false;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

Game::~Game()
{
	delete scene;
}

void Game::Load()
{
	DirectX::SimpleMath::Vector3 initVelocity = {.75f, .5f, .0f};
	Ball* ball = new Ball(Id(L"ball"), initVelocity, 1.1f);

	DirectX::SimpleMath::Vector3 player1Velocity = {.0f, 3.f, .0f};
	auto* user1 = new Plank(Id(L"player_1"), 0, player1Velocity);
	user1->GetSceneComponent()->SetPosition({-0.9f, .0f, 1.f, 1.f});
	user1->GetSceneComponent()->SetColor({GREEN});

	DirectX::SimpleMath::Vector3 player2Velocity = {.0f, 3.f, .0f};
	auto* user2 = new Plank(Id(L"player_2"), 1, player2Velocity);
	user2->GetSceneComponent()->SetPosition({0.9f, .0f, 1.f, 1.f});
	user2->GetSceneComponent()->SetColor({RED});

	AddGameObject(ball);
	AddGameObject(user1);
	AddGameObject(user2);
}
void Game::AddGameObject(GameObject* gameObject)
{
	this->objects.emplace_back(gameObject);
	if (gameObject->GetSceneComponent() != nullptr) {
		scene->AddObject(gameObject->GetSceneComponent());
	}
}

void Game::UpdateUI()
{
	WCHAR text[256];
	swprintf_s(text, TEXT(L"Score: %i / %i"), score[0], score[1]);
	SetWindowTextW(RenderManager::Get()->GetWindow()->getHWnd(), reinterpret_cast<LPCWSTR>(text));
}

void Game::CalculateCollisions()
{
	for(int i = 0; i < objects.size(); i++) {
		DirectX::XMFLOAT4 collision = objects[i]->GetCollision();
		for(int j = i + 1; j < objects.size(); j++) {
			DirectX::XMFLOAT4 otherCollision = objects[j]->GetCollision();
			DirectX::XMFLOAT4 result = Intersect(collision, otherCollision);
			if (result.x != 0 || result.y != 0 || result.z != 0 || result.w != 0) {
				objects[i]->OnCollisionEnter(result);
				objects[j]->OnCollisionEnter(result);
			}
		}
	}
}
