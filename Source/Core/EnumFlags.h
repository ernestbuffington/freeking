#pragma once

#include <type_traits>

template<typename T>
class EnumFlags
{
	static_assert(std::is_enum<T>::value, "EnumFlags only accepts enums");
public:

	using UnderlyingType = std::underlying_type_t<T>;

	EnumFlags() = default;
	explicit EnumFlags(const T& v) : _value(static_cast<UnderlyingType>(v)) {}
	explicit EnumFlags(const UnderlyingType& v) : _value(v) {}

	EnumFlags& operator=(const T& v) { return _value = static_cast<UnderlyingType>(v); return *this; }
	EnumFlags& operator=(const UnderlyingType& v) { _value = v; return *this; }

	constexpr bool operator&(const T& v) { return _value & static_cast<UnderlyingType>(v); }
	constexpr bool operator[](const T& v) const { return _value & static_cast<UnderlyingType>(v); }
	constexpr bool operator[](const EnumFlags& v) const { return _value & v._value; }

private:

	UnderlyingType _value;
};
