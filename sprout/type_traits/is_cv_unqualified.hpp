/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_IS_CV_UNQUALIFIED_HPP
#define SPROUT_TYPE_TRAITS_IS_CV_UNQUALIFIED_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/is_const_unqualified.hpp>
#include <sprout/type_traits/is_volatile_unqualified.hpp>

namespace sprout {
	//
	// is_cv_unqualified
	//
	template<typename T>
	struct is_cv_unqualified
		: public sprout::bool_constant<
			sprout::is_const_unqualified<T>::value && sprout::is_volatile_unqualified<T>::value
		>
	{};

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_cv_unqualified_v = sprout::is_cv_unqualified<T>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_IS_CV_UNQUALIFIED_HPP
