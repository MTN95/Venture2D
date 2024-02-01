#include "MenuState.hpp"
#include "../../Game.hpp"
#include "../../Util/Log.hpp"
#include "../../Util/Common.hpp"
#include "../../Util/ColorMacros.hpp"
#include "../../Input/InputManager.hpp"
#include <glm/glm.hpp>


namespace venture
{
	MenuState::MenuState()
		: mCurrentMenu( MenuType::MAIN )
	{ }

	MenuState::~MenuState()
	{
		//LOG_INFO( "Cleaning MenuState!\n" );
		//Clean();
	}

	void MenuState::Init()
	{
		LOG_INFO( "Initializing MenuState!\n" );
		mCurrentMenu = MenuType::MAIN;

		float xAxisCenter = SCREEN_WIDTH / 2.f;

		glm::vec2 playButtonPosition( glm::vec2( xAxisCenter, ( SCREEN_HEIGHT / 3.f ) ) );
		glm::vec2 optionsButtonPosition( glm::vec2( xAxisCenter, ( SCREEN_HEIGHT / 3.f ) + 50.f ) );
		glm::vec2 creditsButtonPosition( glm::vec2( xAxisCenter, ( SCREEN_HEIGHT / 3.f ) + 100.f ) );
		glm::vec2 quitButtonPosition( glm::vec2( xAxisCenter, ( SCREEN_HEIGHT / 3.f ) + 150.f ) );

		glm::vec2 backButtonPosition( SCREEN_WIDTH / 10.f, SCREEN_HEIGHT - 50.f );

		mPlayButton = std::unique_ptr<Button, ButtonDeleter>( new Button( "Play", 30, playButtonPosition ), ButtonDeleter() );
		mOptionsButton = std::unique_ptr<Button, ButtonDeleter>( new Button( "Options", 30, optionsButtonPosition ), ButtonDeleter() );
		mCreditsButton = std::unique_ptr<Button, ButtonDeleter>( new Button( "Credits", 30, creditsButtonPosition ), ButtonDeleter() );
		mQuitButton = std::unique_ptr<Button, ButtonDeleter>( new Button( "Quit", 30, quitButtonPosition ), ButtonDeleter() );
		mBackButton = std::unique_ptr<Button, ButtonDeleter>( new Button( "Back", 30, backButtonPosition ), ButtonDeleter() );

		mTextRenderer = std::unique_ptr<TextRenderer, TextRendererDeleter>( new TextRenderer( "Hello BITCH", 26, SDL_Color( 255, 200, 0, 255 ) ), TextRendererDeleter() );
		mTextRenderer->CreateText();
	}

	void MenuState::ProcessInput( InputManager* input )
	{
		mPlayButton->ProcessInput( input );
		mOptionsButton->ProcessInput( input );
		mCreditsButton->ProcessInput( input );
		mBackButton->ProcessInput( input );
		mQuitButton->ProcessInput( input );

		if ( input->isKeyPressed( SDL_SCANCODE_ESCAPE ) )
		{
			Game::get()->ChangeState( GameStateType::OUTRO );
		}
	}

	void MenuState::Update( float deltaTime )
	{
				// if mouse location is outside buttons
		auto input = InputManager::get();

		auto mouseX = input->GetMouseX();
		auto mouseY = input->GetMouseY();

		bool mouseOverPlayBtn = ( mouseX == mPlayButton->GetPosition().x ) && ( mouseY == mPlayButton->GetPosition().y );
		bool mouseOverOptionsBtn = ( mouseX == mOptionsButton->GetPosition().x ) && ( mouseY == mOptionsButton->GetPosition().y );
		bool mouseOverCreditsBtn = ( mouseX == mCreditsButton->GetPosition().x ) && ( mouseY == mCreditsButton->GetPosition().y );
		bool mouseOverQuitBtn = ( mouseX == mQuitButton->GetPosition().x ) && ( mouseY == mQuitButton->GetPosition().y );

		// This code manages the mouse button's locking and unlocking mechanism.
		// This mechanism ensures that clicks are only registered when the mouse button's 
		// press and release actions occur within the designated button boundaries.
		if ( !mouseOverPlayBtn || !mouseOverOptionsBtn || !mouseOverCreditsBtn || !mouseOverQuitBtn )
		{
			bool leftButtunDown = input->isMouseButtonDown( MouseButton::LEFT );
			bool leftButtunPressed = input->isMouseButtonPressed( MouseButton::LEFT );
			bool RightButtunDown = input->isMouseButtonDown( MouseButton::RIGHT );
			bool RightButtunPressed = input->isMouseButtonPressed( MouseButton::RIGHT );

			if ( leftButtunDown || leftButtunPressed || RightButtunDown || RightButtunPressed )
			{
				LOG_INFO( "PRESSING" );
				input->LockMouse();
			}
			if ( input->isMouseButtonReleased( MouseButton::LEFT ) )
			{
				LOG_INFO( "RELEASED" );
				input->UnlockMouse();
			}
		}

		// Text Animation Test -------------------------------------------------

		mPlayButton->ApplySineAnimation( deltaTime, 1.3f, 25.f, 0.0f );       // No offset
		mOptionsButton->ApplySineAnimation( deltaTime, 1.3f, 25.f, 0.1f );    // Slight offset
		mCreditsButton->ApplySineAnimation( deltaTime, 1.3f, 25.f, 0.2f );    // A bit more offset
		mBackButton->ApplySineAnimation( deltaTime, 1.3f, 25.f, 0.3f );       // Even more offset
		mQuitButton->ApplySineAnimation( deltaTime, 1.3f, 25.f, 0.4f );       // Maximum offset

		// ---------------------------------------------------------------------

		const auto& game = Game::get();
		

		if (mOptionsButton)
		{
			if ( mOptionsButton->isButtonPressed() )
			{
				mOptionsButton->ResetButton();
				SwitchMenu( MenuType::OPTIONS );
			}
		}

		if (mCreditsButton)
		{
			if ( mCreditsButton->isButtonPressed() )
			{
				mCreditsButton->ResetButton();
				SwitchMenu( MenuType::CREDITS );
			}	
		}

		if (mBackButton)
		{
			if ( mBackButton->isButtonPressed() )
			{
				mBackButton->ResetButton();
				SwitchMenu( MenuType::MAIN );
			}
		}
		// ERROR, order matters, don't seems to understand why, 
		// connected to the current game state variable inside game class
		// and the change state function.
		// which ever is not the last in this update function makes problems.
		// seems like the class gets deleted and a run time error is thrown.

		if ( mQuitButton )
		{
			if ( mQuitButton->isButtonPressed() )
			{
				mQuitButton->ResetButton();
				game->ChangeState( GameStateType::OUTRO );
			}
		}

		if ( mPlayButton )
		{
			if ( mPlayButton->isButtonPressed() )
			{
				mPlayButton->ResetButton();
				game->ChangeState( GameStateType::PLAY );
			}
		}

	}

	void MenuState::Render( SDL_Renderer* renderer )
	{
		switch ( mCurrentMenu )
		{
			case MenuType::MAIN:
				RenderMain( renderer );
				break;
			case MenuType::OPTIONS:
				RenderOptions( renderer );
				break;
			case MenuType::CREDITS:
				RenderCredits( renderer );
				break;
			default:
				break;
		}
	}

	void MenuState::Clean()
	{
// 		if( mPlayButton )
// 			mPlayButton->Clean();
// 		if ( mOptionsButton )
// 			mOptionsButton->Clean();
// 		if ( mCreditsButton )
// 			mCreditsButton->Clean();
// 		if ( mBackButton )
// 			mBackButton->Clean();
// 		if ( mQuitButton )
// 			mQuitButton->Clean();
	}

	void MenuState::RenderMain( SDL_Renderer* renderer )
	{
		SDL_SetRenderDrawColor( renderer, COLOR_LIGHTGREY.r, COLOR_LIGHTGREY.g, COLOR_LIGHTGREY.b, 255 );
		SDL_RenderClear( renderer );

		mPlayButton->Render( renderer );
		mOptionsButton->Render( renderer );
		mCreditsButton->Render( renderer );
		mQuitButton->Render( renderer );

		mTextRenderer->RenderText(renderer,{ 100.f,100.f });
	}

	void MenuState::RenderOptions( SDL_Renderer* renderer )
	{
		SDL_SetRenderDrawColor( renderer, COLOR_LIGHTBLUE.r, COLOR_LIGHTBLUE.g, COLOR_LIGHTBLUE.b, 255 );
		SDL_RenderClear( renderer );

		mBackButton->Render( renderer );
	}

	void MenuState::RenderCredits( SDL_Renderer* renderer )
	{
		SDL_SetRenderDrawColor( renderer, COLOR_DARKGREY.r, COLOR_DARKGREY.g, COLOR_DARKGREY.b, 255 );
		SDL_RenderClear( renderer );

		mBackButton->Render( renderer );
	}

}