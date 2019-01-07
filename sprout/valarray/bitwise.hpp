/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_VALARRAY_BITWISE_HPP
#define SPROUT_VALARRAY_BITWISE_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/valarray/valarray.hpp>
#include <sprout/algorithm/fixed/transform.hpp>
#include <sprout/functional/bit_and.hpp>
#include <sprout/functional/bit_or.hpp>
#include <sprout/functional/bit_xor.hpp>
#include <sprout/functional/shift_left.hpp>
#include <sprout/functional/shift_right.hpp>
#include <sprout/functional/bind2nd.hpp>
#include <sprout/functional/bind1st.hpp>

namespace sprout {
	//
	// operator&
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	operator&(sprout::valarray<T, N> const& lhs, sprout::valarray<T, N> const& rhs) {
		return sprout::fixed::transform(lhs.begin(), lhs.end(), rhs.begin(), lhs, sprout::bit_and<>());
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	operator&(sprout::valarray<T, N> const& lhs, T const& rhs) {
		return sprout::fixed::transform(lhs.begin(), lhs.end(), lhs, sprout::bind2nd(sprout::bit_and<>(), rhs));
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	operator&(T const& lhs, sprout::valarray<T, N> const& rhs) {
		return sprout::fixed::transform(rhs.begin(), rhs.end(), rhs, sprout::bind1st(sprout::bit_and<>(), lhs));
	}
	//
	// operator|
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	operator|(sprout::valarray<T, N> const& lhs, sprout::valarray<T, N> const& rhs) {
		return sprout::fixed::transform(lhs.begin(), lhs.end(), rhs.begin(), lhs, sprout::bit_or<>());
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	operator|(sprout::valarray<T, N> const& lhs, T const& rhs) {
		return sprout::fixed::transform(lhs.begin(), lhs.end(), lhs, sprout::bind2nd(sprout::bit_or<>(), rhs));
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	operator|(T const& lhs, sprout::valarray<T, N> const& rhs) {
		return sprout::fixed::transform(rhs.begin(), rhs.end(), rhs, sprout::bind1st(sprout::bit_or<>(), lhs));
	}
	//
	// operator^
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	operator^(sprout::valarray<T, N> const& lhs, sprout::valarray<T, N> const& rhs) {
		return sprout::fixed::transform(lhs.begin(), lhs.end(), rhs.begin(), lhs, sprout::bit_xor<>());
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	operator^(sprout::valarray<T, N> const& lhs, T const& rhs) {
		return sprout::fixed::transform(lhs.begin(), lhs.end(), lhs, sprout::bind2nd(sprout::bit_xor<>(), rhs));
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	operator^(T const& lhs, sprout::valarray<T, N> const& rhs) {
		return sprout::fixed::transform(rhs.begin(), rhs.end(), rhs, sprout::bind1st(sprout::bit_xor<>(), lhs));
	}
	//
	// operator<<
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	operator<<(sprout::valarray<T, N> const& lhs, sprout::valarray<T, N> const& rhs) {
		return sprout::fixed::transform(lhs.begin(), lhs.end(), rhs.begin(), lhs, sprout::shift_left<>());
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	operator<<(sprout::valarray<T, N> const& lhs, T const& rhs) {
		return sprout::fixed::transform(lhs.begin(), lhs.end(), lhs, sprout::bind2nd(sprout::shift_left<>(), rhs));
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	operator<<(T const& lhs, sprout::valarray<T, N> const& rhs) {
		return sprout::fixed::transform(rhs.begin(), rhs.end(), rhs, sprout::bind1st(sprout::shift_left<>(), lhs));
	}
	//
	// operator>>
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	operator>>(sprout::valarray<T, N> const& lhs, sprout::valarray<T, N> const& rhs) {
		return sprout::fixed::transform(lhs.begin(), lhs.end(), rhs.begin(), lhs, sprout::shift_right<>());
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	operator>>(sprout::valarray<T, N> const& lhs, T const& rhs) {
		return sprout::fixed::transform(lhs.begin(), lhs.end(), lhs, sprout::bind2nd(sprout::shift_right<>(), rhs));
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	operator>>(T const& lhs, sprout::valarray<T, N> const& rhs) {
		return sprout::fixed::transform(rhs.begin(), rhs.end(), rhs, sprout::bind1st(sprout::shift_right<>(), lhs));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_VALARRAY_BITWISE_HPP
