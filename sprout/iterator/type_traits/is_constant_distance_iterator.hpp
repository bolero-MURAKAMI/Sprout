/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ITERATOR_TYPE_TRAITS_IS_CONSTANT_DISTANCE_ITERATOR_HPP
#define SPROUT_ITERATOR_TYPE_TRAITS_IS_CONSTANT_DISTANCE_ITERATOR_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	//
	// is_constant_distance_iterator
	//
	template<typename MaybeIterator>
	struct is_constant_distance_iterator
		: public sprout::bool_constant<
#ifdef SPROUT_NO_CXX14_CONSTEXPR
			sprout::is_random_access_iterator<MaybeIterator>::value && !std::is_pointer<MaybeIterator>::value
#else	// #ifdef SPROUT_NO_CXX14_CONSTEXPR
			sprout::is_random_access_iterator<MaybeIterator>::value
#endif	// #ifdef SPROUT_NO_CXX14_CONSTEXPR
		>
	{};

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename MaybeIterator>
	SPROUT_STATIC_CONSTEXPR bool is_constant_distance_iterator_v = sprout::is_constant_distance_iterator<MaybeIterator>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_TYPE_TRAITS_IS_CONSTANT_DISTANCE_ITERATOR_HPP
