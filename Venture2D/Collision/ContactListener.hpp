#pragma once
#include <iostream>
#include <box2d/box2d.h>
#include "../ECS/Components/BoxCollisionComponent.hpp"

namespace venture
{
	// Define a custom class to handle collision events
	class ContactListener : public b2ContactListener
	{
	public:
		static ContactListener* get()
		{
			if ( s_Instance == nullptr )
			{
				s_Instance = new ContactListener();
			}
			return s_Instance;
		}

		void BeginContact( b2Contact* contact )
		{
			// Handle collision beginning
			b2Fixture* fixtureA = contact->GetFixtureA();
			b2Fixture* fixtureB = contact->GetFixtureB();

			// You can access user data or other fixture properties here
			// For example:
			// MyGameObject* objectA = static_cast<MyGameObject*>(fixtureA->GetUserData());
			// MyGameObject* objectB = static_cast<MyGameObject*>(fixtureB->GetUserData());

			// Implement your collision response logic here
			std::cout << "Collision began!" << std::endl;
		}

		void EndContact( b2Contact* contact )
		{
			// Handle collision ending
			// Implement your collision response logic here
			std::cout << "Collision ended!" << std::endl;
		}

	private:
		static ContactListener* s_Instance;
	};

	ContactListener* ContactListener::s_Instance = nullptr;
}
