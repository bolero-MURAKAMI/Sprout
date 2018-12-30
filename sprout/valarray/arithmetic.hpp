/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_VALARRAY_ARITHMETIC_HPP
#define SPROUT_VALARRAY_ARITHMETIC_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/valarray/valarray.hpp>
#include <sprout/algorithm/fixed/transform.hpp>
#include <sprout/functional/plus.hpp>
#include <sprout/functional/minus.hpp>
#include <sprout/functional/multiplies.hpp>
#include <sprout/functional/divides.hpp>
#include <sprout/functional/modulus.hpp>
#include <sprout/functional/bind2nd.hpp>
#include <sprout/functional/bind1st.hpp>

namespace sprout {
	//
	// operator+
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	operator+(sprout::valarray<T, N> const& lhs, sprout::valarray<T, N> const& rhs) {
		return sprout::fixed::transform(lhs.begin(), lhs.end(), rhs.begin(), lhs, sprout::plus<>());
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	operator+(sprout::valarray<T, N> const& lhs, T const& rhs) {
		return sprout::fixed::transform(lhs.begin(), lhs.end(), lhs, sprout::bind2nd(sprout::plus<>(), rhs));
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	operator+(T const& lhs, sprout::valarray<T, N> const& rhs) {
		return sprout::fixed::transform(rhs.begin(), rhs.end(), rhs, sprout::bind1st(sprout::plus<>(), lhs));
	}
	//
	// operator-
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	operator-(sprout::valarray<T, N> const& lhs, sprout::valarray<T, N> const& rhs) {
		return sprout::fixed::transform(lhs.begin(), lhs.end(), rhs.begin(), lhs, sprout::minus<>());
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	operator-(sprout::valarray<T, N> const& lhs, T const& rhs) {
		return sprout::fixed::transform(lhs.begin(), lhs.end(), lhs, sprout::bind2nd(sprout::minus<>(), rhs));
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	operator-(T const& lhs, sprout::valarray<T, N> const& rhs) {
		return sprout::fixed::transform(rhs.begin(), rhs.end(), rhs, sprout::bind1st(sprout::minus<>(), lhs));
	}
	//
	// operator*
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	operator*(sprout::valarray<T, N> const& lhs, sprout::valarray<T, N> const& rhs) {
		return sprout::fixed::transform(lhs.begin(), lhs.end(), rhs.begin(), lhs, sprout::multiplies<>());
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	operator*(sprout::valarray<T, N> const& lhs, T const& rhs) {
		return sprout::fixed::transform(lhs.begin(), lhs.end(), lhs, sprout::bind2nd(sprout::multiplies<>(), rhs));
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	operator*(T const& lhs, sprout::valarray<T, N> const& rhs) {
		return sprout::fixed::transform(rhs.begin(), rhs.end(), rhs, sprout::bind1st(sprout::multiplies<>(), lhs));
	}
	//
	// operator/
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	operator/(sprout::valarray<T, N> const& lhs, sprout::valarray<T, N> const& rhs) {
		return sprout::fixed::transform(lhs.begin(), lhs.end(), rhs.begin(), lhs, sprout::divides<>());
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	operator/(sprout::valarray<T, N> const& lhs, T const& rhs) {
		return sprout::fixed::transform(lhs.begin(), lhs.end(), lhs, sprout::bind2nd(sprout::divides<>(), rhs));
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	operator/(T const& lhs, sprout::valarray<T, N> const& rhs) {
		return sprout::fixed::transform(rhs.begin(), rhs.end(), rhs, sprout::bind1st(sprout::divides<>(), lhs));
	}
	//
	// operator%
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	operator%(sprout::valarray<T, N> const& lhs, sprout::valarray<T, N> const& rhs) {
		return sprout::fixed::transform(lhs.begin(), lhs.end(), rhs.begin(), lhs, sprout::modulus<>());
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	operator%(sprout::valarray<T, N> const& lhs, T const& rhs) {
		return sprout::fixed::transform(lhs.begin(), lhs.end(), lhs, sprout::bind2nd(sprout::modulus<>(), rhs));
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	operator%(T const& lhs, sprout::valarray<T, N> const& rhs) {
		return sprout::fixed::transform(rhs.begin(), rhs.end(), rhs, sprout::bind1st(sprout::modulus<>(), lhs));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_VALARRAY_ARITHMETIC_HPP
