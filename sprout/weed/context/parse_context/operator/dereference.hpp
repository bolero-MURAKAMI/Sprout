#ifndef SPROUT_WEED_CONTEXT_PARSE_CONTEXT_TERMINAL_OPERATOR_DEREFERENCE_HPP
#define SPROUT_WEED_CONTEXT_PARSE_CONTEXT_TERMINAL_OPERATOR_DEREFERENCE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/weed/eval_result.hpp>
#include <sprout/weed/limited.hpp>
#include <sprout/weed/expr/tag.hpp>
#include <sprout/weed/expr/eval.hpp>
#include <sprout/weed/attr_cnv/times.hpp>
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
					sprout::weed::tag::dereference
				>::value
			>::type
		> {
		private:
			typedef sprout::weed::parse_context<Iterator> context_type;
			typedef typename sprout::tuples::tuple_element<0, typename Expr::args_type>::type expr_type;
			typedef typename sprout::weed::traits::limit_of<expr_type, Iterator, context_type>::type limit;
			typedef typename sprout::weed::traits::attribute_of<expr_type, Iterator, context_type>::type attr_type;
		public:
			typedef typename sprout::weed::traits::attribute_of<Expr, Iterator, context_type>::type attribute_type;
			typedef sprout::weed::eval_result<context_type, Iterator, attribute_type> result_type;
		private:
			template<typename Result, typename Head, typename... Attrs>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Attrs) + 1 == limit::value,
				result_type
			>::type call(
				expr_type const& expr,
				context_type const& ctx,
				sprout::weed::limited::category limited_category,
				Result const& res,
				Head const& head,
				Attrs const&... attrs
				) const
			{
				return res.success()
					? limited_category == sprout::weed::limited::discard
						? call(
							expr,
							res.ctx(),
							limited_category,
							sprout::weed::eval(expr, res.ctx()),
							head,
							attrs...
							)
						: call(
							expr,
							res.ctx(),
							limited_category,
							sprout::weed::eval(expr, res.ctx()),
							attrs...,
							res.attr()
							)
					: result_type(
						true,
						ctx.begin(),
						sprout::weed::attr_cnv::times<limit::value, attr_type>(head, attrs...),
						ctx
						)
					;
			}
			template<typename Result, typename Head, typename... Attrs>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Attrs) + 2 == limit::value,
				result_type
			>::type call(
				expr_type const& expr,
				context_type const& ctx,
				sprout::weed::limited::category limited_category,
				Result const& res,
				Head const& head,
				Attrs const&... attrs
				) const
			{
				return res.success()
					? limited_category != sprout::weed::limited::stopover
						? call(
							expr,
							res.ctx(),
							limited_category,
							sprout::weed::eval(expr, res.ctx()),
							head,
							attrs...,
							res.attr()
							)
						: result_type(
							true,
							res.current(),
							sprout::weed::attr_cnv::times<limit::value, attr_type>(head, attrs..., res.attr()),
							res.ctx()
							)
					: result_type(
						true,
						ctx.begin(),
						sprout::weed::attr_cnv::times<limit::value, attr_type>(head, attrs...),
						ctx
						)
					;
			}
			template<typename Result, typename Head, typename... Attrs>
			SPROUT_CONSTEXPR typename std::enable_if<
				(sizeof...(Attrs) + 2 < limit::value),
				result_type
			>::type call(
				expr_type const& expr,
				context_type const& ctx,
				sprout::weed::limited::category limited_category,
				Result const& res,
				Head const& head,
				Attrs const&... attrs
				) const
			{
				return res.success()
					? call(
						expr,
						res.ctx(),
						limited_category,
						sprout::weed::eval(expr, res.ctx()),
						head,
						attrs...,
						res.attr()
						)
					: result_type(
						true,
						ctx.begin(),
						sprout::weed::attr_cnv::times<limit::value, attr_type>(head, attrs...),
						ctx
						)
					;
			}
			template<typename Result>
			SPROUT_CONSTEXPR result_type call_inf(
				expr_type const& expr,
				context_type const& ctx,
				Result const& res
				) const
			{
				return res.success()
					? call_inf(expr, res.ctx(), sprout::weed::eval(expr, res.ctx()))
					: result_type(true, ctx.begin(), attribute_type(), ctx)
					;
			}
			template<bool Infinity, typename Result>
			SPROUT_CONSTEXPR typename std::enable_if<
				Infinity,
				result_type
			>::type call(
				expr_type const& expr,
				context_type const& ctx,
				Result const& res
				) const
			{
				return res.success()
					? call_inf(expr, res.ctx(), sprout::weed::eval(expr, res.ctx()))
					: result_type(true, ctx.begin(), attribute_type(), ctx)
					;
			}
			template<bool Infinity, typename Result>
			SPROUT_CONSTEXPR typename std::enable_if<
				!Infinity,
				result_type
			>::type call(
				expr_type const& expr,
				context_type const& ctx,
				Result const& res
				) const
			{
				return res.success()
					? call(
						expr,
						res.ctx(),
						sprout::tuples::get<0>(expr.args()).limited_category(),
						sprout::weed::eval(expr, res.ctx()),
						res.attr()
						)
					: result_type(true, ctx.begin(), attribute_type(), ctx)
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
					ctx,
					sprout::weed::eval(sprout::tuples::get<0>(expr.args()), ctx)
					);
			}
		};
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_CONTEXT_PARSE_CONTEXT_TERMINAL_OPERATOR_DEREFERENCE_HPP
