#ifndef SPROUT_TYPE_TRAITS_IS_C_STR_HPP
#define SPROUT_TYPE_TRAITS_IS_C_STR_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	//
	// is_c_str
	//
	template<typename T>
	struct is_c_str
		: public std::false_type
	{};
	template<typename T>
	struct is_c_str<T const>
		: public sprout::is_c_str<T>
	{};
	template<typename T>
	struct is_c_str<T volatile>
		: public sprout::is_c_str<T>
	{};
	template<typename T>
	struct is_c_str<T const volatile>
		: public sprout::is_c_str<T>
	{};
	template<std::size_t N>
	struct is_c_str<char[N]>
		: public std::true_type
	{};
	template<std::size_t N>
	struct is_c_str<wchar_t[N]>
		: public std::true_type
	{};
	template<std::size_t N>
	struct is_c_str<char16_t[N]>
		: public std::true_type
	{};
	template<std::size_t N>
	struct is_c_str<char32_t[N]>
		: public std::true_type
	{};

#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T>
	using is_c_str_t = typename sprout::is_c_str<T>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_IS_C_STR_HPP
