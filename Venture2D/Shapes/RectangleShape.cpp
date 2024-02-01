#include "RectangleShape.hpp"

namespace venture
{
	RectangleShape::RectangleShape( RectConfig rectangleConfig )
		: IShape( ShapeType::RECTANGLE,
				  rectangleConfig.m_position,
				  rectangleConfig.m_color,
				  rectangleConfig.m_rotation )
		, mWidth( rectangleConfig.m_width )
		, mHeight( rectangleConfig.m_height )
	{}

	RectangleShape::RectangleShape( float length, float width, const glm::vec2& position )
		: IShape( ShapeType::RECTANGLE, position, DEFAULT_COLOR, DEFAULT_ROTATION )
		, mWidth( length )
		, mHeight( width )
	{}

	RectangleShape::RectangleShape( const glm::vec2& position )
		: IShape( ShapeType::RECTANGLE, position, DEFAULT_COLOR, DEFAULT_ROTATION )
	{
		mWidth = DEFAULT_LENGTH;
		mHeight = DEFAULT_WIDTH;
	}


	RectangleShape::RectangleShape( const RectangleShape& other )
		: IShape( ShapeType::RECTANGLE,
				  other.mShapePosition,
				  other.mShapeColor,
				  other.mShapeRotation )
		, mWidth( other.mWidth )
		, mHeight( other.mHeight )
	{}

	RectangleShape::RectangleShape( RectangleShape&& other ) noexcept
		: IShape( ShapeType::RECTANGLE,
				  other.mShapePosition,
				  other.mShapeColor,
				  other.mShapeRotation )
		, mWidth( other.mWidth )
		, mHeight( other.mHeight )
	{}

	RectangleShape& RectangleShape::operator=( const RectangleShape& other )
	{
		if ( this != &other )
		{
			mShapePosition = other.mShapePosition;
			mShapeColor = other.mShapeColor;
			mShapeRotation = other.mShapeRotation;
			mWidth = other.mWidth;
			mHeight = other.mHeight;
		}
		return *this;
	}

	RectangleShape& RectangleShape::operator=( RectangleShape&& other ) noexcept
	{
		if ( this != &other )
		{
			mShapePosition = other.mShapePosition;
			mShapeColor = other.mShapeColor;
			mShapeRotation = other.mShapeRotation;
			mWidth = other.mWidth;
			mHeight = other.mHeight;
		}
		return *this;
	}

	RectangleShape::~RectangleShape()
	{

	}

	void venture::RectangleShape::Scale( float scaleFactor ) noexcept
	{
		mWidth *= scaleFactor;
		mHeight *= scaleFactor;
	}

}