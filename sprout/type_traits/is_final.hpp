/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_IS_FINAL_HPP
#define SPROUT_TYPE_TRAITS_IS_FINAL_HPP

#include <sprout/config.hpp>
#include <sprout/detail/predef.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	//
	// is_final
	//
#if SPROUT_CLANG_HAS_FUTURE(is_final) || SPROUT_GCC_OR_LATER(4, 7, 0)
	template<typename T>
	struct is_final
		: public sprout::bool_constant<__is_final(T)>
	{};
#else	// #if SPROUT_CLANG_HAS_FUTURE(is_final) || SPROUT_GCC_OR_LATER(4, 7, 0)
	template<typename T>
	struct is_final
		: public sprout::false_type
	{};
#endif	// #if SPROUT_CLANG_HAS_FUTURE(is_final) || SPROUT_GCC_OR_LATER(4, 7, 0)

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_final_v = sprout::is_final<T>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_IS_FINAL_HPP
