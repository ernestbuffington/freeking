#include "EntityLump.h"
#include <charconv>

namespace Freeking
{
	bool EntityKeyValue::ValueAsVector(Vector3f& v) const
	{
		return EntityLump::TryParseVector(Value, v);
	}

	bool EntityKeyValue::ValueAsFloat(float& v) const
	{
		return EntityLump::TryParseFloat(Value, v);
	}

	bool EntityKeyValue::ValueAsInt(int& v) const
	{
		return EntityLump::TryParseInt(Value, v);
	}

	EntityLump::EntityLump(const std::string& string)
	{
		size_t pos = 0;
		while (pos < string.size())
		{
			EntityDef entityDef;
			if (!TryParseEntityDef(string, pos, entityDef))
			{
				break;
			}

			if (entityDef.TryGetString("classname", entityDef.classname))
			{
				entityDef.TryGetString("targetname", entityDef.targetname);
				entityDef.TryGetString("target", entityDef.target);
				entityDef.TryGetFloat("angle", entityDef.angle);
				entityDef.logic = !entityDef.TryGetVector("origin", entityDef.origin);

				Entities.push_back(entityDef);
			}
		}
	}

	bool EntityLump::EntityDef::TryGetString(const std::string& key, std::string& value) const
	{
		auto it = keyValues.find(key);
		if (it == keyValues.end())
		{
			return false;
		}

		value = it->second;

		return true;
	}

	bool EntityLump::EntityDef::TryGetSplitString(const std::string& key, std::vector<std::string>& value) const
	{
		auto it = keyValues.find(key);
		if (it == keyValues.end())
		{
			return false;
		}

		value = SplitString(it->second, " ");

		return true;
	}

	bool EntityLump::EntityDef::TryGetInt(const std::string& key, int& value) const
	{
		std::string s;
		if (!TryGetString(key, s))
		{
			return false;
		}

		return TryParseInt(s, value);
	}

	bool EntityLump::EntityDef::TryGetFloat(const std::string& key, float& value) const
	{
		std::string s;
		if (!TryGetString(key, s))
		{
			return false;
		}

		return TryParseFloat(s, value);
	}

	bool EntityLump::EntityDef::TryGetVector(const std::string& key, Vector3f& value) const
	{
		std::string s;
		if (!TryGetString(key, s))
		{
			return false;
		}

		return TryParseVector(s, value);
	}

	bool EntityLump::TryParseVector(const std::string& s, Vector3f& v)
	{
		auto xyz = SplitString(s, " ");
		if (xyz.size() != 3)
		{
			return false;
		}

		float x, y, z;
		if (!TryParseFloat(xyz[0], x) ||
			!TryParseFloat(xyz[1], y) ||
			!TryParseFloat(xyz[2], z))
		{
			return false;
		}

		v = Vector3f(x, y, z);

		return true;
	}

	bool EntityLump::TryParseFloat(const std::string& s, float& v)
	{
		return std::from_chars(s.data(), s.data() + s.size(), v, std::chars_format::general).ec == std::errc();
	}

	bool EntityLump::TryParseInt(const std::string& s, int& v)
	{
		return std::from_chars(s.data(), s.data() + s.size(), v).ec == std::errc();
	}

	std::vector<std::string> EntityLump::SplitString(const std::string& s, const std::string& delimiter)
	{
		std::vector<std::string> result;
		size_t start = 0;
		size_t end = 0;

		do
		{
			end = s.find(delimiter, start);
			size_t length = end - start;
			std::string token = s.substr(start, length);

			if (length > 0)
			{
				result.emplace_back(token);
			}

			start += length + delimiter.length();
		} 
		while (end != std::string::npos);

		return result;
	}

	bool EntityLump::TryParseEntityDef(const std::string& string, size_t& pos, EntityDef& entityDef)
	{
		bool begin = false;

		while (pos < string.size())
		{
			const char& c = string[pos];

			if (c == ' ' ||
				c == '\t' ||
				c == '\n' ||
				c == '\r')
			{
				pos++;

				continue;
			}
			else if (c == '{')
			{
				if (begin)
				{
					return false;
				}

				begin = true;
				pos++;

				continue;
			}
			else if (c == '}')
			{
				pos++;

				break;
			}
			else if (begin && c == '"')
			{
				std::string key = ParseSubString(string, pos);
				std::string value = ParseSubString(string, pos);
				entityDef.keyValues.emplace(key, value);

				continue;
			}
			else if (c != 0)
			{
				return false;
			}

			pos++;
		}

		return true;
	}

	std::string EntityLump::ParseSubString(const std::string& string, size_t& pos)
	{
		bool begin = false;
		std::string subString = "";

		while (pos < string.size())
		{
			const char& c = string[pos++];

			if (c == '"')
			{
				if (!begin)
				{
					begin = true;

					continue;
				}

				break;
			}
			else if (begin)
			{
				subString += c;
			}
		}

		return subString;
	}
}
