#pragma once

#include <unordered_map>
#include <algorithm>

#include "Entity.hpp"


namespace venture
{

	// (optional) make entity manager manage and update all of the game entities


	class EntityManager
	{
	private:
		std::unordered_map<std::size_t, Entity*> mIndexToEntitiesMap;
	public:
		static EntityManager* get()
		{
			if (s_Instance == nullptr)
			{
				s_Instance = new EntityManager();
			}
			return s_Instance;
		}

		Entity* createEntity(const std::string_view& entityName);
		void destroyEntity(Entity* entity);
		//void updateEntities(float deltaTime);

	private:
		static EntityManager* s_Instance;
		EntityManager();
		~EntityManager();
	};

}