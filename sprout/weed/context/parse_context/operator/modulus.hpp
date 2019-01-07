/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_CONTEXT_PARSE_CONTEXT_TERMINAL_OPERATOR_MODULUS_HPP
#define SPROUT_WEED_CONTEXT_PARSE_CONTEXT_TERMINAL_OPERATOR_MODULUS_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/weed/eval_result.hpp>
#include <sprout/weed/limited.hpp>
#include <sprout/weed/expr/tag.hpp>
#include <sprout/weed/expr/eval.hpp>
#include <sprout/weed/attr_cnv/results/modulus.hpp>
#include <sprout/weed/attr_cnv/modulus.hpp>
#include <sprout/weed/traits/expr/tag_of.hpp>
#include <sprout/weed/traits/parser/attribute_of.hpp>
#include <sprout/weed/traits/parser/limit_of.hpp>
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
					sprout::weed::tag::modulus
				>::value
			>::type
		> {
		private:
			typedef sprout::weed::parse_context<Iterator> context_type;
			typedef typename sprout::tuples::tuple_element<0, typename Expr::args_type>::type expr1_type;
			typedef typename sprout::tuples::tuple_element<1, typename Expr::args_type>::type expr2_type;
			typedef typename sprout::weed::traits::limit_of<expr1_type, Iterator, context_type>::type limit;
			typedef typename sprout::weed::traits::attribute_of<expr1_type, Iterator, context_type>::type attr_type;
		public:
			typedef typename sprout::weed::attr_cnv::results::modulus<
				limit::value,
				typename sprout::weed::traits::attribute_of<expr1_type, Iterator, context_type>::type
			>::type attribute_type;
			typedef sprout::weed::eval_result<context_type, Iterator, attribute_type> result_type;
		private:
			template<typename Result, typename... Attrs>
			SPROUT_CONSTEXPR result_type call_1(
				expr1_type const& expr1,
				expr2_type const& expr2,
				context_type const& ctx,
				sprout::weed::limited::category limited_category,
				Result const& res,
				Attrs const&... attrs
				) const
			{
				return res.success()
					? call(
						expr1,
						expr2,
						res.ctx(),
						limited_category,
						sprout::weed::eval(expr1, res.ctx()),
						attrs...
						)
					: result_type(
						true,
						ctx.begin(),
						sprout::weed::attr_cnv::modulus<limit::value, attr_type>(attrs...),
						ctx
						)
					;
			}
			template<typename Result, typename Head, typename... Attrs>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Attrs) + 1 == limit::value,
				result_type
			>::type call(
				expr1_type const& expr1,
				expr2_type const& expr2,
				context_type const& ctx,
				sprout::weed::limited::category limited_category,
				Result const& res,
				Head const& head,
				Attrs const&... attrs
				) const
			{
				return res.success()
					? limited_category == sprout::weed::limited::discard
						? call_1(
							expr1,
							expr2,
							res.ctx(),
							limited_category,
							sprout::weed::eval(expr2, res.ctx()),
							head,
							attrs...
							)
						: call_1(
							expr1,
							expr2,
							res.ctx(),
							limited_category,
							sprout::weed::eval(expr2, res.ctx()),
							attrs...,
							res.attr()
							)
					: result_type(
						true,
						ctx.begin(),
						sprout::weed::attr_cnv::modulus<limit::value, attr_type>(head, attrs...),
						ctx
						)
					;
			}
			template<typename Result, typename Head, typename... Attrs>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Attrs) + 2 == limit::value,
				result_type
			>::type call(
				expr1_type const& expr1,
				expr2_type const& expr2,
				context_type const& ctx,
				sprout::weed::limited::category limited_category,
				Result const& res,
				Head const& head,
				Attrs const&... attrs
				) const
			{
				return res.success()
					? limited_category != sprout::weed::limited::stopover
						? call_1(
							expr1,
							expr2,
							res.ctx(),
							limited_category,
							sprout::weed::eval(expr2, res.ctx()),
							head,
							attrs...,
							res.attr()
							)
						: result_type(
							true,
							res.current(),
							sprout::weed::attr_cnv::modulus<limit::value, attr_type>(head, attrs..., res.attr()),
							res.ctx()
							)
					: result_type(
						true,
						ctx.begin(),
						sprout::weed::attr_cnv::modulus<limit::value, attr_type>(head, attrs...),
						ctx
						)
					;
			}
			template<typename Result, typename Head, typename... Attrs>
			SPROUT_CONSTEXPR typename std::enable_if<
				(sizeof...(Attrs) + 2 < limit::value),
				result_type
			>::type call(
				expr1_type const& expr1,
				expr2_type const& expr2,
				context_type const& ctx,
				sprout::weed::limited::category limited_category,
				Result const& res,
				Head const& head,
				Attrs const&... attrs
				) const
			{
				return res.success()
					? call_1(
						expr1,
						expr2,
						res.ctx(),
						limited_category,
						sprout::weed::eval(expr2, res.ctx()),
						head,
						attrs...,
						res.attr()
						)
					: result_type(
						true,
						ctx.begin(),
						sprout::weed::attr_cnv::modulus<limit::value, attr_type>(head, attrs...),
						ctx
						)
					;
			}
			template<typename Result>
			SPROUT_CONSTEXPR result_type call_inf_1(
				expr1_type const& expr1,
				expr2_type const& expr2,
				context_type const& ctx,
				Result const& res
				) const
			{
				return res.success()
					? call_inf(expr1, expr2, res.ctx(), sprout::weed::eval(expr1, res.ctx()))
					: result_type(true, ctx.begin(), attribute_type(), ctx)
					;
			}
			template<typename Result>
			SPROUT_CONSTEXPR result_type call_inf(
				expr1_type const& expr1,
				expr2_type const& expr2,
				context_type const& ctx,
				Result const& res
				) const
			{
				return res.success()
					? call_inf_1(expr1, expr2, res.ctx(), sprout::weed::eval(expr2, res.ctx()))
					: result_type(true, ctx.begin(), attribute_type(), ctx)
					;
			}
			template<bool Infinity, typename Result>
			SPROUT_CONSTEXPR typename std::enable_if<
				Infinity,
				result_type
			>::type call(
				expr1_type const& expr1,
				expr2_type const& expr2,
				context_type const& ctx,
				Result const& res
				) const
			{
				return res.success()
					? call_inf_1(expr1, expr2, res.ctx(), sprout::weed::eval(expr2, res.ctx()))
					: result_type(false, ctx.begin(), attribute_type(), ctx)
					;
			}
			template<bool Infinity, typename Result>
			SPROUT_CONSTEXPR typename std::enable_if<
				!Infinity,
				result_type
			>::type call(
				expr1_type const& expr1,
				expr2_type const& expr2,
				context_type const& ctx,
				Result const& res
				) const
			{
				return res.success()
					? call_1(
						expr1,
						expr2,
						res.ctx(),
						sprout::tuples::get<0>(expr1.args()).limited_category(),
						sprout::weed::eval(expr2, res.ctx()), res.attr()
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
				return call<limit::value == std::size_t(-1)>(
					sprout::tuples::get<0>(expr.args()),
					sprout::tuples::get<1>(expr.args()),
					ctx,
					sprout::weed::eval(sprout::tuples::get<0>(expr.args()), ctx)
					);
			}
		};
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_CONTEXT_PARSE_CONTEXT_TERMINAL_OPERATOR_MODULUS_HPP
