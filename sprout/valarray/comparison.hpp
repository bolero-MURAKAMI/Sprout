/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
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
#include <sprout/functional/not_equal_to.hpp>
#include <sprout/functional/greater.hpp>
#include <sprout/functional/less.hpp>
#include <sprout/functional/greater_equal.hpp>
#include <sprout/functional/less_equal.hpp>
#include <sprout/functional/bind2nd.hpp>
#include <sprout/functional/bind1st.hpp>
#include <sprout/sized_pit/sized_pit.hpp>

namespace sprout {
	//
	// operator==
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<bool, N>
	operator==(sprout::valarray<T, N> const& lhs, sprout::valarray<T, N> const& rhs) {
		typedef sprout::sized_pit<sprout::valarray<bool, N> > sized_pit_type;
		return sprout::fixed::transform(lhs.begin(), lhs.end(), rhs.begin(), sized_pit_type(lhs.size()), sprout::equal_to<>());
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<bool, N>
	operator==(sprout::valarray<T, N> const& lhs, T const& rhs) {
		typedef sprout::sized_pit<sprout::valarray<bool, N> > sized_pit_type;
		return sprout::fixed::transform(lhs.begin(), lhs.end(), sized_pit_type(lhs.size()), sprout::bind2nd(sprout::equal_to<>(), rhs));
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<bool, N>
	operator==(T const& lhs, sprout::valarray<T, N> const& rhs) {
		typedef sprout::sized_pit<sprout::valarray<bool, N> > sized_pit_type;
		return sprout::fixed::transform(rhs.begin(), rhs.end(), sized_pit_type(rhs.size()), sprout::bind1st(sprout::equal_to<>(), lhs));
	}
	//
	// operator!=
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<bool, N>
	operator!=(sprout::valarray<T, N> const& lhs, sprout::valarray<T, N> const& rhs) {
		typedef sprout::sized_pit<sprout::valarray<bool, N> > sized_pit_type;
		return sprout::fixed::transform(lhs.begin(), lhs.end(), rhs.begin(), sized_pit_type(lhs.size()), sprout::not_equal_to<>());
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<bool, N>
	operator!=(sprout::valarray<T, N> const& lhs, T const& rhs) {
		typedef sprout::sized_pit<sprout::valarray<bool, N> > sized_pit_type;
		return sprout::fixed::transform(lhs.begin(), lhs.end(), sized_pit_type(lhs.size()), sprout::bind2nd(sprout::not_equal_to<>(), rhs));
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<bool, N>
	operator!=(T const& lhs, sprout::valarray<T, N> const& rhs) {
		typedef sprout::sized_pit<sprout::valarray<bool, N> > sized_pit_type;
		return sprout::fixed::transform(rhs.begin(), rhs.end(), sized_pit_type(rhs.size()), sprout::bind1st(sprout::not_equal_to<>(), lhs));
	}
	//
	// operator<
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<bool, N>
	operator<(sprout::valarray<T, N> const& lhs, sprout::valarray<T, N> const& rhs) {
		typedef sprout::sized_pit<sprout::valarray<bool, N> > sized_pit_type;
		return sprout::fixed::transform(lhs.begin(), lhs.end(), rhs.begin(), sized_pit_type(lhs.size()), sprout::less<>());
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<bool, N>
	operator<(sprout::valarray<T, N> const& lhs, T const& rhs) {
		typedef sprout::sized_pit<sprout::valarray<bool, N> > sized_pit_type;
		return sprout::fixed::transform(lhs.begin(), lhs.end(), sized_pit_type(lhs.size()), sprout::bind2nd(sprout::less<>(), rhs));
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<bool, N>
	operator<(T const& lhs, sprout::valarray<T, N> const& rhs) {
		typedef sprout::sized_pit<sprout::valarray<bool, N> > sized_pit_type;
		return sprout::fixed::transform(rhs.begin(), rhs.end(), sized_pit_type(rhs.size()), sprout::bind1st(sprout::less<>(), lhs));
	}
	//
	// operator>
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<bool, N>
	operator>(sprout::valarray<T, N> const& lhs, sprout::valarray<T, N> const& rhs) {
		typedef sprout::sized_pit<sprout::valarray<bool, N> > sized_pit_type;
		return sprout::fixed::transform(lhs.begin(), lhs.end(), rhs.begin(), sized_pit_type(lhs.size()), sprout::greater<>());
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<bool, N>
	operator>(sprout::valarray<T, N> const& lhs, T const& rhs) {
		typedef sprout::sized_pit<sprout::valarray<bool, N> > sized_pit_type;
		return sprout::fixed::transform(lhs.begin(), lhs.end(), sized_pit_type(lhs.size()), sprout::bind2nd(sprout::greater<>(), rhs));
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<bool, N>
	operator>(T const& lhs, sprout::valarray<T, N> const& rhs) {
		typedef sprout::sized_pit<sprout::valarray<bool, N> > sized_pit_type;
		return sprout::fixed::transform(rhs.begin(), rhs.end(), sized_pit_type(rhs.size()), sprout::bind1st(sprout::greater<>(), lhs));
	}
	//
	// operator<=
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<bool, N>
	operator<=(sprout::valarray<T, N> const& lhs, sprout::valarray<T, N> const& rhs) {
		typedef sprout::sized_pit<sprout::valarray<bool, N> > sized_pit_type;
		return sprout::fixed::transform(lhs.begin(), lhs.end(), rhs.begin(), sized_pit_type(lhs.size()), sprout::less_equal<>());
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<bool, N>
	operator<=(sprout::valarray<T, N> const& lhs, T const& rhs) {
		typedef sprout::sized_pit<sprout::valarray<bool, N> > sized_pit_type;
		return sprout::fixed::transform(lhs.begin(), lhs.end(), sized_pit_type(lhs.size()), sprout::bind2nd(sprout::less_equal<>(), rhs));
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<bool, N>
	operator<=(T const& lhs, sprout::valarray<T, N> const& rhs) {
		typedef sprout::sized_pit<sprout::valarray<bool, N> > sized_pit_type;
		return sprout::fixed::transform(rhs.begin(), rhs.end(), sized_pit_type(rhs.size()), sprout::bind1st(sprout::less_equal<>(), lhs));
	}
	//
	// operator>=
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<bool, N>
	operator>=(sprout::valarray<T, N> const& lhs, sprout::valarray<T, N> const& rhs) {
		typedef sprout::sized_pit<sprout::valarray<bool, N> > sized_pit_type;
		return sprout::fixed::transform(lhs.begin(), lhs.end(), rhs.begin(), sized_pit_type(lhs.size()), sprout::greater_equal<>());
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<bool, N>
	operator>=(sprout::valarray<T, N> const& lhs, T const& rhs) {
		typedef sprout::sized_pit<sprout::valarray<bool, N> > sized_pit_type;
		return sprout::fixed::transform(lhs.begin(), lhs.end(), sized_pit_type(lhs.size()), sprout::bind2nd(sprout::greater_equal<>(), rhs));
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<bool, N>
	operator>=(T const& lhs, sprout::valarray<T, N> const& rhs) {
		typedef sprout::sized_pit<sprout::valarray<bool, N> > sized_pit_type;
		return sprout::fixed::transform(rhs.begin(), rhs.end(), sized_pit_type(rhs.size()), sprout::bind1st(sprout::greater_equal<>(), lhs));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_VALARRAY_COMPARISON_HPP
