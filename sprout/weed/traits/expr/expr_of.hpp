#ifndef SPROUT_WEED_TRAITS_EXPR_EXPR_OF_HPP
#define SPROUT_WEED_TRAITS_EXPR_EXPR_OF_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/weed/expr/expr.hpp>
#include <sprout/weed/traits/expr/terminal_or_expr_of.hpp>
#include <sprout/weed/detail/uncvref.hpp>

namespace sprout {
	namespace weed {
		namespace traits {
			//
			// expr_of
			//
			template<typename Tag, typename... Args>
			struct expr_of {
			public:
				typedef sprout::weed::expr<
					Tag,
					typename sprout::weed::traits::terminal_or_expr_of<
						typename sprout::weed::detail::uncvref<Args>::type
					>::type...
				> type;
			};
		}	// namespace traits
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_TRAITS_EXPR_EXPR_OF_HPP
