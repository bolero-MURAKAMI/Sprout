/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_BRAINFUCK_OOK_HPP
#define SPROUT_BRAINFUCK_OOK_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/utility/pair/pair.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/weed/parse.hpp>
#include <sprout/weed/parser/lim.hpp>
#include <sprout/weed/parser/lit.hpp>
#include <sprout/weed/parser/char/char.hpp>
#include <sprout/weed/parser/char/char_class.hpp>
#include <sprout/weed/parser/string/string.hpp>
#include <sprout/weed/parser/directive/replace.hpp>
#include <sprout/weed/operator.hpp>
#include <sprout/brainfuck/detail/convert.hpp>

namespace sprout {
	namespace brainfuck {
		namespace ook {
			//
			// to_brainfuck
			//
			template<typename InputIterator, typename Result>
			inline SPROUT_CONSTEXPR sprout::pair<typename sprout::fixed::results::algorithm<Result>::type, bool>
			to_brainfuck(InputIterator first, InputIterator last, Result const& result) {
				return sprout::brainfuck::detail::parsed_to_brainfuck(
					sprout::weed::parse(
						first, last,
						*sprout::weed::lim<sprout::container_traits<Result>::static_size>(
							sprout::weed::replace('>')
								["Ook." >> *sprout::weed::space_ >> "Ook?"]
							| sprout::weed::replace('>')
								["Ook?" >> *sprout::weed::space_ >> "Ook."]
							| sprout::weed::replace('>')
								["Ook." >> *sprout::weed::space_ >> "Ook."]
							| sprout::weed::replace('>')
								["Ook!" >> *sprout::weed::space_ >> "Ook!"]
							| sprout::weed::replace('>')
								["Ook!" >> *sprout::weed::space_ >> "Ook."]
							| sprout::weed::replace('>')
								["Ook." >> *sprout::weed::space_ >> "Ook!"]
							| sprout::weed::replace('>')
								["Ook!" >> *sprout::weed::space_ >> "Ook?"]
							| sprout::weed::replace('>')
								["Ook?" >> *sprout::weed::space_ >> "Ook!"]
							| sprout::weed::replace(' ')
								[sprout::weed::char_]
							)
						),
					result
					);
			}

			//
			// exec_range
			//
			template<std::size_t BufferSize = 32, typename BidirectionalRangeSource, typename Output, typename InputRangeInput>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Output>::type
			exec_range(BidirectionalRangeSource const& source, Output const& output, InputRangeInput const& input) {
				typedef typename sprout::container_construct_traits<BidirectionalRangeSource>::copied_type copied_type;
				return sprout::brainfuck::exec_range<BufferSize>(
					sprout::brainfuck::ook::to_brainfuck(sprout::begin(source), sprout::end(source), sprout::pit<copied_type>()).first,
					output, input
					);
			}
			template<std::size_t BufferSize = 32, typename BidirectionalRangeSource, typename Output>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Output>::type
			exec_range(BidirectionalRangeSource const& source, Output const& output) {
				typedef typename sprout::container_construct_traits<BidirectionalRangeSource>::copied_type copied_type;
				return sprout::brainfuck::exec_range<BufferSize>(
					sprout::brainfuck::ook::to_brainfuck(sprout::begin(source), sprout::end(source), sprout::pit<copied_type>()).first,
					output
					);
			}
			template<std::size_t BufferSize = 32, typename BidirectionalRangeSource>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<
				sprout::array<typename sprout::container_traits<BidirectionalRangeSource>::value_type, BufferSize>
			>::type
			exec_range(BidirectionalRangeSource const& source) {
				typedef typename sprout::container_construct_traits<BidirectionalRangeSource>::copied_type copied_type;
				return sprout::brainfuck::exec_range<BufferSize>(
					sprout::brainfuck::ook::to_brainfuck(sprout::begin(source), sprout::end(source), sprout::pit<copied_type>()).first
					);
			}
		}	// namespace ook
	}	// namespace brainfuck
}	// namespace sprout

#endif	// #ifndef SPROUT_BRAINFUCK_OOK_HPP
