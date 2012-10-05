#ifndef SPROUT_COMPLEX_HASH_HPP
#define SPROUT_COMPLEX_HASH_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/complex/complex.hpp>
#include <sprout/functional/hash/hash.hpp>

namespace sprout {
	//
	// hash_value
	//
	template<typename T>
	inline SPROUT_CONSTEXPR std::size_t
	hash_value(sprout::complex<T> const& v) {
		return sprout::hash_values(v.real(), v.imag());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPLEX_HASH_HPP
