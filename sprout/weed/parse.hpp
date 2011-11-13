#ifndef SPROUT_WEED_PARSE_HPP
#define SPROUT_WEED_PARSE_HPP

#include <sprout/config.hpp>
#include <sprout/weed/expr/make_terminal_or_expr.hpp>
#include <sprout/weed/context/parse_context.hpp>
#include <sprout/weed/traits/expr/terminal_or_expr_of.hpp>

namespace sprout {
	namespace weed {
		//
		// parse
		//
		template<typename Iterator, typename Parser>
		SPROUT_CONSTEXPR inline typename sprout::weed::parse_context<Iterator>::template eval<
			typename sprout::weed::traits::terminal_or_expr_of<Parser>::type
		>::result_type::presult_type parse(
			Iterator first,
			Iterator last,
			Parser const& parser
			)
		{
			return sprout::weed::eval(
				sprout::weed::make_terminal_or_expr(parser),
				sprout::weed::parse_context<Iterator>(first, last)
				).presult()
				;
		}
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_PARSE_HPP
