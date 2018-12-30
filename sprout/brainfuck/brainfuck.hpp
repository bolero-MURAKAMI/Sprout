/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_BRAINFUCK_BRAINFUCK_HPP
#define SPROUT_BRAINFUCK_BRAINFUCK_HPP

#include <iterator>
#include <stdexcept>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/array/array.hpp>
#include <sprout/pit/pit.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/value_iterator.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/algorithm/fixed/copy.hpp>
#include <sprout/operation/fixed/set.hpp>
#include <sprout/detail/char_literal.hpp>
#include HDR_ALGORITHM_MIN_MAX_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace brainfuck {
		namespace detail {
			template<typename InputIterator>
			inline SPROUT_CONSTEXPR InputIterator
			find_scope_end(InputIterator const& first, std::size_t count = 0) {
				typedef typename std::iterator_traits<InputIterator>::value_type value_type;
				return *first == SPROUT_CHAR_LITERAL('[', value_type) ? sprout::brainfuck::detail::find_scope_end(sprout::next(first), count + 1)
					: *first == SPROUT_CHAR_LITERAL(']', value_type) ? count == 0
						? first
						: sprout::brainfuck::detail::find_scope_end(sprout::next(first), count - 1)
					: sprout::brainfuck::detail::find_scope_end(sprout::next(first), count)
					;
			}

			template<typename BidirectionalIterator>
			inline SPROUT_CONSTEXPR BidirectionalIterator
			find_scope_start(BidirectionalIterator const& first, std::size_t count = 0) {
				typedef typename std::iterator_traits<BidirectionalIterator>::value_type value_type;
				return *first == SPROUT_CHAR_LITERAL(']', value_type) ? sprout::brainfuck::detail::find_scope_start(sprout::prev(first), count + 1)
					: *first == SPROUT_CHAR_LITERAL('[', value_type) ? count == 0
						? first
						: sprout::brainfuck::detail::find_scope_start(sprout::prev(first), count - 1)
					: sprout::brainfuck::detail::find_scope_start(sprout::prev(first), count)
					;
			}

			template<typename InputIterator>
			inline SPROUT_CONSTEXPR bool
			is_well_formed(InputIterator const& first, InputIterator const& last, std::size_t count = 0) {
				typedef typename std::iterator_traits<InputIterator>::value_type value_type;
				return first == last ? count == 0
					: *first == SPROUT_CHAR_LITERAL('[', value_type)
						? sprout::brainfuck::detail::is_well_formed(sprout::next(first), last, count + 1)
					: *first == SPROUT_CHAR_LITERAL(']', value_type)
						? count != 0 && sprout::brainfuck::detail::is_well_formed(sprout::next(first), last, count - 1)
					: sprout::brainfuck::detail::is_well_formed(sprout::next(first), last, count)
					;
			}

			template<
				typename BidirectionalIteratorSource, typename Output, typename InputIteratorInput,
				typename Buffer, typename OutputBuffer
			>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Output>::type
			exec_impl(
				BidirectionalIteratorSource first, BidirectionalIteratorSource last,
				Output const& output, InputIteratorInput in_first, InputIteratorInput in_last,
				Buffer const& buffer, OutputBuffer const& out_buffer, std::size_t pos = 0, std::size_t out_pos = 0
				)
			{
				typedef typename std::iterator_traits<BidirectionalIteratorSource>::value_type value_type;
				typedef typename sprout::container_traits<OutputBuffer>::value_type out_value_type;
				return first == last
					? sprout::fixed::copy(
						sprout::begin(out_buffer),
						sprout::next(sprout::begin(out_buffer), NS_SSCRISK_CEL_OR_SPROUT::min(out_pos, sprout::size(out_buffer))),
						output
						)
					: *first == SPROUT_CHAR_LITERAL('>', value_type)
						? sprout::brainfuck::detail::exec_impl(
							sprout::next(first), last, output, in_first, in_last,
							buffer, out_buffer, pos + 1, out_pos
							)
					: *first == SPROUT_CHAR_LITERAL('<', value_type)
						? sprout::brainfuck::detail::exec_impl(
							sprout::next(first), last, output, in_first, in_last,
							buffer, out_buffer, pos - 1, out_pos
							)
					: *first == SPROUT_CHAR_LITERAL('+', value_type)
						? sprout::brainfuck::detail::exec_impl(
							sprout::next(first), last, output, in_first, in_last,
							sprout::fixed::set(buffer, pos, value_type(buffer.at(pos) + 1)), out_buffer, pos, out_pos
							)
					: *first == SPROUT_CHAR_LITERAL('+', value_type)
						? sprout::brainfuck::detail::exec_impl(
							sprout::next(first), last, output, in_first, in_last,
							sprout::fixed::set(buffer, pos, value_type(buffer.at(pos) - 1)), out_buffer, pos, out_pos
							)
					: *first == SPROUT_CHAR_LITERAL('.', value_type) ? out_pos != out_buffer.size()
						? sprout::brainfuck::detail::exec_impl(
							sprout::next(first), last, output, in_first, in_last,
							buffer, sprout::fixed::set(out_buffer, out_pos, out_value_type(buffer.at(pos))), pos, out_pos + 1
							)
						: throw std::out_of_range("output out of range")
					: *first == SPROUT_CHAR_LITERAL(',', value_type) ? in_first != in_last
						? sprout::brainfuck::detail::exec_impl(
							sprout::next(first), last, output, sprout::next(in_first), in_last,
							sprout::fixed::set(buffer, pos, value_type(*in_first)), out_buffer, pos, out_pos
							)
						: throw std::out_of_range("input out of range")
					: *first == SPROUT_CHAR_LITERAL('[', value_type) ? buffer.at(pos) == 0
						? sprout::brainfuck::detail::exec_impl(
							sprout::next(sprout::brainfuck::detail::find_scope_end(sprout::next(first))), last, output, in_first, in_last,
							buffer, out_buffer, pos, out_pos
							)
						: sprout::brainfuck::detail::exec_impl(
							sprout::next(first), last, output, in_first, in_last,
							buffer, out_buffer, pos, out_pos
							)
					: *first == SPROUT_CHAR_LITERAL(']', value_type) ? buffer.at(pos) != 0
						? sprout::brainfuck::detail::exec_impl(
							sprout::next(sprout::brainfuck::detail::find_scope_start(sprout::prev(first))), last, output, in_first, in_last,
							buffer, out_buffer, pos, out_pos
							)
						: sprout::brainfuck::detail::exec_impl(
							sprout::next(first), last, output, in_first, in_last,
							buffer, out_buffer, pos, out_pos
							)
					: sprout::brainfuck::detail::exec_impl(
						sprout::next(first), last, output, in_first, in_last,
						buffer, out_buffer, pos, out_pos
						)
					;
			}
		}	// namespace detail

		//
		// exec
		//
		template<std::size_t BufferSize = 32, typename BidirectionalIteratorSource, typename Output, typename InputIteratorInput>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Output>::type
		exec(
			BidirectionalIteratorSource first, BidirectionalIteratorSource last,
			Output const& output, InputIteratorInput in_first, InputIteratorInput in_last
			)
		{
			typedef typename std::iterator_traits<BidirectionalIteratorSource>::value_type value_type;
			typedef sprout::container_traits<Output> out_traits;
			return sprout::brainfuck::detail::exec_impl(
				first, last, output, in_first, in_last,
				sprout::array<value_type, BufferSize>{{}}, sprout::array<typename out_traits::value_type, out_traits::static_size>{{}}
				);
		}
		template<std::size_t BufferSize = 32, typename BidirectionalIteratorSource, typename Output>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Output>::type
		exec(
			BidirectionalIteratorSource first, BidirectionalIteratorSource last,
			Output const& output
			)
		{
			typedef typename std::iterator_traits<BidirectionalIteratorSource>::value_type value_type;
			return sprout::brainfuck::exec<BufferSize>(
				first, last, output, sprout::value_iterator<value_type>(value_type()), sprout::value_iterator<value_type>()
				);
		}
		template<std::size_t BufferSize = 32, typename BidirectionalIteratorSource>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<
			sprout::array<typename std::iterator_traits<BidirectionalIteratorSource>::value_type, BufferSize>
		>::type
		exec(
			BidirectionalIteratorSource first, BidirectionalIteratorSource last
			)
		{
			typedef typename std::iterator_traits<BidirectionalIteratorSource>::value_type value_type;
			return sprout::brainfuck::exec<BufferSize>(
				first, last, sprout::pit<sprout::array<value_type, BufferSize> >()
				);
		}

		//
		// exec_range
		//
		template<std::size_t BufferSize = 32, typename BidirectionalRangeSource, typename Output, typename InputRangeInput>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Output>::type
		exec_range(BidirectionalRangeSource const& source, Output const& output, InputRangeInput const& input) {
			return sprout::brainfuck::exec<BufferSize>(
				sprout::begin(source), sprout::end(source), output, sprout::begin(input), sprout::end(input)
				);
		}
		template<std::size_t BufferSize = 32, typename BidirectionalRangeSource, typename Output>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Output>::type
		exec_range(BidirectionalRangeSource const& source, Output const& output) {
			return sprout::brainfuck::exec<BufferSize>(
				sprout::begin(source), sprout::end(source), output
				);
		}
		template<std::size_t BufferSize = 32, typename BidirectionalRangeSource>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<
			sprout::array<typename sprout::container_traits<BidirectionalRangeSource>::value_type, BufferSize>
		>::type
		exec_range(BidirectionalRangeSource const& source) {
			return sprout::brainfuck::exec<BufferSize>(
				sprout::begin(source), sprout::end(source)
				);
		}

		//
		// is_well_formed
		//
		template<typename InputIterator>
		inline SPROUT_CONSTEXPR bool
		is_well_formed(InputIterator first, InputIterator last) {
			return sprout::brainfuck::detail::is_well_formed(first, last);
		}
	}	// namespace brainfuck
}	// namespace sprout

#endif	// #ifndef SPROUT_BRAINFUCK_BRAINFUCK_HPP
