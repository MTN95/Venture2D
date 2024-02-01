#pragma once
#include "IGameState.hpp"
namespace venture
{
	/*
	* Handles the game's intro when you first enter it.
	*/
	class IntroState : public IGameState
	{

	public:
		~IntroState() override;

		void Init() override;


		void ProcessInput( InputManager* input ) override;


		void Update(float deltaTime) override;


		void Render(SDL_Renderer* renderer) override;


		void Clean() override;

	};

}