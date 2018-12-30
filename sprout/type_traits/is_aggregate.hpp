/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_IS_AGGREGATE_HPP
#define SPROUT_TYPE_TRAITS_IS_AGGREGATE_HPP

#include <sprout/config.hpp>
#include <sprout/detail/predef.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/remove_cv.hpp>
#include <sprout/type_traits/remove_all_extents.hpp>

namespace sprout {
	//
	// is_aggregate
	//
#if SPROUT_CLANG_HAS_FUTURE(is_aggregate) || SPROUT_GCC_OR_LATER(7, 0, 0)
	template<typename T>
	struct is_aggregate
		: public sprout::bool_constant<
			__is_aggregate(typename sprout::remove_cv<typename sprout::remove_all_extents<T>::type>::type)
		>
	{};
#else	// #if SPROUT_CLANG_HAS_FUTURE(is_aggregate) || SPROUT_GCC_OR_LATER(7, 0, 0)
	template<typename T>
	struct is_aggregate
		: public sprout::false_type
	{};
#endif	// #if SPROUT_CLANG_HAS_FUTURE(is_aggregate) || SPROUT_GCC_OR_LATER(7, 0, 0)

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_aggregate_v = sprout::is_aggregate<T>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_IS_AGGREGATE_HPP
