/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIXED_CLAMP_RANGE_COPY_HPP
#define SPROUT_ALGORITHM_FIXED_CLAMP_RANGE_COPY_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/container/indexes.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/clamp_iterator.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/algorithm/clamp.hpp>
#include <sprout/pit/pit.hpp>
#include <sprout/detail/container_complate.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename RandomAccessIterator, typename Result, typename Compare, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
			clamp_range_copy_impl_ra(
				RandomAccessIterator first, RandomAccessIterator, Result const& result,
				typename std::iterator_traits<RandomAccessIterator>::value_type const& low,
				typename std::iterator_traits<RandomAccessIterator>::value_type const& high,
				Compare comp,
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
						? sprout::clamp(first[Indexes - offset], low, high, comp)
						: *sprout::next(sprout::internal_begin(result), Indexes)
						)...
					);
			}
			template<typename RandomAccessIterator, typename Result, typename Compare>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
			clamp_range_copy(
				RandomAccessIterator first, RandomAccessIterator last, Result const& result,
				typename std::iterator_traits<RandomAccessIterator>::value_type const& low,
				typename std::iterator_traits<RandomAccessIterator>::value_type const& high,
				Compare comp,
				std::random_access_iterator_tag*
				)
			{
				return sprout::fixed::detail::clamp_range_copy_impl_ra(
					first, last, result, low, high, comp,
					sprout::container_indexes<Result>::make(),
					sprout::internal_begin_offset(result),
					sprout::size(result),
					sprout::distance(first, last)
					);
			}

			template<typename InputIterator, typename Result, typename Compare, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args),
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			clamp_range_copy_impl(
				InputIterator, InputIterator, Result const& result,
				typename std::iterator_traits<InputIterator>::value_type const&,
				typename std::iterator_traits<InputIterator>::value_type const&,
				Compare,
				typename sprout::container_traits<Result>::size_type,
				Args const&... args
				)
			{
				return sprout::remake<Result>(result, sprout::size(result), args...);
			}
			template<typename InputIterator, typename Result, typename Compare, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args),
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			clamp_range_copy_impl(
				InputIterator first, InputIterator last, Result const& result,
				typename std::iterator_traits<InputIterator>::value_type const& low,
				typename std::iterator_traits<InputIterator>::value_type const& high,
				Compare comp,
				typename sprout::container_traits<Result>::size_type size,
				Args const&... args
				)
			{
				return first != last && sizeof...(Args) < size
					? clamp_range_copy_impl(
						sprout::next(first), last, result, low, high, comp,
						size,
						args..., sprout::clamp(*first, low, high, comp)
						)
					: sprout::detail::container_complate(result, args...)
					;
			}
			template<typename InputIterator, typename Result, typename Compare>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
			clamp_range_copy(
				InputIterator first, InputIterator last, Result const& result,
				typename std::iterator_traits<InputIterator>::value_type const& low,
				typename std::iterator_traits<InputIterator>::value_type const& high,
				Compare comp,
				std::input_iterator_tag*
				)
			{
				return sprout::fixed::detail::clamp_range_copy_impl(first, last, result, low, high, comp, sprout::size(result));
			}

			template<typename InputIterator, typename Result, typename Compare>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::is_fixed_container<Result>::value,
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			clamp_range_copy(
				InputIterator first, InputIterator last, Result const& result,
				typename std::iterator_traits<InputIterator>::value_type const& low,
				typename std::iterator_traits<InputIterator>::value_type const& high,
				Compare comp
				)
			{
				typedef typename std::iterator_traits<InputIterator>::iterator_category* category;
				return sprout::fixed::detail::clamp_range_copy(first, last, result, low, high, comp, category());
			}

			template<typename InputIterator, typename Result, typename Compare>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				!sprout::is_fixed_container<Result>::value,
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			clamp_range_copy(
				InputIterator first, InputIterator last, Result const& result,
				typename std::iterator_traits<InputIterator>::value_type const& low,
				typename std::iterator_traits<InputIterator>::value_type const& high,
				Compare comp
				)
			{
				return sprout::remake<Result>(
					result, sprout::size(result),
					sprout::make_clamp_iterator(first, low, high, comp),
					sprout::make_clamp_iterator(last, low, high, comp)
					);
			}
		}	// namespace detail
		//
		// clamp_range_copy
		//
		template<typename InputIterator, typename Result, typename Compare>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		clamp_range_copy(
			InputIterator first, InputIterator last, Result const& result,
			typename std::iterator_traits<InputIterator>::value_type const& low,
			typename std::iterator_traits<InputIterator>::value_type const& high,
			Compare comp
			)
		{
			return sprout::fixed::detail::clamp_range_copy(first, last, result, low, high, comp);
		}
		template<typename InputIterator, typename Result>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		clamp_range_copy(
			InputIterator first, InputIterator last, Result const& result,
			typename std::iterator_traits<InputIterator>::value_type const& low,
			typename std::iterator_traits<InputIterator>::value_type const& high
			)
		{
			return sprout::fixed::clamp_range_copy(
				first, last, result, low, high,
				NS_SSCRISK_CEL_OR_SPROUT::less<typename std::iterator_traits<InputIterator>::value_type>()
				);
		}

		template<typename Result, typename InputIterator, typename Compare>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		clamp_range_copy(
			InputIterator first, InputIterator last,
			typename std::iterator_traits<InputIterator>::value_type const& low,
			typename std::iterator_traits<InputIterator>::value_type const& high,
			Compare comp
			)
		{
			return sprout::fixed::clamp_range_copy(first, last, sprout::pit<Result>(), low, high, comp);
		}
		template<typename Result, typename InputIterator>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		clamp_range_copy(
			InputIterator first, InputIterator last,
			typename std::iterator_traits<InputIterator>::value_type const& low,
			typename std::iterator_traits<InputIterator>::value_type const& high
			)
		{
			return sprout::fixed::clamp_range_copy(first, last, sprout::pit<Result>(), low, high);
		}
	}	// namespace fixed

	using sprout::fixed::clamp_range_copy;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_CLAMP_RANGE_COPY_HPP
