/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIXED_PREV_PERMUTATION_HPP
#define SPROUT_ALGORITHM_FIXED_PREV_PERMUTATION_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/algorithm/fixed/swap_element.hpp>
#include <sprout/algorithm/fixed/reverse_copy.hpp>
#include <sprout/detail/predef.hpp>
#if SPROUT_GCC_EARLIER(4, 8, 2)
#	include <sprout/algorithm/fit/reverse_copy.hpp>
#	include <sprout/range/algorithm/fixed/copy_backward.hpp>
#else
#	include <sprout/iterator/reverse_iterator.hpp>
#	include <sprout/algorithm/fixed/copy_backward.hpp>
#endif
#include <sprout/utility/pair/pair.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename Result, typename Container, typename Difference>
			inline SPROUT_CONSTEXPR Result
			prev_permutation_impl_4(Container const& cont, Difference d) {
				return Result(
#if SPROUT_GCC_EARLIER(4, 8, 2)
					sprout::range::fixed::copy_backward(sprout::fit::reverse_copy(sprout::next(sprout::begin(cont), d), sprout::end(cont), cont), cont),
#else
					sprout::fixed::copy_backward(sprout::make_reverse_iterator(sprout::end(cont)), sprout::make_reverse_iterator(sprout::next(sprout::begin(cont), d)), cont),
#endif
					true
					);
			}
			template<typename Result, typename Container, typename Compare, typename BidirectionalIterator>
			inline SPROUT_CONSTEXPR Result
			prev_permutation_impl_3(
				Container const& cont, Compare comp,
				BidirectionalIterator const& first, BidirectionalIterator const& last,
				BidirectionalIterator const& i, BidirectionalIterator const& ii, BidirectionalIterator const& j
				)
			{
				return !comp(*sprout::prev(j), *i) ? sprout::fixed::detail::prev_permutation_impl_3<Result>(
						cont, comp, first, last,
						i, ii, sprout::prev(j)
						)
					: sprout::fixed::detail::prev_permutation_impl_4<Result>(
						sprout::fixed::swap_element(cont, i, sprout::prev(j)),
						sprout::distance(first, ii)
						)
					;
			}
			template<typename Result, typename Container, typename Compare, typename BidirectionalIterator>
			inline SPROUT_CONSTEXPR Result
			prev_permutation_impl_2(
				Container const& cont, Compare comp,
				BidirectionalIterator const& first, BidirectionalIterator const& last,
				BidirectionalIterator const& i, BidirectionalIterator const& ii
				)
			{
				return comp(*ii, *i) ? sprout::fixed::detail::prev_permutation_impl_3<Result>(
						cont, comp, first, last,
						i, ii, last
						)
					: i == first ? Result(sprout::fixed::reverse_copy(first, last, cont), false)
					: sprout::fixed::detail::prev_permutation_impl_2<Result>(
						cont, comp, first, last,
						sprout::prev(i), i
						)
					;
			}
			template<typename Result, typename Container, typename Compare, typename BidirectionalIterator>
			inline SPROUT_CONSTEXPR Result
			prev_permutation_impl_1(
				Container const& cont, Compare comp,
				BidirectionalIterator const& first, BidirectionalIterator const& last,
				BidirectionalIterator const& i
				)
			{
				return i == last ? Result(sprout::deep_copy(cont), false)
					: sprout::fixed::detail::prev_permutation_impl_2<Result>(
						cont, comp, first, last,
						sprout::prev(last, 2), sprout::prev(last)
						)
					;
			}
			template<typename Result, typename Container, typename Compare, typename BidirectionalIterator>
			inline SPROUT_CONSTEXPR Result
			prev_permutation_impl(Container const& cont, Compare comp, BidirectionalIterator const& first, BidirectionalIterator const& last) {
				return first == last ? Result(sprout::deep_copy(cont), false)
					: sprout::fixed::detail::prev_permutation_impl_1<Result>(
					cont, comp, first, last,
					sprout::next(first)
					);
			}
		}	// namespace detail
		//
		// prev_permutation
		//
		template<typename Container, typename Compare>
		inline SPROUT_CONSTEXPR sprout::pair<typename sprout::fixed::results::algorithm<Container>::type, bool>
		prev_permutation(Container const& cont, Compare comp) {
			typedef sprout::pair<typename sprout::fixed::results::algorithm<Container>::type, bool> type;
			return sprout::fixed::detail::prev_permutation_impl<type>(
				cont, comp,
				sprout::begin(cont), sprout::end(cont)
				);
		}
		//
		// prev_permutation
		//
		template<typename Container>
		inline SPROUT_CONSTEXPR sprout::pair<typename sprout::fixed::results::algorithm<Container>::type, bool>
		prev_permutation(Container const& cont) {
			typedef sprout::pair<typename sprout::fixed::results::algorithm<Container>::type, bool> type;
			return sprout::fixed::detail::prev_permutation_impl<type>(
				cont, NS_SSCRISK_CEL_OR_SPROUT::less<typename sprout::container_traits<Container>::value_type>(),
				sprout::begin(cont), sprout::end(cont)
				);
		}
	}	// namespace fixed

	using sprout::fixed::prev_permutation;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_PREV_PERMUTATION_HPP
