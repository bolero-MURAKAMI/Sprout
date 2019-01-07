/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_HAS_UNIQUE_OBJECT_REPRESENTATIONS_HPP
#define SPROUT_TYPE_TRAITS_HAS_UNIQUE_OBJECT_REPRESENTATIONS_HPP

#include <sprout/config.hpp>
#include <sprout/detail/predef.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/remove_cv.hpp>
#include <sprout/type_traits/remove_all_extents.hpp>

namespace sprout {
	//
	// has_unique_object_representations
	//
#if SPROUT_CLANG_HAS_FUTURE(has_unique_object_representations) || SPROUT_GCC_OR_LATER(7, 0, 0)
	template<typename T>
	struct has_unique_object_representations
		: public sprout::bool_constant<
			__has_unique_object_representations(typename sprout::remove_cv<typename sprout::remove_all_extents<T>::type>::type)
		>
	{};
#else	// #if SPROUT_CLANG_HAS_FUTURE(has_unique_object_representations) || SPROUT_GCC_OR_LATER(7, 0, 0)
	template<typename T>
	struct has_unique_object_representations
		: public sprout::false_type
	{};
#endif	// #if SPROUT_CLANG_HAS_FUTURE(has_unique_object_representations) || SPROUT_GCC_OR_LATER(7, 0, 0)

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool has_unique_object_representations_v = sprout::has_unique_object_representations<T>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_HAS_UNIQUE_OBJECT_REPRESENTATIONS_HPP
