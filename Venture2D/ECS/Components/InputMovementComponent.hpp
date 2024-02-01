#pragma once

#include "../IComponent.hpp"
#include "../../Util/Log.hpp"

namespace venture 
{
	// Currently Supports only Keyboard input
	class InputMovementComponent : public IComponent
	{
	public:
		InputMovementComponent(int moveSpeed = 0);
		InputMovementComponent(const InputMovementComponent& other);
		~InputMovementComponent() override;
		
		void Update(float deltaTime) override;
	
		void ProcessKeyboardInput(float deltaTime);
		
		const int GetMovementSpeed() const { return mMovementSpeed; }

		inline int SetMovementSpeed(int newSpeed) { mMovementSpeed = newSpeed; }

		std::unique_ptr<IComponent, IComponentDeleter> Clone() const override
		{
			return std::unique_ptr<IComponent, IComponentDeleter>( new InputMovementComponent( *this ) );
		}


	private:
		int mMovementSpeed;
	};

}