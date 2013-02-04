#ifndef SPROUT_FUNCTIONAL_HASH_HASH_RANGE_HPP
#define SPROUT_FUNCTIONAL_HASH_HASH_RANGE_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/functional/hash/hash_fwd.hpp>
#include <sprout/functional/hash/hash_combine.hpp>
#include <sprout/iterator/next.hpp>

namespace sprout {
	//
	// hash_range
	//
	template<typename InputIterator>
	inline SPROUT_CONSTEXPR std::size_t
	hash_range(std::size_t seed, InputIterator first, InputIterator last) {
		return first != last
			? sprout::hash_range(sprout::hash_combine(seed, *first), sprout::next(first), last)
			: seed
			;
	}
	template<typename InputIterator>
	inline SPROUT_CONSTEXPR std::size_t
	hash_range(InputIterator first, InputIterator last) {
		return sprout::hash_range(0, first, last);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_HASH_HASH_RANGE_HPP
