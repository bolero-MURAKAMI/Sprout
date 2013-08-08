/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_SWAP_HPP
#define SPROUT_UTILITY_SWAP_HPP

#include <utility>
#include <sprout/config.hpp>

namespace sprout_swap_detail {
	using std::swap;

	template<typename T>
	inline void
	swap_impl(T& a, T& b)
	SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(swap(a, b)))
	{
		return swap(a, b);
	}
}	// namespace sprout_swap_detail

namespace sprout {
	//
	// swap
	//
	template<typename T1, typename T2>
	inline void
	swap(T1& lhs, T2& rhs)
	SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout_swap_detail::swap_impl(lhs, rhs)))
	{
		return sprout_swap_detail::swap_impl(lhs, rhs);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_SWAP_HPP
