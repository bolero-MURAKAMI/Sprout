/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_EXTENT_HPP
#define SPROUT_TYPE_TRAITS_EXTENT_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/type_traits/detail/type_traits_wrapper.hpp>

namespace sprout {
	//
	// extent
	//
	template<typename T, unsigned I = 0>
	struct extent
		: public sprout::detail::type_traits_wrapper<std::extent<T, I> >
	{};

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename T, unsigned I = 0>
	SPROUT_STATIC_CONSTEXPR std::size_t extent_v = sprout::extent<T, I>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_EXTENT_HPP
