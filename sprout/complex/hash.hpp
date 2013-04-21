#ifndef SPROUT_COMPLEX_HASH_HPP
#define SPROUT_COMPLEX_HASH_HPP

#include <cstddef>
#include <functional>
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
#if defined(__clang__)
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wmismatched-tags"
#endif
	//
	// hash
	//
	template<typename T>
	struct hash<sprout::complex<T> >
		: public sprout::hash<sprout::complex<T> >
	{};
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif
}	// namespace std

#endif	// #ifndef SPROUT_COMPLEX_HASH_HPP
