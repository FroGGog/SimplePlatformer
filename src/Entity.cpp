#include "Entity.h"

void Entity::destroy()
{
	is_active = false;
}

size_t Entity::id() const
{
	return m_id;
}

bool Entity::isActive() const
{
	return is_active;
}

const TAG& Entity::tag() const
{
	return m_tag;
}
