#include "EntityManager.h"

EntityManager::EntityManager()
{
	m_ent_num = 0;
}

std::shared_ptr<Entity> EntityManager::addEntity(const TAG& tag)
{
	auto& e = std::make_shared<Entity>( m_ent_num, tag );

	m_entmap[tag].push_back(e);
	m_entvec.push_back(e);
	m_ent_num++;

	return e;
}

entitiesVec& EntityManager::getAllByTag(const TAG& tag)
{
	return m_entmap[tag];
}
