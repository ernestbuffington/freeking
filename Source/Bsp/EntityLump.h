#pragma once

#include "Vector.h"
#include <string>
#include <vector>
#include <map>

namespace Freeking
{
	struct EntityKeyValue
	{
		std::string Key;
		std::string Value;

		bool ValueAsVector(Vector3f& v) const;
		bool ValueAsFloat(float& v) const;
		bool ValueAsInt(int& v) const;
	};

	class EntityLump
	{
	public:

		EntityLump() = default;

		bool Parse(const std::string& string);

		class EntityDef
		{
		public:

			bool TryGetString(const std::string& key, std::string& value) const;
			bool TryGetSplitString(const std::string& key, std::vector<std::string>& value) const;
			bool TryGetInt(const std::string& key, int& value) const;
			bool TryGetFloat(const std::string& key, float& value) const;
			bool TryGetVector(const std::string& key, Vector3f& value) const;

			std::map<std::string, std::string> keyValues;

			std::string classname;
			std::string targetname;
			std::string target;
			Vector3f origin;
			float angle;
			bool logic;
		};

		std::vector<EntityDef> Entities;

	private:

		static bool TryParseEntityDef(const std::string& string, size_t& pos, EntityDef& entityDef);
		static bool TryParseVector(const std::string& s, Vector3f& v);

		static std::vector<std::string> SplitString(const std::string& s, const std::string& delimiter);
		static std::string ParseSubString(const std::string& string, size_t& pos);

		friend struct EntityKeyValue;
	};
}
