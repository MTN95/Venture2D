#include "EntityManager.hpp"
#include "../Util/Log.hpp"


namespace venture
{

	EntityManager* EntityManager::s_Instance = nullptr;

	EntityManager::EntityManager()
	{

	}

	EntityManager::~EntityManager()
	{
		for ( auto& entity : mIndexToEntitiesMap )
		{
			delete entity.second;
		}
	}

	Entity* EntityManager::createEntity(const std::string_view& entityName)
	{
		Entity* entity = new Entity(entityName);
		mIndexToEntitiesMap.insert( { entity->GetID(),entity } );
		LOG_DEBUG( "New Entity Created! (ID:{0},Name:{1}): ", entity->GetID(), entity->GetName() );
		return entity;
	}

	void EntityManager::destroyEntity( Entity* entity )
	{
		auto it = mIndexToEntitiesMap.find( entity->GetID() );
		if ( it != mIndexToEntitiesMap.end() )
		{
			mIndexToEntitiesMap.erase( it );
			LOG_DEBUG( "Entity Destroyed! (ID:{0},Name:{1}): ", entity->GetID(), entity->GetName() );
			delete entity;
		}
	}

	// void EntityManager::updateEntities(float deltaTime)
	// {
	// 	for (auto& entity : mIndexToEntitiesMap) 
	// 	{
	// 		//std::cout << "EntityManager Updating Entities..\n";
	// 		entity.second->updateComponents(deltaTime);
	// 	}
	// }
}