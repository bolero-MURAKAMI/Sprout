/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPLEX_TYPE_TRAITS_HPP
#define SPROUT_COMPLEX_TYPE_TRAITS_HPP

#include <sprout/config.hpp>
#include <sprout/complex/complex.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	//
	// is_complex
	//
	template<typename T>
	struct is_complex
		: public sprout::false_type
	{};
	template<typename T>
	struct is_complex<T const>
		: public sprout::is_complex<T>
	{};
	template<typename T>
	struct is_complex<T const volatile>
		: public sprout::is_complex<T>
	{};
	template<typename T>
	struct is_complex<sprout::complex<T> >
		: public sprout::true_type
	{};

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_complex_v = sprout::is_complex<T>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPLEX_TYPE_TRAITS_HPP
