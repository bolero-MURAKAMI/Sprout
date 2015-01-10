/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIXED_SWAP_ELEMENT_COPY_HPP
#define SPROUT_ALGORITHM_FIXED_SWAP_ELEMENT_COPY_HPP

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
#include <sprout/detail/container_complate.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename RandomAccessIterator, typename Result, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
			swap_element_copy_impl_ra(
				RandomAccessIterator first, RandomAccessIterator,
				Result const& result,
				RandomAccessIterator pos1, RandomAccessIterator pos2,
				sprout::index_tuple<Indexes...>,
				typename sprout::container_traits<Result>::difference_type offset,
				typename sprout::container_traits<Result>::size_type size,
				typename sprout::container_traits<Result>::size_type input_size
				)
			{
				return sprout::remake<Result>(
					result,
					sprout::size(result),
					(Indexes >= offset && Indexes < offset + size && Indexes < offset + input_size
						? sprout::next(first, Indexes - offset) == pos1
							? *pos2
							: sprout::next(first, Indexes - offset) == pos2
							? *pos1
							: first[Indexes - offset]
						: *sprout::next(sprout::internal_begin(result), Indexes)
						)...
					);
			}
			template<typename RandomAccessIterator, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
			swap_element_copy(
				RandomAccessIterator first, RandomAccessIterator last,
				Result const& result,
				RandomAccessIterator pos1, RandomAccessIterator pos2,
				std::random_access_iterator_tag*
				)
			{
				return sprout::fixed::detail::swap_element_copy_impl_ra(
					first, last,
					result,
					pos1, pos2,
					sprout::container_indexes<Result>::make(),
					sprout::internal_begin_offset(result),
					sprout::size(result),
					sprout::distance(first, last)
					);
			}

			template<typename ForwardIterator, typename Result, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args),
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			swap_element_copy_impl(
				ForwardIterator, ForwardIterator,
				Result const& result,
				ForwardIterator, ForwardIterator,
				typename sprout::container_traits<Result>::size_type,
				Args const&... args
				)
			{
				return sprout::remake<Result>(result, sprout::size(result), args...);
			}
			template<typename ForwardIterator, typename Result, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args),
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			swap_element_copy_impl(
				ForwardIterator first, ForwardIterator last,
				Result const& result,
				ForwardIterator pos1, ForwardIterator pos2,
				typename sprout::container_traits<Result>::size_type size,
				Args const&... args
				)
			{
				return first != last && sizeof...(Args) < size
					? sprout::fixed::detail::swap_element_copy_impl(
						sprout::next(first), last, result, pos1, pos2,
						size, args..., first == pos1 ? *pos2 : first == pos2 ? *pos1 : *first
						)
					: sprout::detail::container_complate(result, args...)
					;
			}
			template<typename ForwardIterator, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
			swap_element_copy(
				ForwardIterator first, ForwardIterator last,
				Result const& result,
				ForwardIterator pos1, ForwardIterator pos2,
				std::forward_iterator_tag*
				)
			{
				return sprout::fixed::detail::swap_element_copy_impl(first, last, result, pos1, pos2, sprout::size(result));
			}
		}	// namespace detail
		//
		// swap_element_copy
		//
		template<typename ForwardIterator, typename Result>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		swap_element_copy(ForwardIterator first, ForwardIterator last, Result const& result, ForwardIterator pos1, ForwardIterator pos2) {
			typedef typename std::iterator_traits<ForwardIterator>::iterator_category* category;
			return sprout::fixed::detail::swap_element_copy(first, last, result, pos1, pos2, category());
		}

		template<typename Result, typename ForwardIterator>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		swap_element_copy(ForwardIterator first, ForwardIterator last, ForwardIterator pos1, ForwardIterator pos2) {
			return sprout::fixed::swap_element_copy(first, last, sprout::pit<Result>(), pos1, pos2);
		}
	}	// namespace fixed

	template<
		typename ForwardIterator, typename Result,
		typename sprout::enabler_if<!sprout::is_iterator_outputable<Result>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
	swap_element_copy(ForwardIterator first, ForwardIterator last, Result const& result, ForwardIterator pos1, ForwardIterator pos2) {
		typedef typename std::iterator_traits<ForwardIterator>::iterator_category* category;
		return sprout::fixed::detail::swap_element_copy(first, last, result, pos1, pos2, category());
	}

	template<typename Result, typename ForwardIterator>
	inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
	swap_element_copy(ForwardIterator first, ForwardIterator last, ForwardIterator pos1, ForwardIterator pos2) {
		return sprout::fixed::swap_element_copy(first, last, sprout::pit<Result>(), pos1, pos2);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_SWAP_ELEMENT_COPY_HPP
