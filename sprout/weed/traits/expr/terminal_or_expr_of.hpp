#ifndef SPROUT_WEED_TRAITS_EXPR_TERMINAL_OR_EXPR_OF_HPP
#define SPROUT_WEED_TRAITS_EXPR_TERMINAL_OR_EXPR_OF_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/weed/traits/expr/is_expr.hpp>
#include <sprout/weed/traits/expr/terminal_of.hpp>
#include <sprout/weed/detail/uncvref.hpp>

namespace sprout {
	namespace weed {
		namespace traits {
			//
			// terminal_or_expr_of
			//
			template<typename Arg>
			struct terminal_or_expr_of {
			public:
				typedef typename std::conditional<
					sprout::weed::traits::is_expr<
						typename sprout::weed::detail::uncvref<Arg>::type
					>::value,
					typename sprout::weed::detail::uncvref<Arg>::type,
					typename sprout::weed::traits::terminal_of<Arg>::type
				>::type type;
			};
		}	// namespace traits
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_TRAITS_EXPR_TERMINAL_OR_EXPR_OF_HPP
