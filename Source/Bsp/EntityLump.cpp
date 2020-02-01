#include "EntityLump.h"
#include "Util.h"

namespace Freeking
{
	bool EntityProperty::ValueAsVector(Vector3f& v) const
	{
		return Util::TryParseVector(_value, v);
	}

	bool EntityProperty::ValueAsFloat(float& v) const
	{
		return Util::TryParseFloat(_value, v);
	}

	bool EntityProperty::ValueAsInt(int& v) const
	{
		return Util::TryParseInt(_value, v);
	}

	bool EntityProperty::ValueAsModelIndex(int& v) const
	{
		if (!_value.empty() && _value[0] == '*')
		{
			if (Util::TryParseInt(_value.substr(1), v))
			{
				return true;
			}
		}

		v = -1;

		return false;
	}

	bool EntityProperties::TryGetString(const std::string& key, CommonString& value) const
	{
		if (TryGetString(key, value.value))
		{
			value.unset = false;
			return true;
		}

		return false;
	}

	bool EntityProperties::TryGetVector(const std::string& key, CommonVector& value) const
	{
		if (TryGetVector(key, value.value))
		{
			value.unset = false;
			return true;
		}

		return false;
	}

	bool EntityProperties::TryGetFloat(const std::string& key, CommonScalar& value) const
	{
		if (TryGetFloat(key, value.value))
		{
			value.unset = false;
			return true;
		}

		return false;
	}

	bool EntityProperties::TryGetInt(const std::string& key, CommonInt& value) const
	{
		if (TryGetInt(key, value.value))
		{
			value.unset = false;
			return true;
		}

		return false;
	}

	bool EntityProperties::TryGetString(const std::string& key, std::string& value) const
	{
		auto it = _keyToValues.find(key);
		if (it == _keyToValues.end())
		{
			return false;
		}

		value = it->second;

		return true;
	}

	bool EntityProperties::TryGetSplitString(const std::string& key, std::vector<std::string>& value) const
	{
		auto it = _keyToValues.find(key);
		if (it == _keyToValues.end())
		{
			return false;
		}

		value = Util::SplitString(it->second, " ");

		return true;
	}

	bool EntityProperties::TryGetInt(const std::string& key, int& value) const
	{
		std::string s;
		if (!TryGetString(key, s))
		{
			return false;
		}

		return Util::TryParseInt(s, value);
	}

	bool EntityProperties::TryGetFloat(const std::string& key, float& value) const
	{
		std::string s;
		if (!TryGetString(key, s))
		{
			return false;
		}

		return Util::TryParseFloat(s, value);
	}

	bool EntityProperties::TryGetVector(const std::string& key, Vector3f& value) const
	{
		std::string s;
		if (!TryGetString(key, s))
		{
			return false;
		}

		return Util::TryParseVector(s, value);
	}

	void EntityProperties::AddKeyValue(const std::string& key, const std::string& value)
	{
		_keyValues.emplace_back(key, value);
		_keyToValues.emplace(key, value);
	}

	void EntityProperties::FindCommonValues()
	{
		if (TryGetString("classname", _classname))
		{
			TryGetString("name", _name);
			TryGetString("targetname", _targetname);
			TryGetString("target", _target);
			TryGetVector("origin", _origin);
			TryGetFloat("angle", _angle);
		}
	}

	bool EntityLump::Parse(const std::string& string, std::vector<EntityProperties>& items)
	{
		std::vector<EntityProperties> entityKeyValues;

		size_t pos = 0;
		while (pos < string.size())
		{
			EntityProperties keyValues;
			if (!TryParseKeyValues(string, pos, keyValues))
			{
				return false;
			}

			keyValues.FindCommonValues();

			if (keyValues.GetClassnameProperty())
			{
				items.push_back(std::move(keyValues));
			}
		}

		return true;
	}

	bool EntityLump::TryParseKeyValues(const std::string& string, size_t& pos, EntityProperties& properties)
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
				properties.AddKeyValue(key, value);

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
