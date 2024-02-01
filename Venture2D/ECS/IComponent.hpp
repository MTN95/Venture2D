#pragma once
#include <memory>
#include <string_view>
//#include "Entity.hpp"

namespace venture
{
	struct IComponentDeleter;
	class Entity;

	class IComponent
	{
	public:
		IComponent() = default;
		virtual ~IComponent() = default;

		virtual void Update(float deltaTime) = 0;
		virtual std::unique_ptr<IComponent,IComponentDeleter> Clone() const = 0;
		void SetComponentName(std::string_view newName){mEntityName = newName;}

		Entity* mEntityOwner = nullptr;
		std::string_view mEntityName = "defaultComponentName";
	};

	struct IComponentDeleter
	{
		void operator()( IComponent* c ) const
		{
			delete c;
		}
	};

}