#include "PlayState.hpp"
#include "../../Game.hpp"
#include "../../Util/Log.hpp"
#include "../../Input/InputManager.hpp"
#include "../../Util/ColorMacros.hpp"
#include "../../ECS/Components/ShapeComponent.hpp"
#include "../../ECS/Components/BoxCollisionComponent.hpp"
#include "../../Shapes/RectangleShape.hpp"

namespace venture
{
	PlayState::~PlayState() {}

	void PlayState::Init()
	{
		LOG_INFO( "Initializing PlayState!\n" );


		float groundHeight = 30.f;

		myGround.x = 10.f;
		myGround.y = static_cast<float>(SCREEN_HEIGHT) - groundHeight;
		myGround.w = 1900.f;
		myGround.h = groundHeight;

		entityBox = std::unique_ptr<Entity, EntityDeleter>( new Entity( "entityBox" ), EntityDeleter() );
		
		entityBox != nullptr ? LOG_DEBUG( "ent Box is OK" ) : LOG_DEBUG( "INVALID NOT OK" );

		RectConfig rectCfg( 50.f,20.f, glm::vec2{ 100.f,250.f }, COLOR_DARKGREEN, 0);
		
		// Create a RectangleShape dynamically
		auto rectA = new RectangleShape( rectCfg );

		entityBox->AddComponent<ShapeComponent>( rectA );

		auto game = Game::get();
		
		auto entityRect = SDL_FRect( 0.f
													,0.f
													,static_cast< float >( entityBox->GetEntityWidth() )
													,static_cast< float >( entityBox->GetEntityHeight() )
													);

		entityBox->AddComponent<BoxCollisionComponent>( entityRect );
		

		//----------------------------------------
		// Should be managed by the EntityManager
		//----------------------------------------
		AddEntity( std::string( entityBox->GetName() ), entityBox );
	}

	void PlayState::ProcessInput( InputManager* input )
	{
		if ( input->isKeyPressed(SDL_SCANCODE_ESCAPE))
		{
			Game::get()->ChangeState(GameStateType::OUTRO);
		}

	}

	void PlayState::Update( float deltaTime ) 
	{
		//----------------------------------------
		// Should be managed by the EntityManager
		//----------------------------------------
		for ( auto& [id, entity] : mTotalEntities )
		{
			entity->Update( deltaTime );
		}

	}

	void PlayState::Render( SDL_Renderer* renderer )
	{
		//----------------------------------------
		// Testing 
		//----------------------------------------
		SDL_SetRenderDrawColor( renderer, COLOR_RED.r, COLOR_RED.g, COLOR_RED.b, 255 );
		SDL_RenderFillRectF( renderer, &myGround );
		
		//----------------------------------------
		// Should be managed by the EntityManager
		//----------------------------------------
		for ( auto& [id, entity] : mTotalEntities )
		{
			entity->Render( renderer );
			if ( entity->GetComponent<ShapeComponent>() )
			{
				entity->GetComponent<ShapeComponent>()->Render( renderer);
			}
		}

	}

	void PlayState::Clean() 
	{
		mTotalEntities.clear();
		LOG_INFO("Cleaning PlayState! .. .. .. ");
	}

	//----------------------------------------
	// Should be managed by the EntityManager
	//----------------------------------------
	void PlayState::AddEntity( const std::string& id, std::unique_ptr<Entity, EntityDeleter>& entity )
	{
		mTotalEntities[ id ] = std::unique_ptr<Entity, EntityDeleter>( entity.get() );
	}

	//----------------------------------------
	// Should be managed by the EntityManager
	//----------------------------------------
	std::unique_ptr<Entity, EntityDeleter>& PlayState::GetEntity( const std::string& id )
	{
		static std::unique_ptr<Entity, EntityDeleter> nullEntity = nullptr;

		auto it = mTotalEntities.find( id );
		if ( it != mTotalEntities.end() )
		{
			return it->second;
		}
		LOG_ERROR( "Game Object Is nullptr!" );
		return nullEntity;
	}

	//----------------------------------------
	// Should be managed by the EntityManager
	//----------------------------------------
	void PlayState::RemoveObject( const std::string& id ) { mTotalEntities.erase( id ); }

}