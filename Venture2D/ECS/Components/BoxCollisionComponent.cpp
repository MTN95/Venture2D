#include "BoxCollisionComponent.hpp"
#include "../Entity.hpp"

namespace venture
{

	BoxCollisionComponent::BoxCollisionComponent( const SDL_FRect& rect )
		: mBoxCollision( rect )
	{
		SetComponentName( "BoxCollisionComponent" );
	}

	BoxCollisionComponent::BoxCollisionComponent( const BoxCollisionComponent& other )
		: mBoxCollision( other.mBoxCollision )
	{
		SetComponentName( "BoxCollisionComponent" );
	}

	BoxCollisionComponent::BoxCollisionComponent( BoxCollisionComponent&& other ) noexcept
		: IComponent( other ), mBoxCollision( other.mBoxCollision )
	{
		SetComponentName( "BoxCollisionComponent" );
		// reset the other's state if needed
	}

	BoxCollisionComponent& BoxCollisionComponent::operator=( const BoxCollisionComponent& other )
	{
		if ( this != &other )
		{
			IComponent::operator=( other ); // Call the base class copy assignment
			mBoxCollision = other.mBoxCollision;
		}
		return *this;
	}

	BoxCollisionComponent& BoxCollisionComponent::operator=( BoxCollisionComponent&& other ) noexcept
	{
		if ( this != &other )
		{
			IComponent::operator=( other ); // Call the base class move assignment
			mBoxCollision = other.mBoxCollision;
			// reset the other's state if needed
		}
		return *this;
	}

	BoxCollisionComponent::~BoxCollisionComponent()
	{}

	bool BoxCollisionComponent::IsColliding( const BoxCollisionComponent& other )
	{
		const auto& rectB = other.GetBoxCollision();

		//The sides of the rectangles
		float leftA, leftB;
		float rightA, rightB;
		float topA, topB;
		float bottomA, bottomB;

		//Calculate the sides of rect A
		leftA = mBoxCollision.x;
		rightA = mBoxCollision.x + mBoxCollision.w;
		topA = mBoxCollision.y;
		bottomA = mBoxCollision.y + mBoxCollision.h;

		//Calculate the sides of rect B
		leftB = rectB.x;
		rightB = rectB.x + rectB.w;
		topB = rectB.y;
		bottomB = rectB.y + rectB.h;

		//If any of the sides from A are outside of B
		if ( bottomA <= topB )
		{
			return false;
		}

		if ( topA >= bottomB )
		{
			return false;
		}

		if ( rightA <= leftB )
		{
			return false;
		}

		if ( leftA >= rightB )
		{
			return false;
		}

		//If none of the sides from A are outside B
		return true;
	}

	void BoxCollisionComponent::Update( float deltaTime )
	{
		if ( mEntityOwner != nullptr )
		{
			mBoxCollision.x = mEntityOwner->GetPosition().x;
			mBoxCollision.y = mEntityOwner->GetPosition().y;
		}
	}

}
