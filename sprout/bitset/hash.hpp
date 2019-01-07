/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_BITSET_HASH_HPP
#define SPROUT_BITSET_HASH_HPP

#include <functional>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/bitset/bitset.hpp>

namespace sprout {
	// 20.5.3 hash support

	//
	// hash_value
	//
	template<std::size_t N>
	inline SPROUT_CONSTEXPR std::size_t
	hash_value(sprout::bitset<N> const& v) {
		return v.to_hash();
	}
}	// namespace sprout

namespace std {
#if defined(__clang__)
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wmismatched-tags"
#endif
	//
	// hash
	//
	template<std::size_t N>
	struct hash<sprout::bitset<N> >
		: public sprout::hash<sprout::bitset<N> >
	{};
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif
}	// namespace std

#endif	// #ifndef SPROUT_BITSET_HASH_HPP
