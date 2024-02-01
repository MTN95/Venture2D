#pragma once

#include <memory>
#include <unordered_map>
#include "IGameState.hpp"
#include "../../Util/Log.hpp"
#include "../../ECS/Entity.hpp"

namespace venture
{

/*
 * Handles the game play state, meaning the actual gameplay of the game.
 * When you press play, there will be an instructions screen (or something similar)
 * before you enter the "Play-State".
 */
	class PlayState : public IGameState
	{
	public:
		using UEntity = std::unique_ptr<Entity, EntityDeleter>;
		using EntityMap = std::unordered_map<std::string, UEntity>;

		PlayState() = default;
		~PlayState() override;

		void Init() override; 
		void ProcessInput( InputManager* input ) override;
		void Update( float deltaTime ) override;
		void Render( SDL_Renderer* renderer ) override;
		void Clean() override;

		// Should be managed by the EntityManager
		void AddEntity( const std::string& id, std::unique_ptr<Entity, EntityDeleter>& entity );
		std::unique_ptr<Entity, EntityDeleter>& GetEntity( const std::string& id );
		void RemoveObject( const std::string& id );
		//----------------------------------------

	private:
		SDL_FRect myGround;

		// Should be managed by the EntityManager
		EntityMap mTotalEntities;
		UEntity entityBox;
		//----------------------------------------

	};

}