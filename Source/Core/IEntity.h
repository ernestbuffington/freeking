#pragma once

#include "EntityLump.h"
#include "Vector.h"
#include "Matrix4x4.h"
#include "Quaternion.h"
#include "Material.h"
#include <iostream>

namespace Freeking
{
	typedef std::shared_ptr<class IEntity> shared_ptr_entity;
	typedef std::shared_ptr<class IEntityComponent> shared_ptr_component;

	class IEntity
	{
	public:

		IEntity() = default;
		virtual ~IEntity() = default;

		virtual void InitializeProperties(const EntityLump::EntityDef& def);
		virtual void Initialize();
		virtual void PostInitialize();
		virtual void Tick(double dt);
		virtual void PostTick();
		virtual void Spawn();

		static shared_ptr_entity Make(const std::string_view& classname);

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) = 0;

		template <typename T>
		T* CreateComponent()
		{
			static_assert(std::is_base_of<IEntityComponent, T>::value, "CreateComponent type parameter must derive from IEntityComponent");

			auto component = std::make_shared<T>();
			_components.push_back(std::static_pointer_cast<IEntityComponent>(component));

			return component.get();
		}

		std::string _name;
		std::vector<shared_ptr_component> _components;
	};
}
