/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DETAIL_FUNCTIONAL_CONST_SUBSCRIPT_HPP
#define SPROUT_DETAIL_FUNCTIONAL_CONST_SUBSCRIPT_HPP

#include <utility>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/as_const.hpp>
#include <sprout/functional/transparent.hpp>

namespace sprout {
	namespace detail {
		template<typename T = void>
		struct const_subscript;
		template<>
		struct const_subscript<void>
			: public sprout::transparent<>
		{
		public:
			template<typename T, typename U>
			SPROUT_CONSTEXPR decltype(std::declval<T>()[std::declval<U>()])
			operator()(T&& x, U&& y)
			const SPROUT_NOEXCEPT_IF_EXPR(const_cast<decltype(std::declval<T>()[std::declval<U>()])>(sprout::as_const(std::declval<T>())[std::declval<U>()]))
			{
				return const_cast<decltype(std::declval<T>()[std::declval<U>()])>(sprout::as_const(x)[SPROUT_FORWARD(U, y)]);
			}
		};
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_FUNCTIONAL_CONST_SUBSCRIPT_HPP
