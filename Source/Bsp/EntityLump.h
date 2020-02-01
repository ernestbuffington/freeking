#pragma once

#include "Vector.h"
#include <string>
#include <vector>
#include <unordered_map>

namespace Freeking
{
	class EntityProperty
	{
	public:

		EntityProperty() = delete;
		EntityProperty(const std::string& key, const std::string& value) :
			_key(key), _value(value)
		{
		}

		inline bool IsKey(const std::string& key) const { return _key == key; }
		inline const std::string Key() const { return _key; }
		inline const std::string Value() const { return _value; }

		bool ValueAsVector(Vector3f& v) const;
		bool ValueAsFloat(float& v) const;
		bool ValueAsInt(int& v) const;
		bool ValueAsModelIndex(int& v) const;

	private:

		std::string _key;
		std::string _value;
	};

	class EntityProperties
	{
	public:

		template <typename T>
		class CommonValue
		{
		public:

			operator const T&() const { return value; }
			const T& operator*() const { return value; }
			explicit operator bool() const { return !unset; }

		private:

			CommonValue() : value(), unset(true) {}
			CommonValue(const T& v) : value(v), unset(false) {}

			T value;
			bool unset;

			friend class EntityProperties;
		};

		EntityProperties() = default;
		EntityProperties(EntityProperties&&) = default;
		EntityProperties(const EntityProperties&) = delete;
		EntityProperties& operator=(const EntityProperties&) = delete;

		void AddKeyValue(const std::string& key, const std::string& value);
		void FindCommonValues();

		using CommonString = CommonValue<std::string>;
		using CommonVector = CommonValue<Vector3f>;
		using CommonScalar = CommonValue<float>;
		using CommonInt = CommonValue<int>;

		inline const std::vector<EntityProperty>& GetKeyValues() const { return _keyValues; }

		const CommonString& GetClassnameProperty() const { return _classname; }
		const CommonString& GetNameProperty() const { return _name; }
		const CommonString& GetTargetnameProperty() const { return _targetname; }
		const CommonString& GetTargetProperty() const { return _target; }
		const CommonVector& GetOriginProperty() const { return _origin; }
		const CommonScalar& GetAngleProperty() const { return _angle; }

		bool TryGetSplitString(const std::string& key, std::vector<std::string>& value) const;

	private:

		bool TryGetString(const std::string& key, std::string& value) const;
		bool TryGetInt(const std::string& key, int& value) const;
		bool TryGetFloat(const std::string& key, float& value) const;
		bool TryGetVector(const std::string& key, Vector3f& value) const;

		bool TryGetString(const std::string& key, CommonString& value) const;
		bool TryGetVector(const std::string& key, CommonVector& value) const;
		bool TryGetFloat(const std::string& key, CommonScalar& value) const;
		bool TryGetInt(const std::string& key, CommonInt& value) const;

		std::unordered_map<std::string, std::string> _keyToValues;
		std::vector<EntityProperty> _keyValues;

		CommonString _classname;
		CommonString _name;
		CommonString _targetname;
		CommonString _target;
		CommonVector _origin;
		CommonScalar _angle;
	};

	class EntityLump
	{
	public:

		EntityLump() = delete;
		~EntityLump() = delete;

		static bool Parse(const std::string& string, std::vector<EntityProperties>& items);

	private:

		static bool TryParseKeyValues(const std::string& string, size_t& pos, EntityProperties& properties);
		static std::string ParseSubString(const std::string& string, size_t& pos);
	};
}
