/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_ALIGNED_STORAGE_HPP
#define SPROUT_TYPE_TRAITS_ALIGNED_STORAGE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/type_traits/alignment_of.hpp>

namespace sprout {
	//
	// aligned_storage
	//
	using std::aligned_storage;

#if SPROUT_USE_TEMPLATE_ALIASES
	template<
		std::size_t Len,
		std::size_t Align = sprout::alignment_of<typename sprout::aligned_storage<Len>::type>::value
	>
	using aligned_storage_t = typename sprout::aligned_storage<Len, Align>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_ALIGNED_STORAGE_HPP
