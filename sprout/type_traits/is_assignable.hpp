/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_IS_ASSIGNABLE_HPP
#define SPROUT_TYPE_TRAITS_IS_ASSIGNABLE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/detail/type_traits_wrapper.hpp>

namespace sprout {
	//
	// is_assignable
	//
	template<typename T, typename U>
	struct is_assignable
		: public sprout::detail::type_traits_wrapper<std::is_assignable<T, U> >
	{};

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename T, typename U>
	SPROUT_STATIC_CONSTEXPR bool is_assignable_v = sprout::is_assignable<T, U>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_IS_ASSIGNABLE_HPP
