#pragma once

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include "../IComponent.hpp"
#include "../../Shapes/IShape.hpp"

namespace venture
{


	class ShapeComponent : public IComponent
	{
	public:
		/**
		* @brief The shape component constructor.
		*/
		ShapeComponent(IShape* shape);

		/**
		* @brief The shape component copy constructor.
		*/
		ShapeComponent( const ShapeComponent& other );

		/**
		* @brief The shape component move constructor.
		*/
		ShapeComponent( ShapeComponent&& other ) noexcept;


		/**
		* @brief The shape component copy assignment operator.
		*/
		ShapeComponent& operator=( const ShapeComponent& other );


		/**
		* @brief The shape component move assignment operator.
		*/
		ShapeComponent& operator=( ShapeComponent&& other ) noexcept;

		/**
		* @brief The shape component destructor.
		*/
		~ShapeComponent() override;

		/**
		* @brief The shape component update function.
		*/
		void Update( float deltaTime ) override;

		/**
		* @brief The shape component clone function.
		*/
		std::unique_ptr<IComponent, IComponentDeleter> Clone() const override
		{
			return std::unique_ptr<IComponent, IComponentDeleter>( new ShapeComponent( *this ) );
		}

		// Method to render the shape
		void Render( SDL_Renderer* renderer );

		IShape* GetShape() const noexcept { return mShape; }

	private:
		
		IShape* mShape;

	};
}
