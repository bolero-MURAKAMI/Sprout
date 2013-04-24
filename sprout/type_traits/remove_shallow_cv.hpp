#ifndef SPROUT_TYPE_TRAITS_REMOVE_SHALLOW_CV_HPP
#define SPROUT_TYPE_TRAITS_REMOVE_SHALLOW_CV_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/identity.hpp>

namespace sprout {
	//
	// remove_shallow_cv
	//
	template<typename T>
	struct remove_shallow_cv
		: public sprout::identity<T>
	{};
	template<typename T>
	struct remove_shallow_cv<T const>
		: public std::conditional<std::is_array<T>::value, T const, T>
	{};
	template<typename T>
	struct remove_shallow_cv<T volatile>
		: public std::conditional<std::is_array<T>::value, T volatile, T>
	{};
	template<typename T>
	struct remove_shallow_cv<T const volatile>
		: public std::conditional<std::is_array<T>::value, T const volatile, T>
	{};

#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T>
	using remove_shallow_cv_t = typename sprout::remove_shallow_cv<T>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_REMOVE_SHALLOW_CV_HPP
