#ifndef SPROUT_BRAINFUCK_MISA_HPP
#define SPROUT_BRAINFUCK_MISA_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/utility/pair.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
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
		namespace misa {
			//
			// to_brainfuck
			//
			template<typename InputIterator, typename Result>
			inline SPROUT_CONSTEXPR sprout::pair<typename sprout::fixed::result_of::algorithm<Result>::type, bool>
			to_brainfuck(InputIterator first, InputIterator last, Result const& result) {
				return sprout::brainfuck::detail::parsed_to_brainfuck(
					sprout::weed::parse(
						first, last,
						*sprout::weed::lim<sprout::container_traits<Result>::static_size>(
							sprout::weed::replace('>')
								[sprout::weed::lit('>') | "\x81\xA8"/*"→"*/ | "\x81\x60"/*"～"*/ | "\x81\5B"/*"ー"*/]
							| sprout::weed::replace('<')
								[sprout::weed::lit('<') | "\x81\xA9"/*"←"*/ | "\x81\x9A"/*"★"*/ | "\x81\x99"/*"☆"*/]
							| sprout::weed::replace('+')
								[sprout::weed::lit('+') | "\x82\xA0"/*"あ"*/ | "\x82\x9F"/*"ぁ"*/ | "\x82\xA8"/*"お"*/ | "\x82\xA7"/*"ぉ"*/]
							| sprout::weed::replace('-')
								[sprout::weed::lit('-') | "\x82\xC1"/*"っ"*/ | "\x83\x62"/*"ッ"*/]
							| sprout::weed::replace('.')
								[sprout::weed::lit('.') | "\x81\x49"/*"！"*/]
							| sprout::weed::replace(',')
								[sprout::weed::lit(',') | "\x81\x48"/*"？"*/]
							| sprout::weed::replace('[')
								[sprout::weed::lit('[') | "\x81\x75"/*"「"*/ | "\x81\x77"/*"『"*/]
							| sprout::weed::replace(']')
								[sprout::weed::lit(']') | "\x81\x76"/*"」"*/ | "\x81\x78"/*"』"*/]
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
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Output>::type
			exec_range(BidirectionalRangeSource const& source, Output const& output, InputRangeInput const& input) {
				typedef typename sprout::container_construct_traits<BidirectionalRangeSource>::copied_type copied_type;
				return sprout::brainfuck::exec_range<BufferSize>(
					sprout::brainfuck::misa::to_brainfuck(sprout::begin(source), sprout::end(source), sprout::pit<copied_type>()).first,
					output, input
					);
			}
			template<std::size_t BufferSize = 32, typename BidirectionalRangeSource, typename Output>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Output>::type
			exec_range(BidirectionalRangeSource const& source, Output const& output) {
				typedef typename sprout::container_construct_traits<BidirectionalRangeSource>::copied_type copied_type;
				return sprout::brainfuck::exec_range<BufferSize>(
					sprout::brainfuck::misa::to_brainfuck(sprout::begin(source), sprout::end(source), sprout::pit<copied_type>()).first,
					output
					);
			}
			template<std::size_t BufferSize = 32, typename BidirectionalRangeSource>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<
				sprout::array<typename sprout::container_traits<BidirectionalRangeSource>::value_type, BufferSize>
			>::type
			exec_range(BidirectionalRangeSource const& source) {
				typedef typename sprout::container_construct_traits<BidirectionalRangeSource>::copied_type copied_type;
				return sprout::brainfuck::exec_range<BufferSize>(
					sprout::brainfuck::misa::to_brainfuck(sprout::begin(source), sprout::end(source), sprout::pit<copied_type>()).first
					);
			}
		}	// namespace misa
	}	// namespace brainfuck
}	// namespace sprout

#endif	// #ifndef SPROUT_BRAINFUCK_MISA_HPP
