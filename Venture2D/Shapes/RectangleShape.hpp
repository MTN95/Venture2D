#pragma once
#include "IShape.hpp"
#include <Box2d/b2_polygon_shape.h>
#include "../Util/ColorMacros.hpp"

namespace venture
{
	struct RectConfig
	{
		RectConfig( float width, float height, const glm::vec2& position, const SDL_Color& color, float rotation )
			: m_width( width ), m_height( height ), m_position(position), m_color(color), m_rotation(rotation)
		{}

		float m_width;
		float m_height;
		const glm::vec2& m_position; 
		const SDL_Color& m_color;
		float m_rotation;
	};

	class RectangleShape : public IShape
	{

	public:

		RectangleShape( RectConfig rectangleConfig );
		RectangleShape( float length, float width, const glm::vec2& position );
		RectangleShape( const glm::vec2& position );

		RectangleShape(const RectangleShape& other);
		RectangleShape(RectangleShape&& other) noexcept;
		
		RectangleShape& operator=(const RectangleShape& other);
		RectangleShape& operator=(RectangleShape&& other) noexcept;

		~RectangleShape() override;

		double Area() const noexcept override { return mWidth * mHeight; }
		double Perimeter() const noexcept override { return ( ( mWidth + mHeight ) * 2 ); }
		void Scale( float scaleFactor ) noexcept override;

		glm::vec2 GetBoundingBox() const noexcept override { return { mWidth, mHeight }; }

		IShape* Clone() const override
		{
			return new RectangleShape( *this );
		}

		//void UpdateBox2DShape()
		//{
			// Update the Box2D shape to match the current size of the rectangle
			//mBox2DShape.SetAsBox( mWidth / 2.0f, mHeight / 2.0f );
		//}

		//const b2Shape& GetBox2DShape() const override { return mBox2DShape; }

	private:

		//b2PolygonShape mBox2DShape;

		float mWidth;
		float mHeight;
		
		const float DEFAULT_LENGTH = 50.0;
		const float DEFAULT_WIDTH = 50.0;
	};

}
