#ifndef SPROUT_VARIANT_TYPE_TRAITS_HPP
#define SPROUT_VARIANT_TYPE_TRAITS_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/variant/variant_fwd.hpp>

namespace sprout {
	//
	// is_variant
	//
	template<typename T>
	struct is_variant
		: public std::false_type
	{};
	template<typename T>
	struct is_variant<T const>
		: public sprout::is_variant<T>
	{};
	template<typename T>
	struct is_variant<T const volatile>
		: public sprout::is_variant<T>
	{};
	template<typename... Types>
	struct is_variant<sprout::variant<Types...> >
		: public std::true_type
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_VARIANT_TYPE_TRAITS_HPP
