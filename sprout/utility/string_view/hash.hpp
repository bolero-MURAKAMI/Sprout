/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_STRING_VIEW_HASH_HPP
#define SPROUT_UTILITY_STRING_VIEW_HASH_HPP

#include <functional>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/utility/string_view/string_view.hpp>
#include <sprout/functional/hash.hpp>

namespace sprout {
	//
	// hash_value
	//
	template<typename T, typename Traits>
	inline SPROUT_CONSTEXPR std::size_t
	hash_value(sprout::basic_string_view<T, Traits> const& v) {
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
	template<typename T, typename Traits>
	struct hash<sprout::basic_string_view<T, Traits> >
		: public sprout::hash<sprout::basic_string_view<T, Traits> >
	{};
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif
}	// namespace std

#endif	// #ifndef SPROUT_UTILITY_STRING_VIEW_HASH_HPP
