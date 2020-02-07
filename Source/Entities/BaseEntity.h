#pragma once

#include "EntityLump.h"
#include "Vector.h"
#include "Matrix4x4.h"
#include "Quaternion.h"
#include "Shader.h"
#include <iostream>

namespace Freeking
{
	class BaseEntity
	{
	public:

		using SharedPtr = std::shared_ptr<BaseEntity>;

		BaseEntity();
		virtual ~BaseEntity() = default;

		virtual void InitializeProperties(const EntityProperties& properties);
		virtual void Initialize();
		virtual void PostInitialize();
		virtual void Tick(double dt);
		virtual void PostTick();
		virtual void Spawn();

		void Trigger();

		static SharedPtr Make(const std::string_view& classname);

	protected:

		virtual void OnTrigger();

		virtual bool SetProperty(const EntityProperty& property);

		std::string _name;
		std::string _classname;
		std::string _targetname;
		std::string _target;

		double _timeSpawned;
	};
}
