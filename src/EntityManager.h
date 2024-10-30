#pragma once
#include <vector>
#include <map>

#include "Entity.h"

typedef std::vector<std::shared_ptr<Entity>> entitiesVec;
typedef std::map<TAG, entitiesVec> entitiesMap;


class EntityManager {

private:

	size_t m_ent_num;
	entitiesMap m_entmap;
	entitiesVec m_entvec;


public:

	EntityManager();

	std::shared_ptr<Entity> addEntity(const TAG& tag);
	entitiesVec& getAllByTag(const TAG& tag);


};