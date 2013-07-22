#ifndef SPROUT_WEED_PARSER_DIRECTIVE_REPLACE_HPP
#define SPROUT_WEED_PARSER_DIRECTIVE_REPLACE_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/type_traits/identity.hpp>
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
		// replace_p
		//
		template<typename Parser, typename T>
		struct replace_p
			: public sprout::weed::parser_base
		{
		public:
			typedef T value_type;
			template<typename Context, typename Iterator>
			struct attribute
				: public sprout::identity<value_type>
			{};
			template<typename Context, typename Iterator>
			struct result
				: public sprout::identity<sprout::weed::parser_result<Iterator, typename attribute<Context, Iterator>::type> >
			{};
		private:
			typedef typename sprout::weed::traits::terminal_or_expr_of<Parser>::type expr_type;
		private:
			expr_type expr_;
			value_type value_;
		private:
			template<typename Context, typename Iterator, typename Result>
			SPROUT_CONSTEXPR typename result<Context, Iterator>::type call(
				Iterator first,
				Result const& res
				) const
			{
				typedef typename result<Context, Iterator>::type result_type;
				return res.success()
					? result_type(true, res.current(), value_)
					: result_type(false, first, value_)
					;
			}
		public:
			replace_p() = default;
			SPROUT_CONSTEXPR replace_p(
				Parser const& p,
				value_type const& value
				)
				: expr_(sprout::weed::make_terminal_or_expr(p))
				, value_(value)
			{}
			template<typename Context, typename Iterator>
			SPROUT_CONSTEXPR typename result<Context, Iterator>::type operator()(
				Iterator first, Iterator,
				Context const& ctx
				) const
			{
				return call<Context>(first, sprout::weed::eval(expr_, ctx));
			}
		};
		//
		// replace_d
		//
		template<typename T>
		struct replace_d {
		public:
			typedef T value_type;
		private:
			value_type value_;
		public:
			explicit SPROUT_CONSTEXPR replace_d(value_type const& value)
				: value_(value)
			{}
			template<typename Parser>
			SPROUT_CONSTEXPR sprout::weed::replace_p<Parser, value_type> operator[](Parser const& p) const {
				return sprout::weed::replace_p<Parser, value_type>(p, value_);
			}
		};
		//
		// replace_g
		//
		struct replace_g {
		public:
			template<typename T>
			SPROUT_CONSTEXPR sprout::weed::replace_d<T> operator()(T const& value) const {
				return sprout::weed::replace_d<T>(value);
			}
		};
		//
		// replace
		//
		SPROUT_CONSTEXPR sprout::weed::replace_g replace = sprout::weed::replace_g();
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_PARSER_DIRECTIVE_REPLACE_HPP
