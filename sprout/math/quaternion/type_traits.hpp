/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_QUATERNION_TYPE_TRAITS_HPP
#define SPROUT_MATH_QUATERNION_TYPE_TRAITS_HPP

#include <sprout/config.hpp>
#include <sprout/math/quaternion/quaternion.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	namespace math {
		//
		// is_quaternion
		//
		template<typename T>
		struct is_quaternion
			: public sprout::false_type
		{};
		template<typename T>
		struct is_quaternion<T const>
			: public sprout::math::is_quaternion<T>
		{};
		template<typename T>
		struct is_quaternion<T const volatile>
			: public sprout::math::is_quaternion<T>
		{};
		template<typename T>
		struct is_quaternion<sprout::math::quaternion<T> >
			: public sprout::true_type
		{};

#if SPROUT_USE_VARIABLE_TEMPLATES
		template<typename T>
		SPROUT_STATIC_CONSTEXPR bool is_quaternion_v = sprout::math::is_quaternion<T>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
	}	// namespace math

	using sprout::math::is_quaternion;
#if SPROUT_USE_VARIABLE_TEMPLATES
	using sprout::math::is_quaternion_v;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_QUATERNION_TYPE_TRAITS_HPP
