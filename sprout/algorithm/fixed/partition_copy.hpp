/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIXED_PARTITION_COPY_HPP
#define SPROUT_ALGORITHM_FIXED_PARTITION_COPY_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/pit/pit.hpp>
#include <sprout/detail/container_complate.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename InputIterator, typename Result, typename Predicate, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args),
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			partition_copy_impl(
				InputIterator, InputIterator, Result const& result, Predicate,
				typename sprout::container_traits<Result>::size_type,
				Args const&... args
				)
			{
				return sprout::remake<Result>(result, sprout::size(result), args...);
			}
			template<typename InputIterator, typename Result, typename Predicate, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args),
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			partition_copy_impl(
				InputIterator first, InputIterator last, Result const& result, Predicate pred,
				typename sprout::container_traits<Result>::size_type size,
				Args const&... args
				)
			{
				return first != last && sizeof...(Args) < size
					? pred(*first)
						? sprout::fixed::detail::partition_copy_impl(sprout::next(first), last, result, pred, size, *first, args...)
						: sprout::fixed::detail::partition_copy_impl(sprout::next(first), last, result, pred, size, args..., *first)
					: sprout::detail::container_complate(result, args...)
					;
			}
		}	// namespace detail
		//
		// partition_copy
		//
		template<typename InputIterator, typename Result, typename Predicate>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		partition_copy(InputIterator first, InputIterator last, Result const& result, Predicate pred) {
			return sprout::fixed::detail::partition_copy_impl(first, last, result, pred, sprout::size(result));
		}

		template<typename Result, typename InputIterator, typename Predicate>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		partition_copy(InputIterator first, InputIterator last, Predicate pred) {
			return sprout::fixed::partition_copy(first, last, sprout::pit<Result>(), pred);
		}
	}	// namespace fixed

	using sprout::fixed::partition_copy;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_PARTITION_COPY_HPP
