/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_VALARRAY_TYPE_TRAITS_HPP
#define SPROUT_VALARRAY_TYPE_TRAITS_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/valarray/valarray.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	//
	// is_valarray
	//
	template<typename T>
	struct is_valarray
		: public sprout::false_type
	{};
	template<typename T>
	struct is_valarray<T const>
		: public sprout::is_valarray<T>
	{};
	template<typename T>
	struct is_valarray<T const volatile>
		: public sprout::is_valarray<T>
	{};
	template<typename T, std::size_t N>
	struct is_valarray<sprout::valarray<T, N> >
		: public sprout::true_type
	{};

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_valarray_v = sprout::is_valarray<T>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_VALARRAY_TYPE_TRAITS_HPP
