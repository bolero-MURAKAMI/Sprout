#ifndef SPROUT_COMPLEX_HASH_HPP
#define SPROUT_COMPLEX_HASH_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/complex/complex.hpp>
#include <sprout/functional/hash.hpp>

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

namespace std {
	//
	// hash
	//
	template<typename T>
	struct hash<sprout::complex<T> >
		: public sprout::hash<sprout::complex<T> >
	{};
}	// namespace std

#endif	// #ifndef SPROUT_COMPLEX_HASH_HPP
