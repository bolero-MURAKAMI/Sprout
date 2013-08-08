/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_BRAINFUCK_DETAIL_CONVERT_HPP
#define SPROUT_BRAINFUCK_DETAIL_CONVERT_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/copy.hpp>

namespace sprout {
	namespace brainfuck {
		namespace detail {
			template<typename Result, typename Parsed>
			inline SPROUT_CONSTEXPR sprout::pair<typename sprout::fixed::result_of::algorithm<Result>::type, bool>
			parsed_to_brainfuck(Parsed const& parsed, Result const& result) {
				return parsed.success()
					? sprout::pair<typename sprout::fixed::result_of::algorithm<Result>::type, bool>(
						sprout::fixed::copy(sprout::begin(parsed.attr()), sprout::end(parsed.attr()), result),
						true
						)
					: sprout::pair<typename sprout::fixed::result_of::algorithm<Result>::type, bool>(
						sprout::deep_copy(result),
						false
						)
					;
			}
		}	// namespace detail
	}	// namespace brainfuck
}	// namespace sprout

#endif	// #ifndef SPROUT_BRAINFUCK_DETAIL_CONVERT_HPP
