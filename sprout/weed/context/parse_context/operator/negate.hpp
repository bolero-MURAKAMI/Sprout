/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_CONTEXT_PARSE_CONTEXT_TERMINAL_OPERATOR_NEGATE_HPP
#define SPROUT_WEED_CONTEXT_PARSE_CONTEXT_TERMINAL_OPERATOR_NEGATE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/weed/eval_result.hpp>
#include <sprout/weed/expr/tag.hpp>
#include <sprout/weed/expr/eval.hpp>
#include <sprout/weed/attr_cnv/results/negate.hpp>
#include <sprout/weed/attr_cnv/negate.hpp>
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
					sprout::weed::tag::negate
				>::value
			>::type
		> {
		private:
			typedef sprout::weed::parse_context<Iterator> context_type;
			typedef typename sprout::tuples::tuple_element<0, typename Expr::args_type>::type expr_type;
		public:
			typedef typename sprout::weed::attr_cnv::results::negate<
				typename sprout::weed::traits::attribute_of<expr_type, Iterator, context_type>::type
			>::type attribute_type;
			typedef sprout::weed::eval_result<context_type, Iterator, attribute_type> result_type;
		private:
			template<typename Result>
			SPROUT_CONSTEXPR result_type call(
				context_type const& ctx,
				Result const& res
				) const
			{
				return result_type(
					true,
					res.current(),
					sprout::weed::attr_cnv::negate(res.attr(), res.success()),
					res.success() ? context_type(ctx, res.current()) : ctx
					);
			}
		public:
			SPROUT_CONSTEXPR result_type operator()(
				Expr const& expr,
				context_type const& ctx
				) const
			{
				return call(ctx, sprout::weed::eval(sprout::tuples::get<0>(expr.args()), ctx));
			}
		};
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_CONTEXT_PARSE_CONTEXT_TERMINAL_OPERATOR_NEGATE_HPP
