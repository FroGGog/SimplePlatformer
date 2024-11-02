#include <tuple>

#include "Components.h"

typedef std::tuple<CBoundingBox, CText> ComponentsTuple;

enum class TAG {DEFAULT, BACK_TILE, TILE, TEXT};

class Entity {

private:

	bool is_active = true;

	TAG m_tag = TAG::DEFAULT;

	size_t m_id = 0;

	ComponentsTuple m_components;

public:

	Entity(const size_t id, const TAG tag) :m_id(id), m_tag(tag) {};

	void destroy();
	size_t id() const;
	bool isActive() const;
	const TAG& tag() const;

	template<typename T>
	bool hasComponets() const
	{
		return getComponent<T>().has;
	}

	template<typename T>
	T& getComponent()
	{
		return std::get<T>(m_components);
	}

	template<typename T>
	const T& getComponent() const
	{
		return std::get<T>(m_components);
	}

	template<typename T, typename ... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		auto& component = getComponent<T>();
		component = T(std::forward<TArgs>(mArgs)...);
		component.has = true;
		return component;

	}


};