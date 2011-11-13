#ifndef SPROUT_WEED_TRAITS_EXPR_TAG_OF_HPP
#define SPROUT_WEED_TRAITS_EXPR_TAG_OF_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/weed/traits/expr/is_expr.hpp>

namespace sprout {
	namespace weed {
		namespace traits {
			//
			// tag_of
			//
			template<typename Expr, typename = void>
			struct tag_of;
			template<typename Expr>
			struct tag_of<Expr const>
				: public sprout::weed::traits::tag_of<Expr>
			{};
			template<typename Expr>
			struct tag_of<
				Expr,
				typename std::enable_if<
					sprout::weed::traits::is_expr<Expr>::value
				>::type
			> {
			public:
				typedef typename Expr::expr_tag type;
			};
		}	// namespace traits
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_TRAITS_EXPR_TAG_OF_HPP
