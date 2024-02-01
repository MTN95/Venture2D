#include "ShapeComponent.hpp"
#include "../../Util/Common.hpp"
#include "../../Game.hpp"
#include "../Entity.hpp"

namespace venture
{

	ShapeComponent::ShapeComponent( IShape* shape )
		: mShape(shape)

	{
		SetComponentName( "ShapeComponent" );
	}

	ShapeComponent::ShapeComponent( const ShapeComponent& other )
		: mShape( other.mShape->Clone() )
	{
		SetComponentName( "ShapeComponent" );
	}

	ShapeComponent::ShapeComponent( ShapeComponent&& other ) noexcept
		: IComponent( other )
		, mShape( other.mShape )
	{
		SetComponentName( "ShapeComponent" );
		other.mShape = nullptr;
	}

	ShapeComponent& ShapeComponent::operator=( const ShapeComponent& other )
	{
		if ( this != &other )
		{
			IComponent::operator=( other ); // Call the base class copy assignment

		}
		return *this;
	}

	ShapeComponent& ShapeComponent::operator=( ShapeComponent&& other ) noexcept
	{
		if ( this != &other )
		{
			IComponent::operator=( other ); // Call the base class move assignment

		}
		return *this;
	}

	ShapeComponent::~ShapeComponent()
	{ 
		delete mShape; 
	}

	void ShapeComponent::Update( float deltaTime )
	{
		if ( mEntityOwner != nullptr )
		{
			// update the shapes position to the entity's position
			mShape->SetPosition(mEntityOwner->GetPosition());
		}
	}

	void ShapeComponent::Render( SDL_Renderer* renderer )
	{
		// Set the color for drawing the shape
		SDL_SetRenderDrawColor( renderer, 
								mShape->GetShapeColor().r, 
								mShape->GetShapeColor().g, 
								mShape->GetShapeColor().b, 
								mShape->GetShapeColor().a );

		auto xPos = mShape->GetPosition().x;
		auto yPos = mShape->GetPosition().y;
		auto boundingBox= mShape->GetBoundingBox();

		// Draw the shape based on its type
		switch ( mShape->GetShapeType() )
		{
			case ShapeType::RECTANGLE:  // Use boundingBox.x and boundingBox.y as width and height
			{
				SDL_FRect rect = { xPos, yPos, boundingBox.x,boundingBox.y};
				SDL_RenderFillRectF( renderer, &rect );  // Or SDL_RenderDrawRectF if you want an outline
				break;
			}
			case ShapeType::CIRCLE: // Use boundingBox.x / 2 as the radius (assuming x and y are equal)
				// Draw circle logic
				break;
			case ShapeType::TRIANGLE:
				// Draw triangle logic
				break;
			default:
				break;
		}

	}

}
