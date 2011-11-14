#ifndef SPROUT_WEED_OPERATOR_MINUS_HPP
#define SPROUT_WEED_OPERATOR_MINUS_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/weed/expr/tag.hpp>
#include <sprout/weed/expr/make_expr.hpp>
#include <sprout/weed/traits/expr/expr_of.hpp>
#include <sprout/weed/traits/parser/is_parser.hpp>
#include <sprout/weed/detail/uncvref.hpp>

namespace sprout {
	namespace weed {
		//
		// operator-
		//
		template<
			typename Arg1,
			typename Arg2,
			typename = typename std::enable_if<
				sprout::weed::traits::is_parser<
					typename sprout::weed::detail::uncvref<Arg1>::type
				>::value
				&& sprout::weed::traits::is_parser<
					typename sprout::weed::detail::uncvref<Arg2>::type
				>::value
			>::type
		>
		SPROUT_CONSTEXPR inline typename sprout::weed::traits::expr_of<
			sprout::weed::tag::minus,
			Arg1,
			Arg2
		>::type operator-(Arg1&& arg1, Arg2&& arg2) {
			return sprout::weed::make_expr<sprout::weed::tag::minus>(
				sprout::forward<Arg1>(arg1),
				sprout::forward<Arg2>(arg2)
				);
		}
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_OPERATOR_MINUS_HPP
