/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_EXPR_MAKE_EXPR_HPP
#define SPROUT_WEED_EXPR_MAKE_EXPR_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/weed/expr/make_terminal_or_expr.hpp>
#include <sprout/weed/traits/expr/expr_of.hpp>

namespace sprout {
	namespace weed {
		//
		// make_expr
		//
		template<typename Tag, typename... Args>
		inline SPROUT_CONSTEXPR typename sprout::weed::traits::expr_of<Tag, Args...>::type
		make_expr(Args&&... args) {
			return typename sprout::weed::traits::expr_of<Tag, Args...>::type(
				sprout::weed::make_terminal_or_expr(sprout::forward<Args>(args))...
				);
		}
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_EXPR_MAKE_EXPR_HPP
