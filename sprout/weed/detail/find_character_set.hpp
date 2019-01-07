/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_DETAIL_FIND_CHARACTER_SET_HPP
#define SPROUT_WEED_DETAIL_FIND_CHARACTER_SET_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/type_traits/category.hpp>
#include <sprout/utility/pair/pair.hpp>
#include <sprout/detail/char_literal.hpp>

namespace sprout {
	namespace weed {
		namespace detail {
			template<typename RandomAccessIterator, typename T>
			inline SPROUT_CONSTEXPR RandomAccessIterator
			find_character_set_impl_ra(
				RandomAccessIterator const& first, RandomAccessIterator const& last, T const& value,
				typename std::iterator_traits<RandomAccessIterator>::difference_type pivot, RandomAccessIterator const& found
				)
			{
				return found != first ? found
					: pivot == 0 ? (
						*first == SPROUT_CHAR_LITERAL('-', T) ? *sprout::prev(first) <= value && *sprout::next(first) >= value
							: *first == value
						) ? first : last
					: sprout::weed::detail::find_character_set_impl_ra(
						sprout::next(first, pivot), last, value,
						(sprout::distance(first, last) - pivot) / 2,
						sprout::weed::detail::find_character_set_impl_ra(
							first, sprout::next(first, pivot), value,
							pivot / 2,
							first
							)
						)
					;
			}
			template<typename RandomAccessIterator, typename T>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::is_constant_distance_iterator<RandomAccessIterator>::value,
				RandomAccessIterator
			>::type
			find_character_set(
				RandomAccessIterator const& first, RandomAccessIterator const& last, T const& value,
				std::random_access_iterator_tag*
				)
			{
				return first == last ? last
					: sprout::weed::detail::find_character_set_impl_ra(first, last, value, sprout::distance(first, last) / 2, first)
					;
			}

			template<typename BidirectionalIterator, typename T>
			inline SPROUT_CONSTEXPR sprout::pair<BidirectionalIterator, bool>
			find_character_set_impl_1(
				sprout::pair<BidirectionalIterator, bool> const& current,
				BidirectionalIterator const& last, T const& value, typename std::iterator_traits<BidirectionalIterator>::difference_type n
				)
			{
				typedef sprout::pair<BidirectionalIterator, bool> type;
				return current.second || current.first == last ? current
					: n == 1 ? (
						*current.first == SPROUT_CHAR_LITERAL('-', T) ? *sprout::prev(current.first) <= value && *sprout::next(current.first) >= value
							: *current.first == value
						) ? type(current.first, true) : type(sprout::next(current.first), false)
					: sprout::weed::detail::find_character_set_impl_1(
						sprout::weed::detail::find_character_set_impl_1(
							current,
							last, value, n / 2
							),
						last, value, n - n / 2
						)
					;
			}
			template<typename BidirectionalIterator, typename T>
			inline SPROUT_CONSTEXPR sprout::pair<BidirectionalIterator, bool>
			find_character_set_impl(
				sprout::pair<BidirectionalIterator, bool> const& current,
				BidirectionalIterator const& last, T const& value, typename std::iterator_traits<BidirectionalIterator>::difference_type n
				)
			{
				return current.second || current.first == last ? current
					: sprout::weed::detail::find_character_set_impl(
						sprout::weed::detail::find_character_set_impl_1(
							current,
							last, value, n
							),
						last, value, n * 2
						)
					;
			}
			template<typename BidirectionalIterator, typename T>
			inline SPROUT_CONSTEXPR BidirectionalIterator
			find_character_set(
				BidirectionalIterator const& first, BidirectionalIterator const& last, T const& value,
				std::input_iterator_tag*
				)
			{
				typedef sprout::pair<BidirectionalIterator, bool> type;
				return sprout::weed::detail::find_character_set_impl(type(first, false), last, value, 1).first;
			}

			template<typename BidirectionalIterator, typename T>
			inline SPROUT_CONSTEXPR BidirectionalIterator
			find_character_set(BidirectionalIterator const& first, BidirectionalIterator const& last, T const& value) {
				typedef typename std::iterator_traits<BidirectionalIterator>::iterator_category* category;
				return sprout::weed::detail::find_character_set(first, last, value, category());
			}
		}	// namespace detail
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_DETAIL_FIND_CHARACTER_SET_HPP
