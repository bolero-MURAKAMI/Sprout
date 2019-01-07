/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_PARSER_DIRECTIVE_AS_TUPLE_HPP
#define SPROUT_WEED_PARSER_DIRECTIVE_AS_TUPLE_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/weed/parser_result.hpp>
#include <sprout/weed/expr/make_terminal_or_expr.hpp>
#include <sprout/weed/expr/eval.hpp>
#include <sprout/weed/parser/parser_base.hpp>
#include <sprout/weed/traits/type/is_unused.hpp>
#include <sprout/weed/traits/expr/terminal_or_expr_of.hpp>
#include <sprout/weed/traits/parser/attribute_of.hpp>

namespace sprout {
	namespace weed {
		//
		// as_tuple_p
		//
		template<typename Parser>
		struct as_tuple_p
			: public sprout::weed::parser_base
		{
		public:
			template<typename Context, typename Iterator>
			struct attribute {
			private:
				typedef typename sprout::weed::traits::attribute_of<Parser, Iterator, Context>::type attr_type;
			private:
				static_assert(!sprout::weed::traits::is_unused<attr_type>::value, "invalid attribute : unused");
			public:
				typedef sprout::tuples::tuple<attr_type> type;
			};
			template<typename Context, typename Iterator>
			struct result
				: public sprout::identity<sprout::weed::parser_result<Iterator, typename attribute<Context, Iterator>::type> >
			{};
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
					? result_type(true, res.current(), attribute_type(res.attr()))
					: result_type(false, first, attribute_type())
					;
			}
		public:
			SPROUT_CONSTEXPR as_tuple_p() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
			explicit SPROUT_CONSTEXPR as_tuple_p(
				Parser const& p
				)
				: expr_(sprout::weed::make_terminal_or_expr(p))
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
		// as_tuple_d
		//
		struct as_tuple_d {
		public:
			template<typename Parser>
			SPROUT_CONSTEXPR sprout::weed::as_tuple_p<Parser> operator[](Parser const& p) const {
				return sprout::weed::as_tuple_p<Parser>(p);
			}
		};
		//
		// as_tuple
		//
		SPROUT_CONSTEXPR sprout::weed::as_tuple_d as_tuple = sprout::weed::as_tuple_d();
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_PARSER_DIRECTIVE_AS_TUPLE_HPP
