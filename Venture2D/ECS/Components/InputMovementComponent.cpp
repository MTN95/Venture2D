#include "InputMovementComponent.hpp"
#include "TransformComponent.hpp"
#include "../../Input/InputManager.hpp"

namespace venture
{

	InputMovementComponent::InputMovementComponent( int moveSpeed )
		: mMovementSpeed( moveSpeed )
	{

	}

	InputMovementComponent::InputMovementComponent( const InputMovementComponent& other )
		: mMovementSpeed(other.mMovementSpeed)
	{}

	InputMovementComponent::~InputMovementComponent()
	{

	}

	void InputMovementComponent::Update( float deltaTime )
	{
		ProcessKeyboardInput( deltaTime );
	}

	void InputMovementComponent::ProcessKeyboardInput( float deltaTime )
	{
		//auto ownerTransform = mEntityOwner->GetComponent<TransformComponent>();


	}
}