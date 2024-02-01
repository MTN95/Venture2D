#pragma once
#include <glm/glm.hpp>
#include <string>
#include <SDL2/SDL_pixels.h>
#include <Box2d/b2_shape.h>

#include "../Math/Math.hpp"
#include "../Util/ColorMacros.hpp"

namespace venture
{
	enum class ShapeType
	{
		RECTANGLE,
		CIRCLE,
		TRIANGLE
		// Add more shape types as needed
	};

	class IShape
	{
	public:
		virtual ~IShape() = default;

		// Pure virtual functions for common shape functionality
		
		/**
		 * @brief Get the Box2D shape 
		 */
		//virtual const b2Shape& GetBox2DShape() const = 0;

		/**
		 * @brief Get the shape Area
		 */
		virtual double Area() const noexcept = 0;
		
		/**
		 * @brief Get the shape Perimeter
		 */
		virtual double Perimeter() const noexcept = 0;

		/**
		 * @brief Scale the shape, scaleFactor * Length, scaleFactor * Width
		 */
		virtual void Scale( float scaleFactor ) noexcept = 0;
		
		/**
		 * @brief Get the shape BoundingBox
		 */
		virtual glm::vec2 GetBoundingBox() const noexcept = 0;

		/**
		 * @brief Clone the shape
		 */
		virtual IShape* Clone() const = 0;
		
		
		// Accessor and Mutator methods for properties
		/**
		 * @brief Get the shape type
		 */
		ShapeType GetShapeType() const noexcept { return mShapeType; }

		/**
		 * @brief Set the shape type
		 */
		void SetShapeType( ShapeType type ) noexcept { mShapeType = type; }

		/**
		 * @brief Set the shape color
		 */
		SDL_Color GetShapeColor() const noexcept { return mShapeColor; }
		
		/**
		 * @brief Set the shape color
		 */
		void SetShapeColor( const SDL_Color& color ) noexcept { mShapeColor = color; }

		/**
		 * @brief Get the shape position
		 */
		glm::vec2 GetPosition() const noexcept { return mShapePosition; }
		
		/**
		 * @brief Set the shape position
		 */
		void SetPosition( const glm::vec2& position ) noexcept { mShapePosition = position; }

		/**
		 * @brief Get the shape rotation
		 */
		float GetRotation() const noexcept { return mShapeRotation; }
		
		/**
		 * @brief Set the shape rotation
		 */
		void SetRotation( float rotation ) noexcept { mShapeRotation = rotation; }


		/**
		 * @brief ToString returns a string representation of the shape type
		 */
		std::string toString() const noexcept
		{
			switch ( mShapeType )
			{
				case ShapeType::RECTANGLE: return "Rectangle-Shape";
				case ShapeType::CIRCLE: return "Circle-Shape";
				case ShapeType::TRIANGLE: return "Triangle-Shape";
				default: return "Unknown Shape";
			}
		}

		/**
		* @brief Checks if the shapes are equal by comparing the shape type,
		* area, and perimeter with a tolerance for floating-point comparisons.
		*/
		virtual bool Equals( const IShape& other ) const noexcept
		{
			return ( mShapeType == other.mShapeType ) &&
				( Math::NearlyEqual( Area(), other.Area() ) ) &&
				( Math::NearlyEqual( Perimeter(), other.Perimeter() ) );
		}

		

	protected:
		IShape( ShapeType type, const glm::vec2& position, const SDL_Color& color, float rotation )
			: mShapeType( type ), mShapePosition( position ), mShapeColor( color ), mShapeRotation( rotation ) {}
		
		
		ShapeType mShapeType;
		glm::vec2 mShapePosition;
		SDL_Color mShapeColor;
		float mShapeRotation;

		const float DEFAULT_ROTATION = 0.f;
		const SDL_Color DEFAULT_COLOR = COLOR_ORANGE;

	};

}
