#ifndef SPROUT_TYPE_TRAITS_IS_INT_HPP
#define SPROUT_TYPE_TRAITS_IS_INT_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	//
	// is_int
	//
	template<typename T>
	struct is_int
		: public std::integral_constant<
			bool,
			std::is_integral<T>::value && std::is_signed<T>::value
		>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_IS_INT_HPP
