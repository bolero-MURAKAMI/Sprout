/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_CONTEXT_PARSE_CONTEXT_TERMINAL_OPERATOR_MEM_PTR_HPP
#define SPROUT_WEED_CONTEXT_PARSE_CONTEXT_TERMINAL_OPERATOR_MEM_PTR_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/weed/eval_result.hpp>
#include <sprout/weed/expr/tag.hpp>
#include <sprout/weed/expr/eval.hpp>
#include <sprout/weed/attr_cnv/results/mem_ptr.hpp>
#include <sprout/weed/attr_cnv/mem_ptr.hpp>
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
					sprout::weed::tag::mem_ptr
				>::value
			>::type
		> {
		private:
			typedef sprout::weed::parse_context<Iterator> context_type;
			typedef typename sprout::tuples::tuple_element<0, typename Expr::args_type>::type expr1_type;
			typedef typename sprout::tuples::tuple_element<1, typename Expr::args_type>::type expr2_type;
		public:
			typedef typename sprout::weed::attr_cnv::results::mem_ptr<
				typename sprout::weed::traits::attribute_of<expr1_type, Iterator, context_type>::type,
				typename sprout::tuples::tuple_element<0, typename expr2_type::args_type>::type
			>::type attribute_type;
			typedef sprout::weed::eval_result<context_type, Iterator, attribute_type> result_type;
		private:
			template<typename Result1>
			SPROUT_CONSTEXPR result_type call_1(
				typename Expr::args_type const& args,
				context_type const& ctx,
				Result1 const& res
				) const
			{
				return res.success()
					? result_type(
						true,
						res.current(),
						sprout::weed::attr_cnv::mem_ptr(
							res.attr(), sprout::tuples::get<0>(sprout::tuples::get<1>(args).args())
							),
						context_type(ctx, res.current())
						)
					: result_type(false, ctx.begin(), attribute_type(), ctx)
					;
			}
			SPROUT_CONSTEXPR result_type call(
				typename Expr::args_type const& args,
				context_type const& ctx
				) const
			{
				return call_1(args, ctx, sprout::weed::eval(sprout::tuples::get<0>(args), ctx));
			}
		public:
			SPROUT_CONSTEXPR result_type operator()(
				Expr const& expr,
				context_type const& ctx
				) const
			{
				return call(expr.args(), ctx);
			}
		};
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_CONTEXT_PARSE_CONTEXT_TERMINAL_OPERATOR_MEM_PTR_HPP
