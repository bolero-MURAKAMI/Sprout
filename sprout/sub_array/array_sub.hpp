/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_SUB_ARRAY_ARRAY_SUB_HPP
#define SPROUT_SUB_ARRAY_ARRAY_SUB_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/array/array.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/type_traits/identity.hpp>

namespace sprout {
	//
	// array_sub
	//
	template<typename T, std::size_t N>
	struct array_sub
		: public sprout::identity<sprout::sub_array<sprout::array<T, N> > >
	{};

#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T, std::size_t N>
	using array_sub_t = typename sprout::array_sub<T, N>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_SUB_ARRAY_ARRAY_SUB_HPP
