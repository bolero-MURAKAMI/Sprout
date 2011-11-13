#ifndef SPROUT_WEED_PARSER_DIRECTIVE_OMIT_HPP
#define SPROUT_WEED_PARSER_DIRECTIVE_OMIT_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/weed/unused.hpp>
#include <sprout/weed/parser_result.hpp>
#include <sprout/weed/expr/make_terminal_or_expr.hpp>
#include <sprout/weed/expr/eval.hpp>
#include <sprout/weed/parser/parser_base.hpp>
#include <sprout/weed/traits/expr/terminal_or_expr_of.hpp>
#include <sprout/weed/traits/parser/attribute_of.hpp>

namespace sprout {
	namespace weed {
		//
		// omit_p
		//
		template<typename Parser>
		struct omit_p
			: public sprout::weed::parser_base
		{
		public:
			template<typename Context, typename Iterator>
			struct attribute {
			public:
				typedef sprout::weed::unused type;
			};
			template<typename Context, typename Iterator>
			struct result {
			public:
				typedef sprout::weed::parser_result<Iterator, typename attribute<Context, Iterator>::type> type;
			};
		private:
			typedef typename sprout::weed::traits::terminal_or_expr_of<Parser>::type expr_type;
		private:
			expr_type expr_;
		private:
			template<typename Context, typename Iterator, typename Result>
			SPROUT_CONSTEXPR typename result<Context, Iterator>::type call(
				Iterator first,
				Result const& res
				) const
			{
				typedef typename result<Context, Iterator>::type result_type;
				typedef typename attribute<Context, Iterator>::type attribute_type;
				return res.success()
					? result_type(true, res.current(), attribute_type())
					: result_type(false, first, attribute_type())
					;
			}
		public:
			omit_p() = default;
			SPROUT_CONSTEXPR explicit omit_p(
				Parser const& p
				)
				: expr_(sprout::weed::make_terminal_or_expr(p))
			{}
			template<typename Context, typename Iterator>
			SPROUT_CONSTEXPR typename result<Context, Iterator>::type operator()(
				Iterator first,
				Iterator last,
				Context const& ctx
				) const
			{
				return call<Context>(first, sprout::weed::eval(expr_, ctx));
			}
		};
		//
		// omit_d
		//
		struct omit_d {
		public:
			template<typename Parser>
			SPROUT_CONSTEXPR sprout::weed::omit_p<Parser> operator[](Parser const& p) const {
				return sprout::weed::omit_p<Parser>(p);
			}
		};
		//
		// omit
		//
		SPROUT_CONSTEXPR sprout::weed::omit_d omit = sprout::weed::omit_d();
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_PARSER_DIRECTIVE_OMIT_HPP
