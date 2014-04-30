/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_STRING_HASH_HPP
#define SPROUT_STRING_HASH_HPP

#include <functional>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/string/string.hpp>
#include <sprout/functional/hash.hpp>

namespace sprout {
	//
	// hash_value
	//
	template<typename T, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR std::size_t
	hash_value(sprout::basic_string<T, N, Traits> const& v) {
		return sprout::hash_range(v);
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
	template<typename T, std::size_t N, typename Traits>
	struct hash<sprout::basic_string<T, N, Traits> >
		: public sprout::hash<sprout::basic_string<T, N, Traits> >
	{};
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif
}	// namespace std

#endif	// #ifndef SPROUT_STRING_HASH_HPP
