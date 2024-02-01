#pragma once

#include <SDL2/SDL.h>
#include "IGameState.hpp"
#include "../../Graphics/Button.hpp"
#include <memory>

namespace venture
{
	class Timer;

	enum class MenuType
	{
		MAIN,       // shows game's main menu
		OPTIONS,    // shows game's options
		CREDITS,    // shows game's credits
		QUIT        // shows an exit screen and quit the game
	};

	/*
	* Handles the game's main menu screen, and it's other "windows" options, credits, etc.
	*/
	class MenuState : public IGameState
	{
	public:

		MenuState();
		~MenuState() override;

		void Init() override;
		void ProcessInput( InputManager* input ) override;
		void Update( float deltaTime ) override;
		void Render( SDL_Renderer* renderer ) override;
		void Clean() override;

		void SwitchMenu( MenuType newMenu ) { mCurrentMenu = newMenu; }
		void RenderMain( SDL_Renderer* renderer );
		void RenderOptions( SDL_Renderer* renderer );
		void RenderCredits( SDL_Renderer* renderer );

	private:
		MenuType mCurrentMenu;

		// Main Menu Buttons
		std::unique_ptr<Button, ButtonDeleter> mPlayButton;
		std::unique_ptr<Button, ButtonDeleter> mOptionsButton;
		std::unique_ptr<Button, ButtonDeleter> mCreditsButton;
		std::unique_ptr<Button, ButtonDeleter> mBackButton;
		std::unique_ptr<Button, ButtonDeleter> mQuitButton;

		std::unique_ptr<TextRenderer, TextRendererDeleter>           mTextRenderer;


	};
}