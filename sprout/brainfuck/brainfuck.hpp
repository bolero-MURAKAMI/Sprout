#ifndef SPROUT_BRAINFUCK_BRAINFUCK_HPP
#define SPROUT_BRAINFUCK_BRAINFUCK_HPP

#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <sprout/config.hpp>
#include <sprout/array.hpp>
#include <sprout/pit.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/value_iterator.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/copy.hpp>
#include <sprout/operation/fixed/set.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace brainfuck {
		namespace detail {
			template<typename InputIterator>
			inline SPROUT_CONSTEXPR InputIterator
			find_scope_end(InputIterator first, std::size_t count = 0) {
				typedef typename std::iterator_traits<InputIterator>::value_type value_type;
				return *first == value_type('[') ? sprout::brainfuck::detail::find_scope_end(sprout::next(first), count + 1)
					: *first == value_type(']') ? count == 0
						? first
						: sprout::brainfuck::detail::find_scope_end(sprout::next(first), count - 1)
					: sprout::brainfuck::detail::find_scope_end(sprout::next(first), count)
					;
			}

			template<typename BidirectionalIterator>
			inline SPROUT_CONSTEXPR BidirectionalIterator
			find_scope_start(BidirectionalIterator first, std::size_t count = 0) {
				typedef typename std::iterator_traits<BidirectionalIterator>::value_type value_type;
				return *first == value_type(']') ? sprout::brainfuck::detail::find_scope_start(sprout::prev(first), count + 1)
					: *first == value_type('[') ? count == 0
						? first
						: sprout::brainfuck::detail::find_scope_start(sprout::prev(first), count - 1)
					: sprout::brainfuck::detail::find_scope_start(sprout::prev(first), count)
					;
			}

			template<typename InputIterator>
			inline SPROUT_CONSTEXPR bool
			is_well_formed(InputIterator first, InputIterator last, std::size_t count = 0) {
				typedef typename std::iterator_traits<InputIterator>::value_type value_type;
				return first == last ? count == 0
					: *first == value_type('[')
						? sprout::brainfuck::detail::is_well_formed(sprout::next(first), last, count + 1)
					: *first == value_type(']')
						? count != 0 && sprout::brainfuck::detail::is_well_formed(sprout::next(first), last, count - 1)
					: sprout::brainfuck::detail::is_well_formed(sprout::next(first), last, count)
					;
			}

			template<
				typename SourceBidirectionalIterator, typename Output, typename InputInputIterator,
				typename Buffer, typename OutputBuffer
			>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Output>::type
			exec_impl(
				SourceBidirectionalIterator first, SourceBidirectionalIterator last,
				Output const& output, InputInputIterator in_first, InputInputIterator in_last,
				Buffer const& buffer, OutputBuffer const& out_buffer, std::size_t pos = 0, std::size_t out_pos = 0
				)
			{
				typedef typename std::iterator_traits<SourceBidirectionalIterator>::value_type value_type;
				typedef typename sprout::container_traits<OutputBuffer>::value_type out_value_type;
				return first == last
					? sprout::fixed::copy(
						sprout::begin(out_buffer),
						sprout::next(sprout::begin(out_buffer), NS_SSCRISK_CEL_OR_SPROUT::min(out_pos, sprout::size(out_buffer))),
						output
						)
					: *first == value_type('>')
						? sprout::brainfuck::detail::exec_impl(
							sprout::next(first), last, output, in_first, in_last,
							buffer, out_buffer, pos + 1, out_pos
							)
					: *first == value_type('<')
						? sprout::brainfuck::detail::exec_impl(
							sprout::next(first), last, output, in_first, in_last,
							buffer, out_buffer, pos - 1, out_pos
							)
					: *first == value_type('+')
						? sprout::brainfuck::detail::exec_impl(
							sprout::next(first), last, output, in_first, in_last,
							sprout::fixed::set(buffer, pos, value_type(buffer.at(pos) + 1)), out_buffer, pos, out_pos
							)
					: *first == value_type('-')
						? sprout::brainfuck::detail::exec_impl(
							sprout::next(first), last, output, in_first, in_last,
							sprout::fixed::set(buffer, pos, value_type(buffer.at(pos) - 1)), out_buffer, pos, out_pos
							)
					: *first == value_type('.') ? out_pos != out_buffer.size()
						? sprout::brainfuck::detail::exec_impl(
							sprout::next(first), last, output, in_first, in_last,
							buffer, sprout::fixed::set(out_buffer, out_pos, out_value_type(buffer.at(pos))), pos, out_pos + 1
							)
						: throw std::out_of_range("output out of range")
					: *first == value_type(',') ? in_first != in_last
						? sprout::brainfuck::detail::exec_impl(
							sprout::next(first), last, output, sprout::next(in_first), in_last,
							sprout::fixed::set(buffer, pos, value_type(*in_first)), out_buffer, pos, out_pos
							)
						: throw std::out_of_range("input out of range")
					: *first == value_type('[') ? buffer.at(pos) == 0
						? sprout::brainfuck::detail::exec_impl(
							sprout::next(sprout::brainfuck::detail::find_scope_end(sprout::next(first))), last, output, in_first, in_last,
							buffer, out_buffer, pos, out_pos
							)
						: sprout::brainfuck::detail::exec_impl(
							sprout::next(first), last, output, in_first, in_last,
							buffer, out_buffer, pos, out_pos
							)
					: *first == value_type(']') ? buffer.at(pos) != 0
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
		template<std::size_t BufferSize = 32, typename SourceBidirectionalIterator, typename Output, typename InputInputIterator>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Output>::type
		exec(
			SourceBidirectionalIterator first, SourceBidirectionalIterator last,
			Output const& output, InputInputIterator in_first, InputInputIterator in_last
			)
		{
			typedef typename std::iterator_traits<SourceBidirectionalIterator>::value_type value_type;
			typedef sprout::container_traits<Output> out_traits;
			return sprout::brainfuck::detail::exec_impl(
				first, last, output, in_first, in_last,
				sprout::array<value_type, BufferSize>{{}}, sprout::array<typename out_traits::value_type, out_traits::static_size>{{}}
				);
		}
		template<std::size_t BufferSize = 32, typename SourceBidirectionalIterator, typename Output>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Output>::type
		exec(
			SourceBidirectionalIterator first, SourceBidirectionalIterator last,
			Output const& output
			)
		{
			typedef typename std::iterator_traits<SourceBidirectionalIterator>::value_type value_type;
			return sprout::brainfuck::exec<BufferSize>(
				first, last, output, sprout::value_iterator<value_type>(value_type()), sprout::value_iterator<value_type>()
				);
		}
		template<std::size_t BufferSize = 32, typename SourceBidirectionalIterator>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<
			sprout::array<typename std::iterator_traits<SourceBidirectionalIterator>::value_type, BufferSize>
		>::type
		exec(
			SourceBidirectionalIterator first, SourceBidirectionalIterator last
			)
		{
			typedef typename std::iterator_traits<SourceBidirectionalIterator>::value_type value_type;
			return sprout::brainfuck::exec<BufferSize>(
				first, last, sprout::pit<sprout::array<value_type, BufferSize> >()
				);
		}

		//
		// exec_range
		//
		template<std::size_t BufferSize = 32, typename Source, typename Output, typename Input>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Output>::type
		exec_range(Source const& source, Output const& output, Input const& input) {
			return sprout::brainfuck::exec<BufferSize>(
				sprout::begin(source), sprout::end(source), output, sprout::begin(input), sprout::end(input)
				);
		}
		template<std::size_t BufferSize = 32, typename Source, typename Output>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Output>::type
		exec_range(Source const& source, Output const& output) {
			return sprout::brainfuck::exec<BufferSize>(
				sprout::begin(source), sprout::end(source), output
				);
		}
		template<std::size_t BufferSize = 32, typename Source>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<
			sprout::array<typename sprout::container_traits<Source>::value_type, BufferSize>
		>::type
		exec_range(Source const& source) {
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
