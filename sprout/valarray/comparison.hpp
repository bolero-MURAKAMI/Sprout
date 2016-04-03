/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_VALARRAY_COMPARISON_HPP
#define SPROUT_VALARRAY_COMPARISON_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/valarray/valarray.hpp>
#include <sprout/algorithm/fixed/transform.hpp>
#include <sprout/functional/equal_to.hpp>
#include <sprout/functional/less.hpp>
#include <sprout/functional/bind2nd.hpp>
#include <sprout/functional/bind1st.hpp>

namespace sprout {
	//
	// operator==
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<bool, N>
	operator==(sprout::valarray<T, N> const& lhs, sprout::valarray<T, N> const& rhs) {
		return sprout::fixed::transform(lhs.begin(), lhs.end(), rhs.begin(), sprout::valarray<bool, N>(lhs.size()), sprout::equal_to<>());
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<bool, N>
	operator==(sprout::valarray<T, N> const& lhs, T const& rhs) {
		return sprout::fixed::transform(lhs.begin(), lhs.end(), sprout::valarray<bool, N>(lhs.size()), sprout::bind2nd(sprout::equal_to<>(), rhs));
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<bool, N>
	operator==(T const& lhs, sprout::valarray<T, N> const& rhs) {
		return sprout::fixed::transform(rhs.begin(), rhs.end(), sprout::valarray<bool, N>(rhs.size()), sprout::bind1st(sprout::equal_to<>(), lhs));
	}
	//
	// operator!=
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<bool, N>
	operator!=(sprout::valarray<T, N> const& lhs, sprout::valarray<T, N> const& rhs) {
		return !(lhs == rhs);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<bool, N>
	operator!=(sprout::valarray<T, N> const& lhs, T const& rhs) {
		return !(lhs == rhs);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<bool, N>
	operator!=(T const& lhs, sprout::valarray<T, N> const& rhs) {
		return !(lhs == rhs);
	}
	//
	// operator<
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<bool, N>
	operator<(sprout::valarray<T, N> const& lhs, sprout::valarray<T, N> const& rhs) {
		return sprout::fixed::transform(lhs.begin(), lhs.end(), rhs.begin(), sprout::valarray<bool, N>(lhs.size()), sprout::less<>());
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<bool, N>
	operator<(sprout::valarray<T, N> const& lhs, T const& rhs) {
		return sprout::fixed::transform(lhs.begin(), lhs.end(), sprout::valarray<bool, N>(lhs.size()), sprout::bind2nd(sprout::less<>(), rhs));
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<bool, N>
	operator<(T const& lhs, sprout::valarray<T, N> const& rhs) {
		return sprout::fixed::transform(rhs.begin(), rhs.end(), sprout::valarray<bool, N>(rhs.size()), sprout::bind1st(sprout::less<>(), lhs));
	}
	//
	// operator>
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<bool, N>
	operator>(sprout::valarray<T, N> const& lhs, sprout::valarray<T, N> const& rhs) {
		return rhs < lhs;
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<bool, N>
	operator>(sprout::valarray<T, N> const& lhs, T const& rhs) {
		return rhs < lhs;
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<bool, N>
	operator>(T const& lhs, sprout::valarray<T, N> const& rhs) {
		return rhs < lhs;
	}
	//
	// operator<=
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<bool, N>
	operator<=(sprout::valarray<T, N> const& lhs, sprout::valarray<T, N> const& rhs) {
		return !(rhs < lhs);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<bool, N>
	operator<=(sprout::valarray<T, N> const& lhs, T const& rhs) {
		return !(rhs < lhs);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<bool, N>
	operator<=(T const& lhs, sprout::valarray<T, N> const& rhs) {
		return !(rhs < lhs);
	}
	//
	// operator>=
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<bool, N>
	operator>=(sprout::valarray<T, N> const& lhs, sprout::valarray<T, N> const& rhs) {
		return !(lhs < rhs);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<bool, N>
	operator>=(sprout::valarray<T, N> const& lhs, T const& rhs) {
		return !(lhs < rhs);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<bool, N>
	operator>=(T const& lhs, sprout::valarray<T, N> const& rhs) {
		return !(lhs < rhs);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_VALARRAY_COMPARISON_HPP
