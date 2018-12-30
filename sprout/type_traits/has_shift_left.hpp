/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_HAS_SHIFT_LEFT_HPP
#define SPROUT_TYPE_TRAITS_HAS_SHIFT_LEFT_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/dont_care.hpp>
#include <sprout/type_traits/detail/has_binary_op.hpp>

namespace sprout {
	//
	// has_shift_left
	//
	SPROUT_DETAIL_HAS_BINARY_OP_DECL(shift_left, <<, = T);

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename T, typename U = T, typename R = sprout::dont_care>
	SPROUT_STATIC_CONSTEXPR bool has_shift_left_v = sprout::has_shift_left<T, U, R>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_HAS_SHIFT_LEFT_HPP
