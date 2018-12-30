/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_PARSER_CHAR_CHAR_CLASS_HPP
#define SPROUT_WEED_PARSER_CHAR_CHAR_CLASS_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/ctype/ascii.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/weed/unused.hpp>
#include <sprout/weed/parser_result.hpp>
#include <sprout/weed/parser/parser_base.hpp>

namespace sprout {
	namespace weed {
#define SPROUT_WEED_DEFINE_CTYPE_P(NAME, ISNAME) \
		template<bool Nil = false> \
		struct NAME \
			: public sprout::weed::parser_base \
		{ \
		public: \
			template<typename Context, typename Iterator> \
			struct attribute \
				: public std::conditional< \
					Nil, \
					sprout::weed::unused, \
					typename std::iterator_traits<Iterator>::value_type \
				> \
			{}; \
			template<typename Context, typename Iterator> \
			struct result \
				: public sprout::identity<sprout::weed::parser_result<Iterator, typename attribute<Context, Iterator>::type> > \
			{}; \
		public: \
			template<typename Context, typename Iterator> \
			SPROUT_CONSTEXPR typename result<Context, Iterator>::type operator()( \
				Iterator first, Iterator last, \
				Context const& \
				) const \
			{ \
				typedef typename result<Context, Iterator>::type result_type; \
				typedef typename attribute<Context, Iterator>::type attribute_type; \
				return first != last && sprout::ascii::ISNAME(*first) \
					? result_type(true, sprout::next(first), *first) \
					: result_type(false, first, attribute_type()) \
					; \
			} \
		}

		//
		// alnum_p
		// alpha_p
		// blank_p
		// cntrl_p
		// digit_p
		// graph_p
		// print_p
		// punct_p
		// space_p
		// xdigit_p
		// lower_p
		// upper_p
		//
		SPROUT_WEED_DEFINE_CTYPE_P(alnum_p, isalnum);
		SPROUT_WEED_DEFINE_CTYPE_P(alpha_p, isalpha);
		SPROUT_WEED_DEFINE_CTYPE_P(blank_p, isblank);
		SPROUT_WEED_DEFINE_CTYPE_P(cntrl_p, iscntrl);
		SPROUT_WEED_DEFINE_CTYPE_P(digit_p, isdigit);
		SPROUT_WEED_DEFINE_CTYPE_P(graph_p, isgraph);
		SPROUT_WEED_DEFINE_CTYPE_P(print_p, isprint);
		SPROUT_WEED_DEFINE_CTYPE_P(punct_p, ispunct);
		SPROUT_WEED_DEFINE_CTYPE_P(space_p, isspace);
		SPROUT_WEED_DEFINE_CTYPE_P(xdigit_p, isxdigit);
		SPROUT_WEED_DEFINE_CTYPE_P(lower_p, islower);
		SPROUT_WEED_DEFINE_CTYPE_P(upper_p, isupper);

#undef SPROUT_WEED_DEFINE_CTYPE_P

		//
		// alnum
		// alpha
		// blank
		// cntrl
		// digit
		// graph
		// print
		// punct
		// space
		// xdigit
		// lower
		// upper
		//
		SPROUT_STATIC_CONSTEXPR sprout::weed::alnum_p<> alnum = sprout::weed::alnum_p<>();
		SPROUT_STATIC_CONSTEXPR sprout::weed::alpha_p<> alpha = sprout::weed::alpha_p<>();
		SPROUT_STATIC_CONSTEXPR sprout::weed::blank_p<> blank = sprout::weed::blank_p<>();
		SPROUT_STATIC_CONSTEXPR sprout::weed::cntrl_p<> cntrl = sprout::weed::cntrl_p<>();
		SPROUT_STATIC_CONSTEXPR sprout::weed::digit_p<> digit = sprout::weed::digit_p<>();
		SPROUT_STATIC_CONSTEXPR sprout::weed::graph_p<> graph = sprout::weed::graph_p<>();
		SPROUT_STATIC_CONSTEXPR sprout::weed::print_p<> print = sprout::weed::print_p<>();
		SPROUT_STATIC_CONSTEXPR sprout::weed::punct_p<> punct = sprout::weed::punct_p<>();
		SPROUT_STATIC_CONSTEXPR sprout::weed::space_p<> space = sprout::weed::space_p<>();
		SPROUT_STATIC_CONSTEXPR sprout::weed::xdigit_p<> xdigit = sprout::weed::xdigit_p<>();
		SPROUT_STATIC_CONSTEXPR sprout::weed::lower_p<> lower = sprout::weed::lower_p<>();
		SPROUT_STATIC_CONSTEXPR sprout::weed::upper_p<> upper = sprout::weed::upper_p<>();
		//
		// alnum_
		// alpha_
		// blank_
		// cntrl_
		// digit_
		// graph_
		// print_
		// punct_
		// space_
		// xdigit_
		// lower_
		// upper_
		//
		SPROUT_STATIC_CONSTEXPR sprout::weed::alnum_p<true> alnum_ = sprout::weed::alnum_p<true>();
		SPROUT_STATIC_CONSTEXPR sprout::weed::alpha_p<true> alpha_ = sprout::weed::alpha_p<true>();
		SPROUT_STATIC_CONSTEXPR sprout::weed::blank_p<true> blank_ = sprout::weed::blank_p<true>();
		SPROUT_STATIC_CONSTEXPR sprout::weed::cntrl_p<true> cntrl_ = sprout::weed::cntrl_p<true>();
		SPROUT_STATIC_CONSTEXPR sprout::weed::digit_p<true> digit_ = sprout::weed::digit_p<true>();
		SPROUT_STATIC_CONSTEXPR sprout::weed::graph_p<true> graph_ = sprout::weed::graph_p<true>();
		SPROUT_STATIC_CONSTEXPR sprout::weed::print_p<true> print_ = sprout::weed::print_p<true>();
		SPROUT_STATIC_CONSTEXPR sprout::weed::punct_p<true> punct_ = sprout::weed::punct_p<true>();
		SPROUT_STATIC_CONSTEXPR sprout::weed::space_p<true> space_ = sprout::weed::space_p<true>();
		SPROUT_STATIC_CONSTEXPR sprout::weed::xdigit_p<true> xdigit_ = sprout::weed::xdigit_p<true>();
		SPROUT_STATIC_CONSTEXPR sprout::weed::lower_p<true> lower_ = sprout::weed::lower_p<true>();
		SPROUT_STATIC_CONSTEXPR sprout::weed::upper_p<true> upper_ = sprout::weed::upper_p<true>();
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_PARSER_CHAR_CHAR_CLASS_HPP
