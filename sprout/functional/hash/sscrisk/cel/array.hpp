/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_HASH_SSCRISK_CEL_ARRAY_HPP
#define SPROUT_FUNCTIONAL_HASH_SSCRISK_CEL_ARRAY_HPP

#include <cstddef>
#include <sscrisk/cel/array.hpp>
#include <sprout/config.hpp>
#include <sprout/functional/hash/hash_value_traits.hpp>
#include <sprout/functional/hash/hash_range.hpp>

namespace sprout {
	//
	// hash_value_traits
	//
	template<typename T, std::size_t N>
	struct hash_value_traits<sscrisk::cel::array<T, N> > {
	public:
		static SPROUT_CONSTEXPR std::size_t
		hash_value(sscrisk::cel::array<T, N> const& v) {
			return sprout::hash_range(v);
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_HASH_SSCRISK_CEL_ARRAY_HPP
