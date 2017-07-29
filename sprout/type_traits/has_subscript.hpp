/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_HAS_SUBSCRIPT_HPP
#define SPROUT_TYPE_TRAITS_HAS_SUBSCRIPT_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/type_traits/dont_care.hpp>
#include <sprout/type_traits/detail/has_subscript_op.hpp>

namespace sprout {
	//
	// has_subscript
	//
	SPROUT_DETAIL_HAS_SUBSCRIPT_OP_DECL(subscript, [], = std::size_t);

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename T, typename U = std::size_t, typename R = sprout::dont_care>
	SPROUT_STATIC_CONSTEXPR bool has_subscript_v = sprout::has_subscript<T, U, R>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_HAS_SUBSCRIPT_HPP
