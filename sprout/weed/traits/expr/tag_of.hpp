/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_TRAITS_EXPR_TAG_OF_HPP
#define SPROUT_WEED_TRAITS_EXPR_TAG_OF_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/identity.hpp>
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
			>
				: public sprout::identity<typename Expr::expr_tag>
			{};
		}	// namespace traits
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_TRAITS_EXPR_TAG_OF_HPP
