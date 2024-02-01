#include "OutroState.hpp"
#include "../../Util/Common.hpp"
#include "../../Util/ColorMacros.hpp"
#include "../../Util/Log.hpp"
#include "../../Game.hpp"
#include <glm/glm.hpp>

namespace venture
{
	OutroState::~OutroState()
	{ Clean(); }

	void OutroState::Init()
	{
		mOutroTimer = std::unique_ptr<Timer,TimerDeleter>( new Timer(), TimerDeleter() );

		std::string quitMsg = "Thank you for Playing Venture2D, Goodbye.";
		mQuitText = std::unique_ptr<TextRenderer, TextRendererDeleter>( new TextRenderer(quitMsg.c_str(), 24, COLOR_DEEPORANGE), TextRendererDeleter() );
		mQuitText->CreateText();

	}

	void OutroState::ProcessInput( InputManager* input )
	{}

	void OutroState::Update( float deltaTime )
	{}

	void OutroState::Render( SDL_Renderer* renderer )
	{
		SDL_SetRenderDrawColor( renderer, COLOR_BLUEGREY.r, COLOR_BLUEGREY.g, COLOR_BLUEGREY.b, 255 );
		SDL_RenderClear( renderer );

		glm::vec2 SCREEN( SCREEN_WIDTH, SCREEN_HEIGHT );


		auto& size = mQuitText->GetTextTexture()->GetTextureSize();
		glm::ivec2 halfSize = { size.x / 2, size.y / 2 };

		mQuitText->RenderText( renderer, glm::vec2( ( SCREEN_WIDTH / 2.f ) - halfSize.x, ( SCREEN_HEIGHT / 2.f ) - halfSize.y ) );

		mOutroTimer->SetTimer( 1, [ & ]()
		{
			LOG_DEBUG( "QUITTING FROM OUTRO YES MAN BYE" );
			Game::get()->QuitGame();
		} );
	}

	void OutroState::Clean()
	{
		
	}
}