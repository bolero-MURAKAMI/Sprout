/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
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
	//
	// true_type
	// false_type
	//
	typedef sprout::integral_constant<bool, true> true_type;
	typedef sprout::integral_constant<bool, false> false_type;
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP
