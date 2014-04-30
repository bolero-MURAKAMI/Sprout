/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_PARSER_LIM_HPP
#define SPROUT_WEED_PARSER_LIM_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/weed/parser_result.hpp>
#include <sprout/weed/limited.hpp>
#include <sprout/weed/expr/make_terminal_or_expr.hpp>
#include <sprout/weed/expr/eval.hpp>
#include <sprout/weed/parser/parser_base.hpp>
#include <sprout/weed/traits/expr/terminal_or_expr_of.hpp>
#include <sprout/weed/traits/parser/attribute_of.hpp>
#include <sprout/weed/traits/parser/limit_of.hpp>

namespace sprout {
	namespace weed {
		//
		// limit_p
		//
		template<typename Parser, std::size_t Limit>
		struct limit_p
			: public sprout::weed::parser_base
		{
		public:
			SPROUT_STATIC_CONSTEXPR std::size_t limit = Limit;
		public:
			template<typename Context, typename Iterator>
			struct attribute
				: public sprout::weed::traits::attribute_of<Parser, Iterator, Context>
			{};
			template<typename Context, typename Iterator>
			struct result
				: public sprout::identity<sprout::weed::parser_result<Iterator, typename attribute<Context, Iterator>::type> >
			{};
		private:
			typedef typename sprout::weed::traits::terminal_or_expr_of<Parser>::type expr_type;
		private:
			expr_type expr_;
			sprout::weed::limited::category limited_category_;
		public:
			SPROUT_CONSTEXPR limit_p() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
			explicit SPROUT_CONSTEXPR limit_p(
				Parser const& p,
				sprout::weed::limited::category limited_category = sprout::weed::limited::discard
				)
				: expr_(sprout::weed::make_terminal_or_expr(p))
				, limited_category_(limited_category)
			{}
			SPROUT_CONSTEXPR sprout::weed::limited::category limited_category() const {
				return limited_category_;
			}
			template<typename Context, typename Iterator>
			SPROUT_CONSTEXPR typename result<Context, Iterator>::type operator()(
				Iterator, Iterator,
				Context const& ctx
				) const
			{
				return sprout::weed::eval(expr_, ctx).presult();
			}
		};
		template<typename Parser, std::size_t Limit>
		SPROUT_CONSTEXPR_OR_CONST std::size_t limit_p<Parser, Limit>::limit;

		//
		// lim
		//
		template<std::size_t Limit, typename Parser>
		SPROUT_CONSTEXPR sprout::weed::limit_p<Parser, Limit> lim(Parser const& p) {
			return sprout::weed::limit_p<Parser, Limit>(p);
		}
		template<std::size_t Limit, typename Parser>
		SPROUT_CONSTEXPR sprout::weed::limit_p<Parser, Limit> lim(
			Parser const& p,
			sprout::weed::limited::category limited_category
			)
		{
			return sprout::weed::limit_p<Parser, Limit>(p, limited_category);
		}

		namespace traits {
			//
			// limit_of
			//
			template<typename Parser, std::size_t Limit, typename Iterator, typename Context>
			struct limit_of<sprout::weed::limit_p<Parser, Limit>, Iterator, Context>
				: public sprout::integral_constant<std::size_t, Limit>
			{};
		}	// namespace traits
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_PARSER_LIM_HPP
