/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_SWAP_HPP
#define SPROUT_UTILITY_SWAP_HPP

#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/utility/move.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout_swap_detail {
	using std::swap;

	template<typename T, typename sprout::enabler_if<std::is_scalar<T>::value>::type = sprout::enabler>
	inline SPROUT_CXX14_CONSTEXPR void
	swap_impl(T& a, T& b) SPROUT_NOEXCEPT {
		T temp = sprout::move(a);
		a = sprout::move(b);
		b = sprout::move(temp);
	}
	template<typename T, typename sprout::enabler_if<!std::is_scalar<T>::value>::type = sprout::enabler>
	inline SPROUT_CXX14_CONSTEXPR void
	swap_impl(T& a, T& b)
	SPROUT_NOEXCEPT_IF_EXPR(swap(a, b))
	{
		swap(a, b);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CXX14_CONSTEXPR void
	swap_impl(T (& a)[N], T (& b)[N])
	SPROUT_NOEXCEPT_IF_EXPR(sprout_swap_detail::swap_impl(*a, *b))
	{
		for (std::size_t i = 0; i < N; ++i) {
			sprout_swap_detail::swap_impl(a[i], b[i]);
		}
	}
}	// namespace sprout_swap_detail

namespace sprout {
	//
	// 20.2.2 swap
	//
	template<typename T1, typename T2>
	inline SPROUT_CXX14_CONSTEXPR void
	swap(T1& lhs, T2& rhs)
	SPROUT_NOEXCEPT_IF_EXPR(sprout_swap_detail::swap_impl(lhs, rhs))
	{
		return sprout_swap_detail::swap_impl(lhs, rhs);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_SWAP_HPP
