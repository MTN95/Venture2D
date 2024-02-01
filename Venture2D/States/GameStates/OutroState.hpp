#pragma once
#include "IGameState.hpp"
#include "../../Graphics/TextRenderer.hpp"
#include "../../Util/Timer.hpp"
#include <memory>

namespace venture
{
	/*
	* Handles the game's outro when you exit.
	*/
	class OutroState : public IGameState
	{

	public:
		~OutroState() override;

		void Init() override;


		void ProcessInput( InputManager* input ) override;


		void Update( float deltaTime ) override;


		void Render( SDL_Renderer* renderer ) override;


		void Clean() override;

	private:
		std::unique_ptr<TextRenderer, TextRendererDeleter> mQuitText;
		std::unique_ptr<Timer,TimerDeleter> mOutroTimer;
	};

}