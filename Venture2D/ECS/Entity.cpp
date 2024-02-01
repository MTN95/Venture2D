#include "Entity.hpp"
#include <SDL2/SDL.h>
#include "Components/TransformComponent.hpp"
#include "Components/ShapeComponent.hpp"
#include "../Util/Common.hpp"



// Decouple sprite management 

namespace venture
{
	Entity::Entity(const std::string_view& entityName)
	{
		mEntityName = entityName;
		mEntityID = GetEntityID();
	}

	Entity::Entity( const Entity& other )
		: mEntityName( other.mEntityName )
		, mEntityID( other.mEntityID )
		, mEntityWidth( other.mEntityWidth )
		, mEntityHeight( other.mEntityHeight )
		, mTransfromComp ( other.mTransfromComp )
	{
		// Deep copying mIndexToComponentMap
		for ( const auto& pair : other.mIndexToComponentMap )
		{
			if ( pair.second )
			{
				// Assuming IComponent has a clone method or similar
				mIndexToComponentMap[ pair.first ] = std::unique_ptr<IComponent,IComponentDeleter>( pair.second->Clone() );
			}
		}

		// Deep copying mNameToSpriteMap
		for ( const auto& pair : other.mNameToSpriteMap )
		{
			if ( pair.second )
			{
				// Assuming Sprite has a suitable copy constructor
				mNameToSpriteMap[pair.first] = std::unique_ptr<Sprite, SpriteDeleter>(pair.second->Clone());
			}
		}
	
	}

// 	Entity::Entity( Entity&& other ) noexcept
// 		: mName( std::move( other.mName ) )
// 		, mEntityID( other.mEntityID )
// 		, mEntityWidth( other.mEntityWidth )
// 		, mEntityHeight( other.mEntityHeight )
// 		// ... Move other members ...
// 	{
// 		// Move resources from other to this
// 		// Set other's resources to default state
// 	}

	Entity::~Entity()
	{
		Clean();
	}

	void Entity::Init()
	{
		glm::vec2 SCREEN( SCREEN_WIDTH, SCREEN_HEIGHT );
		mTransfromComp = AddComponent<TransformComponent>( glm::vec2{ SCREEN.x / 2.f, SCREEN.y / 2.f } );
		if ( !mTransfromComp )
		{
			LOG_DEBUG( "Entity Transform Component is invalid!" );
		}
	}

	void Entity::Update( float deltaTime )
	{
		UpdateComponents( deltaTime );
		UpdateSprites( deltaTime );
		//mEntitySprite->Update( deltaTime );
	}

	void Entity::Render( SDL_Renderer* renderer )
	{
		// Render entity sprites here
		//mEntitySprite->RenderFrame( renderer, mTransfromComp->GetPosition().x, mTransfromComp->GetPosition().y );
		
		/// needs check if shape or sprite 
		this->GetComponent<ShapeComponent>()->Render(renderer);

	}

	void Entity::Clean()
	{
		CleanComponents();
		CleanSprites();
	}

	const glm::vec2 Entity::GetPosition()
	{
		if ( mTransfromComp == nullptr )
		{
			LOG_WARN( "Entity's transform component is invalid!" );
			return glm::vec2();
		}

		return mTransfromComp->GetPosition();
	}

	const float Entity::GetRotation()
	{
		return mTransfromComp->GetRotation();
	}

	const glm::vec2 Entity::GetScale()
	{
		return mTransfromComp->GetScale();
	}

	const void Entity::SetPosition( const glm::vec2& position )
	{
		if ( mTransfromComp == nullptr )
		{
			LOG_WARN( "Entity's transform component is invalid!\n" );
			return;
		}

		mTransfromComp->SetPosition( position );
	}
	const void Entity::SetScale( const glm::vec2& scale )
	{
		if ( mTransfromComp == nullptr )
		{
			LOG_WARN( "Entity's transform component is invalid!\n" );
			return;
		}

		mTransfromComp->SetScale( scale );
	}

	const void Entity::SetRotation( float rotation )
	{
		if ( mTransfromComp == nullptr )
		{
			LOG_WARN( "Entity's transform component is invalid!\n" );
			return;
		}

		mTransfromComp->SetRotation( rotation );
	}

	bool Entity::AddSprite( const std::string& name, std::unique_ptr<Sprite> newSprite )
	{
		if(newSprite == nullptr)
		{
			LOG_INFO("Sprite is nullptr\n");
			return false;
		}

		mEntityWidth = newSprite->GetSpriteWidth();
		mEntityHeight = newSprite->GetSpriteHeight();

		auto it = mNameToSpriteMap.find( name );
		if ( it == mNameToSpriteMap.end() )
		{
			mNameToSpriteMap[ name ].reset(newSprite.get());
			LOG_DEBUG( "Sprite {0} Added to Entity {1}", name, mEntityName );
			return true;
		}
		LOG_DEBUG( "Sprite {0} Already exists in Entity {1}!", name, mEntityName );
		return false;
	}

	void Entity::RemoveSprite( const std::string& name )
	{
		auto it = mNameToSpriteMap.find( name );
		if ( it != mNameToSpriteMap.end() )
		{
			mNameToSpriteMap.erase( name );
			LOG_DEBUG( "Sprite {0} Deleted from Entity {1}", name, mEntityName );
		}
	}

	Sprite* Entity::GetSprite( const std::string& name )
	{
		auto it = mNameToSpriteMap.find( name );
		if ( it != mNameToSpriteMap.end() )
		{
			return mNameToSpriteMap[ name ].get();
		}
		LOG_DEBUG( "Sprite {0} Does not exists in Entity {1}!", name, mEntityName );
		return nullptr;
	}

	void Entity::SetSprite( const std::string& name,std::unique_ptr<Sprite> newSprite )
	{
		auto it = mNameToSpriteMap.find( name );
		if ( it != mNameToSpriteMap.end() )
		{
			mNameToSpriteMap[ name ].reset(newSprite.get());
		}
	}

	void Entity::UpdateSprites( float deltaTime )
	{
		for ( auto& sprite : mNameToSpriteMap )
		{
			sprite.second->Update(deltaTime);
		}
	}

	void Entity::CleanSprites()
	{
		mNameToSpriteMap.clear();
	}

	void Entity::UpdateComponents( float deltaTime )
	{
		for ( auto& component : mIndexToComponentMap )
		{
			component.second->Update( deltaTime );
		}
	}
	void Entity::CleanComponents()
	{
		mIndexToComponentMap.clear();
	}

	const void Entity::LogComponents() const
	{
		for(auto& component : mIndexToComponentMap)
		{
			auto id = component.first;
			auto name = component.second->mEntityName;
			LOG_INFO("comp id, name: {0} - {1}", id,name);
		}
	}
}