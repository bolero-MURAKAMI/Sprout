/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIXED_COPY_BACKWARD_HPP
#define SPROUT_ALGORITHM_FIXED_COPY_BACKWARD_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/container/indexes.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/pit/pit.hpp>
#include <sprout/math/greater_equal.hpp>
#include <sprout/detail/container_complate_backward.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename RandomAccessIterator, typename Result, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
			copy_backward_impl_ra(
				RandomAccessIterator const&, RandomAccessIterator const& last, Result const& result,
				sprout::index_tuple<Indexes...>,
				typename sprout::container_traits<Result>::difference_type offset,
				typename sprout::container_traits<Result>::size_type size,
				typename sprout::container_traits<Result>::size_type input_size
				)
			{
				return sprout::remake<Result>(
					result, sprout::size(result),
					(Indexes < offset && sprout::math::greater_equal(Indexes + size, offset) && sprout::math::greater_equal(Indexes + input_size, offset)
						? last[Indexes - offset]
						: *sprout::next(sprout::internal_begin(result), Indexes)
						)...
					);
			}
			template<typename RandomAccessIterator, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
			copy_backward(
				RandomAccessIterator const& first, RandomAccessIterator const& last, Result const& result,
				std::random_access_iterator_tag*
				)
			{
				return sprout::fixed::detail::copy_backward_impl_ra(
					first, last, result,
					sprout::container_indexes<Result>::make(),
					sprout::internal_end_offset(result),
					sprout::size(result),
					sprout::distance(first, last)
					);
			}
			template<typename BidirectionalIterator, typename Result, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args),
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			copy_backward_impl(
				BidirectionalIterator, BidirectionalIterator, Result const& result,
				typename sprout::container_traits<Result>::size_type,
				Args const&... args
				)
			{
				return sprout::remake<Result>(result, sprout::size(result), args...);
			}
			template<typename BidirectionalIterator, typename Result, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args),
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			copy_backward_impl(
				BidirectionalIterator const& first, BidirectionalIterator const& last, Result const& result,
				typename sprout::container_traits<Result>::size_type size,
				Args const&... args
				)
			{
				return first != last && sizeof...(Args) < size
					? sprout::fixed::detail::copy_backward_impl(first, sprout::prev(last), result, size, *sprout::prev(last), args...)
					: sprout::detail::container_complate_backward(result, args...)
					;
			}
			template<typename BidirectionalIterator, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
			copy_backward(
				BidirectionalIterator const& first, BidirectionalIterator const& last, Result const& result,
				std::bidirectional_iterator_tag*
				)
			{
				return sprout::fixed::detail::copy_backward_impl(
					first, last, result,
					sprout::size(result)
					);
			}

			template<typename BidirectionalIterator, typename Result>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::is_fixed_container<Result>::value,
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			copy_backward(BidirectionalIterator const& first, BidirectionalIterator const& last, Result const& result) {
				typedef typename std::iterator_traits<BidirectionalIterator>::iterator_category* category;
				return sprout::fixed::detail::copy_backward(first, last, result, category());
			}
		}	// namespace detail
		//
		// copy_backward
		//
		template<typename BidirectionalIterator, typename Result>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		copy_backward(BidirectionalIterator first, BidirectionalIterator last, Result const& result) {
			return sprout::fixed::detail::copy_backward(first, last, result);
		}

		template<typename Result, typename BidirectionalIterator>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		copy_backward(BidirectionalIterator first, BidirectionalIterator last) {
			return sprout::fixed::copy_backward(first, last, sprout::pit<Result>());
		}
	}	// namespace fixed

	template<
		typename BidirectionalIterator, typename Result,
		typename sprout::enabler_if<!sprout::is_iterator_outputable<Result>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
	copy_backward(BidirectionalIterator first, BidirectionalIterator last, Result const& result) {
		return sprout::fixed::copy_backward(first, last, result);
	}

	template<typename Result, typename BidirectionalIterator>
	inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
	copy_backward(BidirectionalIterator first, BidirectionalIterator last) {
		return sprout::fixed::copy_backward<Result>(first, last);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_COPY_BACKWARD_HPP
