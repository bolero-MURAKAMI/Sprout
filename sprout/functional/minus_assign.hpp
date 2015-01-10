/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_MINUS_ASSIGN_HPP
#define SPROUT_FUNCTIONAL_MINUS_ASSIGN_HPP

#include <utility>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	//
	// minus_assign
	//
	template<typename T = void>
	struct minus_assign;
	template<>
	struct minus_assign<void> {
	public:
		typedef void is_transparent;
	public:
		template<typename T, typename U>
		SPROUT_CONSTEXPR decltype(std::declval<T>() -= std::declval<U>())
		operator()(T&& x, U&& y)
		const SPROUT_NOEXCEPT_IF_EXPR(std::declval<T>() -= std::declval<U>())
		{
			return SPROUT_FORWARD(T, x) -= SPROUT_FORWARD(U, y);
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_MINUS_ASSIGN_HPP
