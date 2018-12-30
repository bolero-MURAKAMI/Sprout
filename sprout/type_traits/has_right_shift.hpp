/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_HAS_RIGHT_SHIFT_HPP
#define SPROUT_TYPE_TRAITS_HAS_RIGHT_SHIFT_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/dont_care.hpp>
#include <sprout/type_traits/has_shift_right.hpp>

namespace sprout {
	//
	// has_right_shift
	//
	template<typename T, typename U = T, typename R = sprout::dont_care>
	struct has_right_shift
		: public sprout::has_shift_right<T, U, R>
	{};

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename T, typename U = T, typename R = sprout::dont_care>
	SPROUT_STATIC_CONSTEXPR bool has_right_shift_v = sprout::has_right_shift<T, U, R>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_HAS_RIGHT_SHIFT_HPP
