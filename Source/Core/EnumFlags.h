#pragma once

#include <type_traits>

template<typename T>
class EnumFlags
{
	static_assert(std::is_enum<T>::value, "EnumFlags only accepts enums");
public:

	using UnderlyingType = std::underlying_type_t<T>;

	EnumFlags() = default;
	EnumFlags(const T& v) : _value(static_cast<UnderlyingType>(v)) {}
	EnumFlags(const UnderlyingType& v) : _value(v) {}

	EnumFlags<T>& operator=(const T& v) { return _value = static_cast<UnderlyingType>(v); return *this; }
	EnumFlags<T>& operator=(const UnderlyingType& v) { _value = v; return *this; }

	constexpr bool operator&(const T& v) { return _value & static_cast<UnderlyingType>(v); }
	constexpr bool operator[](const T& v) const { return _value & static_cast<UnderlyingType>(v); }

private:

	UnderlyingType _value;
};
