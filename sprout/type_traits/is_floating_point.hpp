/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_IS_FLOATING_POINT_HPP
#define SPROUT_TYPE_TRAITS_IS_FLOATING_POINT_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/detail/type_traits_wrapper.hpp>

namespace sprout {
	//
	// is_floating_point
	//
	template<typename T>
	struct is_floating_point
		: public sprout::detail::type_traits_wrapper<std::is_floating_point<T> >
	{};

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_floating_point_v = sprout::is_floating_point<T>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_IS_FLOATING_POINT_HPP
