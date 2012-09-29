#ifndef SPROUT_ADL_NOT_FOUND_HPP
#define SPROUT_ADL_NOT_FOUND_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	//
	// not_found_via_adl
	//
	struct not_found_via_adl {};

	//
	// is_not_found_via_adl
	//
	template<typename T>
	struct is_not_found_via_adl
		: public std::is_same<T, sprout::not_found_via_adl>
	{};

	//
	// is_found_via_adl
	//
	template<typename T>
	struct is_found_via_adl
		: public std::integral_constant<bool, sprout::is_not_found_via_adl<T>::value>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_ADL_NOT_FOUND_HPP
