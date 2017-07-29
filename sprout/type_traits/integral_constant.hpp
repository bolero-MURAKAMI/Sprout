/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP
#define SPROUT_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	//
	// integral_constant
	//
	template<typename T, T V>
	struct integral_constant
		: public std::integral_constant<T, V>
	{
	public:
		typedef typename std::integral_constant<T, V>::value_type value_type;
		typedef integral_constant type;
	public:
		SPROUT_STATIC_CONSTEXPR value_type value = V;
	public:
#if defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)
		SPROUT_CONSTEXPR integral_constant() SPROUT_NOEXCEPT {}
		integral_constant(integral_constant const&) = default;
#endif
		SPROUT_CONSTEXPR
		operator value_type() const SPROUT_NOEXCEPT {
			return std::integral_constant<T, V>::value;
		}
		SPROUT_CONSTEXPR bool
		operator!() const SPROUT_NOEXCEPT {
			return !std::integral_constant<T, V>::value;
		}
		SPROUT_CONSTEXPR value_type
		operator()() const SPROUT_NOEXCEPT {
			return std::integral_constant<T, V>::value;
		}
	};
	template<typename T, T V>
	SPROUT_CONSTEXPR_OR_CONST typename sprout::integral_constant<T, V>::value_type sprout::integral_constant<T, V>::value;

	//
	// bool_constant
	//
#if SPROUT_USE_TEMPLATE_ALIASES
	template<bool V>
	using bool_constant = sprout::integral_constant<bool, V>;
#else	// #if SPROUT_USE_TEMPLATE_ALIASES
	template<bool V>
	struct bool_constant
		: public sprout::integral_constant<bool, V>
	{};
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES

	//
	// true_type
	// false_type
	//
	typedef sprout::bool_constant<true> true_type;
	typedef sprout::bool_constant<false> false_type;
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP
