#ifndef SPROUT_TYPE_TRAITS_REMOVE_CVREF_HPP
#define SPROUT_TYPE_TRAITS_REMOVE_CVREF_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	//
	// remove_cvref
	//
	template<typename T>
	struct remove_cvref
		: public std::remove_cv<
			typename std::remove_reference<T>::type
		>
	{};

#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T>
	using remove_cvref_ = typename sprout::remove_cvref<T>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_REMOVE_CVREF_HPP
