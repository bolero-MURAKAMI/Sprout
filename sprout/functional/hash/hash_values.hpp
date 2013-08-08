/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_HASH_HASH_VALUES_HPP
#define SPROUT_FUNCTIONAL_HASH_HASH_VALUES_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/functional/hash/hash_fwd.hpp>
#include <sprout/functional/hash/hash_combine.hpp>

namespace sprout {
	//
	// hash_values
	//
	template<typename... Args>
	inline SPROUT_CONSTEXPR std::size_t
	hash_values(Args const&... args) {
		return sprout::hash_combine(0, args...);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_HASH_HASH_VALUES_HPP
