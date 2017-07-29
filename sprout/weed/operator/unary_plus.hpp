/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_OPERATOR_UNARY_PLUS_HPP
#define SPROUT_WEED_OPERATOR_UNARY_PLUS_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/weed/expr/tag.hpp>
#include <sprout/weed/expr/make_expr.hpp>
#include <sprout/weed/traits/expr/expr_of.hpp>
#include <sprout/weed/traits/parser/is_parser.hpp>

namespace sprout {
	namespace weed {
		//
		// operator+
		//
		template<
			typename Arg,
			typename = typename std::enable_if<
				sprout::weed::traits::is_parser<
					typename std::remove_reference<Arg>::type
				>::value
			>::type
		>
		inline SPROUT_CONSTEXPR typename sprout::weed::traits::expr_of<
			sprout::weed::tag::unary_plus,
			Arg
		>::type operator+(Arg&& arg) {
			return sprout::weed::make_expr<sprout::weed::tag::unary_plus>(
				SPROUT_FORWARD(Arg, arg)
				);
		}
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_OPERATOR_UNARY_PLUS_HPP
