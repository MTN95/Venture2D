#include "Game.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdexcept>
#include "Input/InputManager.hpp"
#include "States/GameStates/GameStates.hpp"
#include "Collision/ContactListener.hpp"
#include "Util/ColorMacros.hpp"

#include "Util/Log.hpp"

namespace venture
{
	Game* Game::s_Instance = nullptr;

	Game::Game()
		: mWindow( nullptr )
		, mRenderer( nullptr )
		, mRunning( false )
		, mFullscreen( false )
	{
		InitSystems();

		mTicksCount = mTimer->PeekMilliseconds();

		//mCurrentState = std::shared_ptr<IGameState>( new MenuState(), IGameStateDeleter() );
		mCurrentState = new MenuState();

		mWorld = new b2World(b2Vec2(0.f, GRAVITY));

		mWorld->SetContactListener(ContactListener::get());



	}

	void Game::RunGame()
	{
		if ( !InitGame( "Venture2D-Engine", SCREEN_WIDTH, SCREEN_HEIGHT ,false) )
		{
			LOG_ERROR( "Game failed to initialize!: {0}\n", SDL_GetError() );
			throw std::runtime_error( "(Game): Failed to Initialize Game\n" );
		}

		while ( mRunning )
		{
			ProcessInput();
			Update();
			Render();

			// Perform the physics simulation step using the calculated time step
			mWorld->Step( 1.0f / 60.0f, 6, 2 );
			
			InputManager::get()->UpdatePrevInput();
		}
		Clean();
	}

	bool Game::InitGame( const char* title, int width, int height, bool fullscreen )
	{
		mWindow.reset( venture::Game::get()->CreateGameWindow( title, width, height, fullscreen ) );
		mRenderer.reset( CreateRenderer( mWindow.get() ) );
		if ( !LoadResources() )
		{
			LOG_ERROR( "Failed to load Game Resources!\n" );
			return false;
		}

		ChangeState( GameStateType::MENU );

		mRunning = true;

		return true;
	}

	void Game::ProcessInput()
	{
		SDL_Event event;
		auto      input = InputManager::get();
		input->ProcessInput( &event );
		mCurrentState->ProcessInput( input );
	}

	void Game::Update()
	{
		// Compute delta time
		// Wait until 16ms has elapsed since last frame
		while ( !SDL_TICKS_PASSED( mTimer->PeekMilliseconds(), mTicksCount + 16 ) )
			;

		float deltaTime = ( mTimer->PeekMilliseconds() - mTicksCount ) / 1000.0f;
		if ( deltaTime > 0.05f )
		{
			deltaTime = 0.05f;
		}
		mTicksCount = mTimer->PeekMilliseconds();

		// 		auto fps = 1.0f / deltaTime;
		// 		std::cout << "FPS: " << fps << '\n';
		// 		std::cout << "DeltaTime: " << deltaTime << '\n';

		mCurrentState->Update( deltaTime );

		
	}

	void Game::Render()
	{
		SDL_SetRenderDrawColor( mRenderer.get(), COLOR_WHITE.r, COLOR_WHITE.g, COLOR_WHITE.b, COLOR_WHITE.a );
		SDL_RenderClear( mRenderer.get() );

		mCurrentState->Render( mRenderer.get() );


		
		SDL_RenderPresent( mRenderer.get() );
	}

	void Game::Clean()
	{
		delete mWorld;

		mCurrentState->Clean();
		delete mCurrentState;

		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
	}

	SDL_Window* Game::CreateGameWindow( const char* title, int width, int height, bool fullscreen ) const
	{
		int window_flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;

		auto win = SDL_CreateWindow( title,
									 SDL_WINDOWPOS_CENTERED,
									 SDL_WINDOWPOS_CENTERED,
									 width,
									 height,
									 window_flags | SDL_WINDOW_RESIZABLE );
		if ( win == nullptr )
		{
			printf( "[Window]-[Error]: Window could not be created!: %s\n", SDL_GetError() );
			throw std::runtime_error( "(Window): Failed to Create Window\n" );
			return nullptr;
		}
		SDL_SetWindowResizable( mWindow.get(), SDL_TRUE );

		LOG_INFO( "Window Created!\n" );
		return win;
	}

	bool Game::LoadResources() { return true; }

	SDL_Renderer* Game::CreateRenderer( SDL_Window* window ) const
	{
		int           render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
		SDL_Renderer* ren = SDL_CreateRenderer( window, -1, render_flags );
		if ( ren == nullptr )
		{
			printf( "[Game]-[Error]: Renderer could not be created!: %s\n", SDL_GetError() );
			throw std::runtime_error( "(Window): Failed to Create Renderer!\n" );
			return nullptr;
		}

		return ren;
	}

	void Game::InitSystems()
	{
		if ( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
		{
			printf( "[Game]-[Error]: Failed to Initialize SDL: %s\n", SDL_GetError() );
			throw std::runtime_error( "(Window): Failed to Initialize SDL\n" );
		}

		int image_flags = IMG_INIT_PNG | IMG_INIT_JPG;
		if ( !( IMG_Init( image_flags ) & image_flags ) )
		{
			LOG_ERROR( "Failed to Initialize SDL_image: {0}\n", IMG_GetError() );
			throw std::runtime_error( "(Game): Failed to Initialize SDL_image!\n" );
		}

		if ( TTF_Init() == -1 )
		{
			LOG_ERROR( "Failed to Initialize SDL_image: {0}\n", TTF_GetError() );
			throw std::runtime_error( "Failed to Initialize SDL_ttf!\n" );
		}

		Log::Init();

		mTimer.reset( new Timer() );
		mTimer->Start();
	}

	void Game::ChangeState( GameStateType newState )
	{
		// The existing mCurrentState will be automatically cleaned up when it's reset
		// due to the custom deleter

// 		switch ( newState )
// 		{
// 			case GameStateType::INTRO:
// 				mCurrentState = std::shared_ptr<IntroState>( new IntroState(), IGameStateDeleter() );
// 				break;
// 			case GameStateType::MENU:
// 				mCurrentState = std::shared_ptr<MenuState>( new MenuState(), IGameStateDeleter() );
// 				break;
// 			case GameStateType::PLAY:
// 				mCurrentState = std::shared_ptr<PlayState>( new PlayState(), IGameStateDeleter() );
// 				break;
// 			case GameStateType::PAUSE:
// 				mCurrentState = std::shared_ptr<PauseState>( new PauseState(), IGameStateDeleter() );
// 				break;
// 			case GameStateType::OUTRO:
// 				mCurrentState = std::shared_ptr<OutroState>( new OutroState(), IGameStateDeleter() );
// 				break;
// 			default:
// 				LOG_ERROR( "Error, No such GameState exists!, Initializing MenuState... !\n" );
// 				mCurrentState = std::shared_ptr<MenuState>( new MenuState(), IGameStateDeleter() );
// 				break;
// 		}

		switch ( newState )
		{
			case GameStateType::INTRO:
				mCurrentState = new IntroState();
				break;
			case GameStateType::MENU:
				mCurrentState = new MenuState();
				break;
			case GameStateType::PLAY:
				mCurrentState = new PlayState();
				break;
			case GameStateType::PAUSE:
				mCurrentState = new PauseState();
				break;
			case GameStateType::OUTRO:
				mCurrentState = new OutroState();
				break;
			default:
				LOG_ERROR( "Error, No such GameState exists!, Initializing MenuState... !\n" );
				mCurrentState = new MenuState();
				break;
		}

		// Initialize the new state
		if ( mCurrentState )
		{
			mCurrentState->Init();
		}
	}

}
