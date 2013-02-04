#ifndef SPROUT_RATIONAL_HASH_HPP
#define SPROUT_RATIONAL_HASH_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/rational/rational.hpp>
#include <sprout/functional/hash.hpp>

namespace sprout {
	//
	// hash_value
	//
	template<typename T>
	inline SPROUT_CONSTEXPR std::size_t
	hash_value(sprout::rational<T> const& v) {
		return sprout::hash_values(v.numerator(), v.denominator());
	}
} // namespace sprout

#endif	// SPROUT_RATIONAL_HASH_HPP
