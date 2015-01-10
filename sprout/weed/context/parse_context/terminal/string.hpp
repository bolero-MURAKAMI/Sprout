/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_CONTEXT_PARSE_CONTEXT_TERMINAL_STRING_HPP
#define SPROUT_WEED_CONTEXT_PARSE_CONTEXT_TERMINAL_STRING_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/begin.hpp>
#include <sprout/container/end.hpp>
#include <sprout/container/size.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/equal.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/weed/eval_result.hpp>
#include <sprout/weed/expr/tag.hpp>
#include <sprout/weed/traits/type/is_string.hpp>
#include <sprout/weed/traits/expr/tag_of.hpp>
#include <sprout/weed/traits/parser/attribute_of.hpp>
#include <sprout/weed/context/parse_context_fwd.hpp>

namespace sprout {
	namespace weed {
		//
		// parse_context::eval
		//
		template<typename Iterator>
		template<typename Expr>
		struct parse_context<Iterator>::eval<
			Expr,
			typename std::enable_if<
				std::is_same<
					typename sprout::weed::traits::tag_of<Expr>::type,
					sprout::weed::tag::terminal
				>::value
				&& sprout::weed::traits::is_string<
					typename sprout::tuples::tuple_element<0, typename Expr::args_type>::type
				>::value
			>::type
		> {
		private:
			typedef sprout::weed::parse_context<Iterator> context_type;
		public:
			typedef sprout::weed::unused attribute_type;
			typedef sprout::weed::eval_result<context_type, Iterator, attribute_type> result_type;
		private:
			template<typename Arg>
			SPROUT_CONSTEXPR result_type call(
				Arg const& arg,
				context_type const& ctx
				) const
			{
				return sprout::distance(ctx.begin(), ctx.end()) >= sprout::size(arg)
					&&sprout::equal(sprout::begin(arg), sprout::end(arg), ctx.begin())
					? result_type(
						true,
						sprout::next(ctx.begin(), sprout::size(arg)),
						attribute_type(),
						context_type(ctx, sprout::next(ctx.begin(), sprout::size(arg)))
						)
					: result_type(false, ctx.begin(), attribute_type(), ctx)
					;
			}
		public:
			SPROUT_CONSTEXPR result_type operator()(
				Expr const& expr,
				context_type const& ctx
				) const
			{
				return call(sprout::tuples::get<0>(expr.args()), ctx);
			}
		};
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_CONTEXT_PARSE_CONTEXT_TERMINAL_STRING_HPP
