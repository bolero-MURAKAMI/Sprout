#ifndef SPROUT_WEED_CONTEXT_PARSE_CONTEXT_TERMINAL_PARSER_HPP
#define SPROUT_WEED_CONTEXT_PARSE_CONTEXT_TERMINAL_PARSER_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/weed/eval_result.hpp>
#include <sprout/weed/expr/tag.hpp>
#include <sprout/weed/traits/type/is_char_type.hpp>
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
				&& !sprout::weed::traits::is_char_type<
					typename sprout::tuples::tuple_element<0, typename Expr::args_type>::type
				>::value
				&& !sprout::weed::traits::is_string<
					typename sprout::tuples::tuple_element<0, typename Expr::args_type>::type
				>::value
			>::type
		> {
		private:
			typedef sprout::weed::parse_context<Iterator> context_type;
			typedef typename sprout::tuples::tuple_element<0, typename Expr::args_type>::type parser_type;
		public:
			typedef typename sprout::weed::traits::attribute_of<Expr, Iterator, context_type>::type attribute_type;
			typedef sprout::weed::eval_result<context_type, Iterator, attribute_type> result_type;
		private:
			template<typename Result>
			SPROUT_CONSTEXPR result_type call(
				Result const& res,
				context_type const& ctx
				) const
			{
				return result_type(res, context_type(ctx, res.current()));
			}
		public:
			SPROUT_CONSTEXPR result_type operator()(
				Expr const& expr,
				context_type const& ctx
				) const
			{
				return call(
					sprout::tuples::get<0>(expr.args())
						.template operator()(ctx.begin(), ctx.end(), ctx),
					ctx
					);
			}
		};
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_CONTEXT_PARSE_CONTEXT_TERMINAL_PARSER_HPP
