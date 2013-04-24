#ifndef SPROUT_TYPE_TRAITS_IS_UINT_HPP
#define SPROUT_TYPE_TRAITS_IS_UINT_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	//
	// is_uint
	//
	template<typename T>
	struct is_uint
		: public std::integral_constant<
			bool,
			std::is_integral<T>::value && std::is_unsigned<T>::value
		>
	{};

#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T>
	using is_uint_t = typename sprout::is_uint<T>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_IS_UINT_HPP
