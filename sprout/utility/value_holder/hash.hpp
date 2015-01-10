/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_VALUE_HOLDER_HASH_HPP
#define SPROUT_UTILITY_VALUE_HOLDER_HASH_HPP

#include <functional>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/utility/value_holder/value_holder.hpp>
#include <sprout/functional/hash.hpp>

namespace sprout {
	//
	// hash_value
	//
	template<typename T>
	inline SPROUT_CONSTEXPR std::size_t
	hash_value(sprout::value_holder<T> const& v) {
		return sprout::to_hash(*v)
			;
	}
	template<typename T>
	inline SPROUT_CONSTEXPR std::size_t
	hash_value(sprout::value_holder<T&> const& v) {
		return v.is_initialized() ? sprout::to_hash(*v)
			: 0
			;
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
	template<typename T>
	struct hash<sprout::value_holder<T> >
		: public sprout::hash<sprout::value_holder<T> >
	{};
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif
}	// namespace std

#endif	// #ifndef SPROUT_UTILITY_VALUE_HOLDER_HASH_HPP
