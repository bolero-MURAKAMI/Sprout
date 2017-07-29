/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ARRAY_COMPARISON_HPP
#define SPROUT_ARRAY_COMPARISON_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/array/array.hpp>
#include <sprout/algorithm/equal.hpp>
#include <sprout/algorithm/lexicographical_compare.hpp>

namespace sprout {
	//
	// operator==
	// operator!=
	// operator<
	// operator>
	// operator<=
	// operator>=
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR bool
	operator==(sprout::array<T, N> const& lhs, sprout::array<T, N> const& rhs) {
		return sprout::equal(lhs.begin(), lhs.end(), rhs.begin());
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR bool
	operator!=(sprout::array<T, N> const& lhs, sprout::array<T, N> const& rhs) {
		return !(lhs == rhs);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR bool
	operator<(sprout::array<T, N> const& lhs, sprout::array<T, N> const& rhs) {
		return sprout::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR bool
	operator>(sprout::array<T, N> const& lhs, sprout::array<T, N> const& rhs) {
		return rhs < lhs;
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR bool
	operator<=(sprout::array<T, N> const& lhs, sprout::array<T, N> const& rhs) {
		return !(rhs < lhs);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR bool
	operator>=(sprout::array<T, N> const& lhs, sprout::array<T, N> const& rhs) {
		return !(lhs < rhs);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ARRAY_COMPARISON_HPP
