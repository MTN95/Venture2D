#include "TransformComponent.hpp"


namespace venture
{
	TransformComponent::TransformComponent()
		: mPosition(glm::vec2(0.0f)), mRotation(0.0f), mScale(glm::vec2(1.0f)) 
	{
		SetComponentName("TransformComponent");
	}

	TransformComponent::TransformComponent( const TransformComponent& other )
		: mPosition(other.mPosition), mRotation(other.mRotation), mScale(other.mScale) 
	{
		SetComponentName("TransformComponent");
	}
	
	TransformComponent::TransformComponent( TransformComponent&& other ) noexcept
		: mPosition(other.mPosition), mRotation(other.mRotation), mScale(other.mScale)
	{
		SetComponentName("TransformComponent");
		other.ResetPosition();		
		other.ResetRotation();		
		other.ResetScale();		
	}

	TransformComponent::TransformComponent(glm::vec2 position)
		: mPosition(position), mRotation(0.0f), mScale(glm::vec2(1.0f))
	{
		SetComponentName("TransformComponent");
	}
	
	TransformComponent::TransformComponent(glm::vec2 position, float rotation)
		: mPosition(position), mRotation(rotation), mScale(glm::vec2(1.0f))
	{
		SetComponentName("TransformComponent");
	}

	TransformComponent::TransformComponent(glm::vec2 position, float rotation, glm::vec2 scale)
		: mPosition(position), mRotation(rotation), mScale(scale)
	{
		SetComponentName("TransformComponent");
	}

	TransformComponent::~TransformComponent()
	{}

	TransformComponent& TransformComponent::operator=( const TransformComponent& other )
	{
		if ( this != &other )
		{
			mPosition = other.mPosition;
			mRotation = other.mRotation;
			mScale = other.mScale;
		}
		return *this;
	}

	TransformComponent& TransformComponent::operator=( TransformComponent&& other ) noexcept
	{
		if ( this != &other )
		{
			mPosition = other.mPosition ;
			mRotation = other.mRotation ;
			mScale = other.mScale ;

			other.ResetPosition();
			other.ResetRotation();
			other.ResetScale();
		}
		return *this;
	}

	void TransformComponent::Update(float deltaTime)
	{
		
	}

}