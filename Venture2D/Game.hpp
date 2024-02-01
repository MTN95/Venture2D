#pragma once

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <cstdint>
#include <memory>
#include <Box2d/b2_world.h>

#include "States/GameStates/IGameState.hpp"
#include "Graphics/TextRenderer.hpp"
#include "Util/Timer.hpp"
#include "Util/Common.hpp"


namespace venture
{

	struct SDLWindowDeleter
	{
		void operator()( SDL_Window* w ) const { SDL_DestroyWindow( w ); }
	};

	struct SDLRendererDeleter
	{
		void operator()( SDL_Renderer* r ) const { SDL_DestroyRenderer( r ); }
	};

	enum struct GameStateType
	{
		INTRO = 1,
		MENU,
		PLAY,
		PAUSE,
		OUTRO,
		GAMEOVER,
		GAMEWON
	};

	class Game
	{
	public:
		// @brief get the game single instance, this class follows the Singleton pattern.
		// NOTE: no point in having more than one instance of the Game class
		static Game* get()
		{
			if ( s_Instance == nullptr )
			{
				s_Instance = new Game();
			}
			return s_Instance;
		}

		// @brief initializes, updates and runs the game main loop.
		void RunGame();

		SDL_Renderer* GetRenderer() const { return mRenderer.get(); }

		const void QuitGame() { mRunning = false; }

		const glm::vec2& GetScreenDimention() const { return { SCREEN_WIDTH, SCREEN_HEIGHT }; }

		IGameState* GetCurrentState() { return mCurrentState; }

		/**
		 * @brief Game's timer
		 */
		const Timer& GetGameTimer() const { return *mTimer; }

		void ChangeState( GameStateType newState );

		b2World* GetWorld() const noexcept { return mWorld; }

	private:

		// @brief initializes the game dependencies, resources and game objects
		bool InitGame( const char* title, int width, int height, bool fullscreen = false );
		// @brief processes player input
		void ProcessInput();
		// @brief updates all of the game dependencies, resources and game objects.
		void Update();
		// @brief renders all of the game textures, sounds and game objects.
		void Render();
		// @brief calls destructor, which cleans all of the game resources.
		void Clean();
		// @brief loads up needed resources such as textures, sfx, music etc..
		bool LoadResources();


		Game();

		SDL_Window* CreateGameWindow( const char* title,
									  int         width,
									  int         height,
									  bool        fullscreen = false ) const;

		SDL_Renderer* CreateRenderer( SDL_Window* window ) const;

		void InitSystems();

		static Game* s_Instance;

		std::unique_ptr<SDL_Window, SDLWindowDeleter>     mWindow;
		std::unique_ptr<SDL_Renderer, SDLRendererDeleter> mRenderer;

		bool mRunning;
		bool mFullscreen;

		std::unique_ptr<Timer, TimerDeleter>           mTimer;


		
		uint64_t                                       mTicksCount;
		
		IGameState* mCurrentState;

		b2World* mWorld;

		Game( const Game& other ) = delete;
		Game& operator=( const Game& other ) = delete;
		Game( Game&& other ) = delete;
		Game& operator=( Game&& other ) = delete;
	};
}
