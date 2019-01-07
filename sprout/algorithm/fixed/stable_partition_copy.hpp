/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIXED_STABLE_PARTITION_COPY_HPP
#define SPROUT_ALGORITHM_FIXED_STABLE_PARTITION_COPY_HPP

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
			template<typename BidirectionalIterator, typename Result, typename Predicate, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args),
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			stable_partition_copy_impl_1(
				BidirectionalIterator const&, BidirectionalIterator const&,
				Result const& result, Predicate,
				typename sprout::container_traits<Result>::size_type,
				Args const&... args
				)
			{
				return sprout::remake<Result>(result, sprout::size(result), args...);
			}
			template<typename BidirectionalIterator, typename Result, typename Predicate, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args),
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			stable_partition_copy_impl_1(
				BidirectionalIterator const& first, BidirectionalIterator const& last,
				Result const& result, Predicate pred,
				typename sprout::container_traits<Result>::size_type size,
				Args const&... args
				)
			{
				return first != last && sizeof...(Args) < size
					? !pred(*first)
						? sprout::fixed::detail::stable_partition_copy_impl_1(
							sprout::next(first), last, result, pred,
							size, args..., *first
							)
						: sprout::fixed::detail::stable_partition_copy_impl_1(
							sprout::next(first), last, result, pred,
							size, args...
							)
					: sprout::detail::container_complate(result, args...)
					;
			}

			template<typename BidirectionalIterator, typename Result, typename Predicate, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args),
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			stable_partition_copy_impl(
				BidirectionalIterator, BidirectionalIterator,
				Result const& result, Predicate,
				typename sprout::container_traits<Result>::size_type,
				BidirectionalIterator,
				Args const&... args
				)
			{
				return sprout::remake<Result>(result, sprout::size(result), args...);
			}
			template<typename BidirectionalIterator, typename Result, typename Predicate, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args),
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			stable_partition_copy_impl(
				BidirectionalIterator const& first, BidirectionalIterator const& last,
				Result const& result, Predicate pred,
				typename sprout::container_traits<Result>::size_type size,
				BidirectionalIterator const& temp_first,
				Args const&... args
				)
			{
				return first != last && sizeof...(Args) < size
					? pred(*first)
						? sprout::fixed::detail::stable_partition_copy_impl(
							sprout::next(first), last, result, pred,
							size, temp_first, args..., *first
							)
						: sprout::fixed::detail::stable_partition_copy_impl(
							sprout::next(first), last, result, pred,
							size, temp_first, args...
							)
					: sprout::fixed::detail::stable_partition_copy_impl_1(
						temp_first, last, result, pred,
						size, args...
						)
					;
			}
		}	// namespace detail
		//
		// stable_partition_copy
		//
		template<typename BidirectionalIterator, typename Result, typename Predicate>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		stable_partition_copy(BidirectionalIterator first, BidirectionalIterator last, Result const& result, Predicate pred) {
			return sprout::fixed::detail::stable_partition_copy_impl(first, last, result, pred, sprout::size(result), first);
		}

		template<typename Result, typename BidirectionalIterator, typename Predicate>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		stable_partition_copy(BidirectionalIterator first, BidirectionalIterator last, Predicate pred) {
			return sprout::fixed::stable_partition_copy(first, last, sprout::pit<Result>(), pred);
		}
	}	// namespace fixed

	using sprout::fixed::stable_partition_copy;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_STABLE_PARTITION_COPY_HPP
