/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_TRAITS_PARSER_LIMIT_OF_HPP
#define SPROUT_WEED_TRAITS_PARSER_LIMIT_OF_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/weed/expr/expr.hpp>
#include <sprout/weed/expr/tag.hpp>

namespace sprout {
	namespace weed {
		namespace traits {
			//
			// limit_of
			//
			template<typename T, typename Iterator, typename Context, typename = void>
			struct limit_of
				: public sprout::integral_constant<std::size_t, static_cast<std::size_t>(-1)>
			{};
			template<typename T, typename Iterator, typename Context>
			struct limit_of<T const, Iterator, Context>
				: public sprout::weed::traits::limit_of<T, Iterator, Context>
			{};
			template<typename Arg, typename Iterator, typename Context>
			struct limit_of<sprout::weed::expr<sprout::weed::tag::terminal, Arg>, Iterator, Context>
				: public sprout::weed::traits::limit_of<Arg, Iterator, Context>
			{};
		}	// namespace traits
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_TRAITS_PARSER_LIMIT_OF_HPP
