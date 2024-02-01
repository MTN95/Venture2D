#pragma once

#include "IGameState.hpp"

namespace venture
{
	/*
	 * Handles the game when it is paused.
	 */
	class PauseState : public IGameState
	{
	public:
		~PauseState() override;

		void Init() override;
		void ProcessInput( InputManager* input ) override;
		void Update(float deltaTime) override;
		void Render(SDL_Renderer* renderer) override;
		void Clean() override;
	};

}