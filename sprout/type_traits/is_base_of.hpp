/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_IS_BASE_OF_HPP
#define SPROUT_TYPE_TRAITS_IS_BASE_OF_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/detail/type_traits_wrapper.hpp>

namespace sprout {
	//
	// is_base_of
	//
	template<typename From, typename To>
	struct is_base_of
		: public sprout::detail::type_traits_wrapper<std::is_base_of<From, To> >
	{};

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename From, typename To>
	SPROUT_STATIC_CONSTEXPR bool is_base_of_v = sprout::is_base_of<From, To>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_IS_BASE_OF_HPP
