/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_HASH_HASH_RANGE_HPP
#define SPROUT_FUNCTIONAL_HASH_HASH_RANGE_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/functional/hash/hash_fwd.hpp>
#include <sprout/functional/hash/hash_combine.hpp>
#include <sprout/container/begin.hpp>
#include <sprout/container/end.hpp>
#include <sprout/numeric/accumulate.hpp>

namespace sprout {
	//
	// hash_combine_accumulator
	//
	template<typename T = std::size_t>
	struct hash_combine_accumulator {
	public:
		typedef T first_argument_type;
		typedef T result_type;
	public:
		template<typename U>
		SPROUT_CONSTEXPR T operator()(T const& seed, U const& v) const {
			return sprout::hash_combine(seed, v);
		}
	};

	//
	// hash_range
	//
	template<typename InputIterator>
	inline SPROUT_CONSTEXPR std::size_t
	hash_range(std::size_t seed, InputIterator first, InputIterator last) {
		return sprout::accumulate(first, last, seed, sprout::hash_combine_accumulator<>());
	}
	template<typename InputIterator>
	inline SPROUT_CONSTEXPR std::size_t
	hash_range(InputIterator first, InputIterator last) {
		return sprout::hash_range(0, first, last);
	}

	template<typename InputRange>
	inline SPROUT_CONSTEXPR std::size_t
	hash_range(std::size_t seed, InputRange const& rng) {
		return sprout::hash_range(seed, sprout::begin(rng), sprout::end(rng));
	}
	template<typename InputRange>
	inline SPROUT_CONSTEXPR std::size_t
	hash_range(InputRange const& rng) {
		return sprout::hash_range(0, rng);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_HASH_HASH_RANGE_HPP
