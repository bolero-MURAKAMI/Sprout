/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_EXPR_MAKE_TERMINAL_OR_EXPR_HPP
#define SPROUT_WEED_EXPR_MAKE_TERMINAL_OR_EXPR_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/weed/expr/make_terminal.hpp>
#include <sprout/weed/traits/expr/is_expr.hpp>
#include <sprout/weed/traits/expr/terminal_or_expr_of.hpp>

namespace sprout {
	namespace weed {
		//
		// make_terminal_or_expr
		//
		template<typename Arg>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::weed::traits::is_expr<
				typename std::remove_reference<Arg>::type
			>::value,
			typename sprout::weed::traits::terminal_or_expr_of<Arg>::type
		>::type make_terminal_or_expr(Arg&& arg) {
			return SPROUT_FORWARD(Arg, arg);
		}
		template<typename Arg>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::weed::traits::is_expr<
				typename std::remove_reference<Arg>::type
			>::value,
			typename sprout::weed::traits::terminal_or_expr_of<Arg>::type
		>::type make_terminal_or_expr(Arg&& arg) {
			return sprout::weed::make_terminal(SPROUT_FORWARD(Arg, arg));
		}
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_EXPR_MAKE_TERMINAL_OR_EXPR_HPP
