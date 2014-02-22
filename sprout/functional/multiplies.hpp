/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  Copyright (C) 2011 RiSK (sscrisk)
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_MULTIPLIES_HPP
#define SPROUT_FUNCTIONAL_MULTIPLIES_HPP

#include <utility>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {

	// 20.8.4 Arithmetic operations
	template<typename T = void>
	struct multiplies {
	public:
		typedef T first_argument_type;
		typedef T second_argument_type;
		typedef T result_type;
	public:
		SPROUT_CONSTEXPR T operator()(T const& x, T const& y) const {
				return x * y;
		}
	};

	template<>
	struct multiplies<void> {
	public:
		typedef void is_transparent;
	public:
		template<typename T, typename U>
		SPROUT_CONSTEXPR decltype(std::declval<T>() * std::declval<U>())
		operator()(T&& x, U&& y)
		const SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(std::declval<T>() * std::declval<U>()))
		{
			return SPROUT_FORWARD(T, x) * SPROUT_FORWARD(U, y);
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_MULTIPLIES_HPP
