/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_BITSET_BITWISE_HPP
#define SPROUT_BITSET_BITWISE_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/bitset/bitset.hpp>

namespace sprout {
	// 20.5.4 bitset operators:

	template<std::size_t N>
	inline SPROUT_CONSTEXPR sprout::bitset<N>
	operator&(sprout::bitset<N> const& lhs, sprout::bitset<N> const& rhs) SPROUT_NOEXCEPT {
		return sprout::bitset<N>(lhs.do_and(rhs));
	}
	template<std::size_t N>
	inline SPROUT_CONSTEXPR sprout::bitset<N>
	operator|(sprout::bitset<N> const& lhs, sprout::bitset<N> const& rhs) SPROUT_NOEXCEPT {
		return sprout::bitset<N>(lhs.do_or(rhs));
	}
	template<std::size_t N>
	inline SPROUT_CONSTEXPR sprout::bitset<N>
	operator^(sprout::bitset<N> const& lhs, sprout::bitset<N> const& rhs) SPROUT_NOEXCEPT {
		return sprout::bitset<N>(lhs.do_xor(rhs));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_BITSET_BITWISE_HPP
