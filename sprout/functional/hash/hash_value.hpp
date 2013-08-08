/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_HASH_HASH_VALUE_HPP
#define SPROUT_FUNCTIONAL_HASH_HASH_VALUE_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/functional/hash/hash_fwd.hpp>

namespace sprout {
	//
	// hash_value
	//
	template<typename T>
	inline SPROUT_CONSTEXPR std::size_t
	hash_value(T const& v) {
		return sprout::hash_value_traits<T>::hash_value(v);
	}
}	// namespace sprout

#include <sprout/functional/hash/hash_value_traits.hpp>

#endif	// #ifndef SPROUT_FUNCTIONAL_HASH_HASH_VALUE_HPP
