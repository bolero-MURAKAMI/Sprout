/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_CURVE_CURVE_POINT_HPP
#define SPROUT_MATH_CURVE_CURVE_POINT_HPP

#include <utility>
#include <sprout/config.hpp>
#include <sprout/tuple/traits.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/type_traits/remove_cvref.hpp>
#include <sprout/tuple/traits.hpp>

namespace sprout {
	namespace math {
		//
		// curve_point
		// curve_point_traits
		// curve_point_result
		//
		template<typename Points>
		struct curve_point
			: public sprout::remove_cvref<decltype(sprout::tuples::nested_get<0>(std::declval<Points const&>()))>
		{};
		template<typename Points>
		struct curve_point_traits
			: public sprout::tuples::tuple_construct_traits<typename sprout::math::curve_point<Points>::type>
		{};
		template<typename Points>
		struct curve_point_result
			: public sprout::identity<
				typename sprout::math::curve_point_traits<Points>::copied_type
			>
		{};
	}	// namespace math
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_CURVE_CURVE_POINT_HPP
