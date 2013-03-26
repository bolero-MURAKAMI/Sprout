#ifndef SPROUT_WEED_TRAITS_EXPR_TERMINAL_OR_EXPR_OF_HPP
#define SPROUT_WEED_TRAITS_EXPR_TERMINAL_OR_EXPR_OF_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/remove_shallow_cvref.hpp>
#include <sprout/weed/traits/expr/is_expr.hpp>
#include <sprout/weed/traits/expr/terminal_of.hpp>

namespace sprout {
	namespace weed {
		namespace traits {
			//
			// terminal_or_expr_of
			//
			template<typename Arg>
			struct terminal_or_expr_of
				: public std::conditional<
					sprout::weed::traits::is_expr<
						typename std::remove_reference<Arg>::type
					>::value,
					sprout::remove_shallow_cvref<Arg>,
					sprout::weed::traits::terminal_of<Arg>
				>::type
			{};
		}	// namespace traits
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_TRAITS_EXPR_TERMINAL_OR_EXPR_OF_HPP
