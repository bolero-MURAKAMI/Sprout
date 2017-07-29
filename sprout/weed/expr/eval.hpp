/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_EXPR_EVAL_HPP
#define SPROUT_WEED_EXPR_EVAL_HPP

#include <sprout/config.hpp>
#include <sprout/weed/expr/make_terminal_or_expr.hpp>
#include <sprout/weed/traits/expr/terminal_or_expr_of.hpp>

namespace sprout {
	namespace weed {
		//
		// eval
		//
		template<typename Expr, typename Context>
		inline SPROUT_CONSTEXPR typename Context::template eval<
			typename sprout::weed::traits::terminal_or_expr_of<Expr>::type
		>::result_type eval(
			Expr const& expr,
			Context const& ctx
			)
		{
			typedef typename Context::template eval<
				typename sprout::weed::traits::terminal_or_expr_of<Expr>::type
			> eval_type;
			return eval_type()(
				sprout::weed::make_terminal_or_expr(expr),
				ctx
				);
		}
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_EXPR_EVAL_HPP
