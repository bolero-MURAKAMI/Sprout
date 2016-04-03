/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DETAIL_ALGORITHM_MASK_INDEX_HPP
#define SPROUT_DETAIL_ALGORITHM_MASK_INDEX_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/pit/pit.hpp>
#include <sprout/detail/container_complate.hpp>

namespace sprout {
	namespace detail {
		template<typename InputIterator, typename Result, typename... Args>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::container_traits<Result>::static_size == sizeof...(Args),
			typename sprout::results::algorithm<Result>::type
		>::type
		mask_index_impl(InputIterator const&, InputIterator const&, Result const& result,
			typename sprout::container_traits<Result>::size_type,
			typename sprout::container_traits<Result>::difference_type,
			Args const&... args
			)
		{
			return sprout::remake<Result>(result, sprout::size(result), args...);
		}
		template<typename InputIterator, typename Result, typename... Args>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::container_traits<Result>::static_size != sizeof...(Args),
			typename sprout::results::algorithm<Result>::type
		>::type
		mask_index_impl(
			InputIterator const& first, InputIterator const& last, Result const& result,
			typename sprout::container_traits<Result>::size_type size,
			typename sprout::container_traits<Result>::difference_type n,
			Args const&... args
			)
		{
			return first != last && sizeof...(Args) < size
				? *first
					? sprout::detail::mask_index_impl(sprout::next(first), last, result, size, n + 1, args..., n)
					: sprout::detail::mask_index_impl(sprout::next(first), last, result, size, n + 1, args...)
				: sprout::detail::container_complate(result, args...)
				;
		}

		template<typename InputIterator, typename Result>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_fixed_container<Result>::value,
			typename sprout::results::algorithm<Result>::type
		>::type
		mask_index_(InputIterator const& first, InputIterator const& last, Result const& result) {
			return sprout::detail::mask_index_impl(first, last, result, sprout::size(result), 0);
		}

		//
		// mask_index
		//
		//	recursion depth:
		//		O(log N)
		//
		template<typename InputIterator, typename Result>
		inline SPROUT_CONSTEXPR typename sprout::results::algorithm<Result>::type
		mask_index(InputIterator first, InputIterator last, Result const& result) {
			return sprout::detail::mask_index_(first, last, result);
		}

		template<typename Result, typename InputIterator>
		inline SPROUT_CONSTEXPR typename sprout::results::algorithm<Result>::type
		mask_index(InputIterator first, InputIterator last) {
			return sprout::detail::mask_index(first, last, sprout::pit<Result>());
		}
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_ALGORITHM_MASK_INDEX_HPP
