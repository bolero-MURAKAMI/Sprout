/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DETAIL_SIZEOF_HPP
#define SPROUT_DETAIL_SIZEOF_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	namespace detail {
		template<typename... Ts>
		struct sizeof_pack
			: public std::integral_constant<std::size_t, sizeof...(Ts)>
		{};
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_SIZEOF_HPP
