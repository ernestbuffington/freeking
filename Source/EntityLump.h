#pragma once

#include "Vector.h"
#include <string>
#include <vector>
#include <map>

namespace Freeking
{
	class EntityLump
	{
	public:

		EntityLump(const std::string& string);

		class EntityDef
		{
		public:

			bool TryGetString(const std::string& key, std::string& value);
			bool TryGetFloat(const std::string& key, float& value);
			bool TryGetVector(const std::string& key, Vector3f& value);

			std::map<std::string, std::string> keyValues;

			std::string classname;
			std::string targetname;
			std::string target;
			Vector3f origin;
			bool logic;
		};

		std::vector<EntityDef> Entities;

	private:

		static bool TryParseEntityDef(const std::string& string, size_t& pos, EntityDef& entityDef);
		static bool TryParseVector(const std::string& s, Vector3f& v);
		static bool TryParseFloat(const std::string& s, float& v);

		static std::vector<std::string> SplitString(const std::string& s, const std::string& delimiter);
		static std::string ParseSubString(const std::string& string, size_t& pos);
	};
}
