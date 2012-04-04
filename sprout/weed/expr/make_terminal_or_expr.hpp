#ifndef SPROUT_WEED_EXPR_MAKE_TERMINAL_OR_EXPR_HPP
#define SPROUT_WEED_EXPR_MAKE_TERMINAL_OR_EXPR_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/weed/expr/make_terminal.hpp>
#include <sprout/weed/traits/expr/is_expr.hpp>
#include <sprout/weed/traits/expr/terminal_or_expr_of.hpp>
#include <sprout/weed/detail/uncvref.hpp>

namespace sprout {
	namespace weed {
		//
		// make_terminal_or_expr
		//
		template<typename Arg>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::weed::traits::is_expr<
				typename sprout::weed::detail::uncvref<Arg>::type
			>::value,
			typename sprout::weed::traits::terminal_or_expr_of<Arg>::type
		>::type make_terminal_or_expr(Arg&& arg) {
			return sprout::forward<Arg>(arg);
		}
		template<typename Arg>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::weed::traits::is_expr<
				typename sprout::weed::detail::uncvref<Arg>::type
			>::value,
			typename sprout::weed::traits::terminal_or_expr_of<Arg>::type
		>::type make_terminal_or_expr(Arg&& arg) {
			return sprout::weed::make_terminal(sprout::forward<Arg>(arg));
		}
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_EXPR_MAKE_TERMINAL_OR_EXPR_HPP
