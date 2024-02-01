#pragma once

#include "IGameState.hpp"

namespace venture
{
	class GameOverState : public IGameState
	{
	public:
		~GameOverState() override;

		void Init() override;
		void ProcessInput( InputManager* input ) override;
		void Update(float deltaTime) override;
		void Render(SDL_Renderer* renderer) override;
		void Clean() override;
	};

}