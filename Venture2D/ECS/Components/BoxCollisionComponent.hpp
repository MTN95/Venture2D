#pragma once

#include <sdl2/SDL.h>
#include "../IComponent.hpp"

namespace venture
{
	class BoxCollisionComponent : public IComponent
	{
	public:
		/**
		* @brief The box collision component constructor.
		*/
		BoxCollisionComponent( const SDL_FRect& rect );

		/**
		* @brief The box collision component copy constructor.
		*/
		BoxCollisionComponent( const BoxCollisionComponent& other );

		/**
		* @brief The box collision component move constructor.
		*/
		BoxCollisionComponent( BoxCollisionComponent&& other ) noexcept;


		BoxCollisionComponent& operator=( const BoxCollisionComponent& other );
		BoxCollisionComponent& operator=( BoxCollisionComponent&& other ) noexcept;


		/**
		* @brief The box collision component destructor.
		*/
		~BoxCollisionComponent() override;

		/**
		* @brief Simple collision detection using SDL_HasIntersected()
		* @return returns an SDL_bool.
		* SDL_TRUE if an intersection happened, SDL_FALSE otherwise.
		*/
		bool IsColliding( const BoxCollisionComponent& other );

		/**
		 * @brief Get the box collision component
		 *
		 * @return returns an SDL_Rect
		*/
		const SDL_FRect& GetBoxCollision() const { return mBoxCollision; }


		void Update( float deltaTime ) override;

		std::unique_ptr<IComponent, IComponentDeleter> Clone() const override
		{
			return std::unique_ptr<BoxCollisionComponent, IComponentDeleter>( new BoxCollisionComponent( *this ), IComponentDeleter() );
		}
		
	private:
		SDL_FRect mBoxCollision;
	};
}
