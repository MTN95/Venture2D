#pragma once

#include <iostream>
#include <unordered_map>
#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include <string_view>
#include <glm/glm.hpp>

#include "IComponent.hpp"
#include "../Graphics/Sprite.hpp"

namespace venture
{
	class Entity
	{
	public:
		Entity(const std::string_view& entityName);
		Entity(const Entity& other);
		//Entity(const Entity&& other) noexcept;
		virtual ~Entity();

		virtual void Init();
		virtual void Update( float deltaTime );
		virtual void Render( SDL_Renderer* renderer );
		void Clean();

		void SetComponentName( std::string_view newName ) { mEntityName = newName; }
		void SetID( std::size_t newID ) { mEntityID = newID; }

		std::string_view GetName() const { return mEntityName; }
		std::size_t GetID() const { return mEntityID; }

		const glm::vec2 GetPosition();
		const float GetRotation();
		const glm::vec2 GetScale();

		const void SetPosition( const glm::vec2& position );
		const void SetScale( const glm::vec2& scale );
		const void SetRotation( float rotation );
		
		const int GetEntityWidth() const { return mEntityWidth;}
		const int GetEntityHeight() const { return mEntityHeight;}

		// Sprite Utility Functions - NEEDS DECOUPLING
		// ------------------------------------------------------------------------
		
		bool AddSprite(const std::string& name, std::unique_ptr<Sprite> newSprite);
		
		void RemoveSprite(const std::string& name);
		void SetSprite(const std::string& name, std::unique_ptr<Sprite> newSprite);
		void UpdateSprites( float deltaTime );
		void CleanSprites();
		
		Sprite* GetSprite(const std::string& name);

		// ------------------------------------------------------------------------

		// Components Utility Functions
		// ------------------------------------------------------------------------
		
		template<typename T>
		T* GetComponent()
		{
			auto compID = getComponentTypeID<T>();
			auto it = mIndexToComponentMap.find( compID );
			if ( it != mIndexToComponentMap.end() )
			{
				// Use .get() to obtain the raw pointer from unique_ptr
				return static_cast< T* >( it->second.get() );
			}
			return nullptr;
		}

		template<typename T, typename... TArgs>
		T* AddComponent( TArgs&&... args )
		{
			auto compID = getComponentTypeID<T>();
			std::unique_ptr<T, IComponentDeleter> component( new T( std::forward<TArgs>( args )... ) );
			T* rawPtr = component.get();
			mIndexToComponentMap[ compID ] = std::move( component );
			return rawPtr;
		}


		template<typename T>
		void RemoveComponent()
		{
			auto compID = getComponentTypeID<T>();
			auto it = mIndexToComponentMap.find( compID );
			if ( it != mIndexToComponentMap.end() )
			{
				// unique_ptr will automatically delete the object it owns when erased
				mIndexToComponentMap.erase( it );
			}
		}

		void UpdateComponents( float deltaTime );
		void CleanComponents();

		inline const size_t GetComponentCount() const { return mIndexToComponentMap.size();}

		const void LogComponents() const;
		// ------------------------------------------------------------------------

		inline bool operator==( const Entity& other ) const { return mEntityID == other.mEntityID; }
		inline bool operator!=( const Entity& other ) const { return !( mEntityID != other.mEntityID ); }

		friend std::ostream& operator<<( std::ostream& os, const Entity& entity ) noexcept
		{
			auto id = entity.mEntityID;
			os << "[Entity ID]: " << '[' <<  id << ']';
			return os;
		}

	private:

		std::size_t GetEntityID()
		{
			static std::size_t entityID = 0;
			return ++entityID;
		}

		std::size_t getUniqueComponentTypeID()
		{
			static std::size_t typeID = 0;
			return ++typeID;
		}

		template<typename T>
		inline std::size_t getComponentTypeID() noexcept
		{
			static_assert( std::is_base_of<IComponent, T>::value, "Type not a child of IComponent!." );
			static const std::size_t typeID = getUniqueComponentTypeID();
			return typeID;
		}

	private:
		class TransformComponent* mTransfromComp;

		//std::unordered_map<std::size_t, IComponent*> mIndexToComponentMap;
		std::unordered_map<std::size_t, std::unique_ptr<IComponent,IComponentDeleter>> mIndexToComponentMap;
		std::unordered_map<std::string, std::unique_ptr<Sprite,SpriteDeleter>> mNameToSpriteMap;

		// Name and ID are being set when created by the EntityManager.
		std::string_view mEntityName;
		std::size_t mEntityID;

		int mEntityWidth;
		int mEntityHeight;
	};


	struct EntityDeleter
	{
		void operator()( Entity* e ) const
		{
			e->Clean();
			delete e;
		}
	};

}