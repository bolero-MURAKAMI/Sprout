/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_PARSE_HPP
#define SPROUT_WEED_PARSE_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/weed/expr/make_terminal_or_expr.hpp>
#include <sprout/weed/context/parse_context.hpp>
#include <sprout/weed/traits/expr/terminal_or_expr_of.hpp>

namespace sprout {
	namespace weed {
		//
		// parse
		//
		template<typename Iterator, typename Parser>
		inline SPROUT_CONSTEXPR typename sprout::weed::parse_context<
			Iterator
		>::template eval<
			typename sprout::weed::traits::terminal_or_expr_of<Parser>::type
		>::result_type::presult_type
		parse(Iterator first, Iterator last, Parser const& parser) {
			return sprout::weed::eval(
				sprout::weed::make_terminal_or_expr(parser),
				sprout::weed::parse_context<Iterator>(first, last)
				).presult()
				;
		}
		template<typename Range, typename Parser>
		inline SPROUT_CONSTEXPR typename sprout::weed::parse_context<
			typename sprout::container_traits<Range>::const_iterator
		>::template eval<
			typename sprout::weed::traits::terminal_or_expr_of<Parser>::type
		>::result_type::presult_type
		parse(Range const& range, Parser const& parser) {
			return sprout::weed::parse(sprout::begin(range), sprout::end(range), parser);
		}

		//
		// parse_range
		//
		template<typename Range, typename Parser>
		inline SPROUT_CONSTEXPR typename sprout::weed::parse_context<
			typename sprout::container_traits<Range>::const_iterator
		>::template eval<
			typename sprout::weed::traits::terminal_or_expr_of<Parser>::type
		>::result_type::presult_type
		parse_range(Range const& range, Parser const& parser) {
			return sprout::weed::parse(range, parser);
		}
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_PARSE_HPP
