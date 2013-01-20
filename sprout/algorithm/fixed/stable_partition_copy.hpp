#ifndef SPROUT_ALGORITHM_FIXED_STABLE_PARTITION_COPY_HPP
#define SPROUT_ALGORITHM_FIXED_STABLE_PARTITION_COPY_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/pit.hpp>
#include <sprout/detail/container_complate.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename BidirectionalIterator, typename Result, typename Predicate, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			stable_partition_copy_impl_1(
				BidirectionalIterator first, BidirectionalIterator last,
				Result const& result, Predicate pred,
				typename sprout::container_traits<Result>::size_type size,
				Args const&... args
				)
			{
				return sprout::remake<Result>(result, sprout::size(result), args...);
			}
			template<typename BidirectionalIterator, typename Result, typename Predicate, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			stable_partition_copy_impl_1(
				BidirectionalIterator first, BidirectionalIterator last,
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
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			stable_partition_copy_impl(
				BidirectionalIterator first, BidirectionalIterator last,
				Result const& result, Predicate pred,
				typename sprout::container_traits<Result>::size_type size,
				BidirectionalIterator temp_first,
				Args const&... args
				)
			{
				return sprout::remake<Result>(result, sprout::size(result), args...);
			}
			template<typename BidirectionalIterator, typename Result, typename Predicate, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			stable_partition_copy_impl(
				BidirectionalIterator first, BidirectionalIterator last,
				Result const& result, Predicate pred,
				typename sprout::container_traits<Result>::size_type size,
				BidirectionalIterator temp_first,
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
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
		stable_partition_copy(BidirectionalIterator first, BidirectionalIterator last, Result const& result, Predicate pred) {
			return sprout::fixed::detail::stable_partition_copy_impl(first, last, result, pred, sprout::size(result), first);
		}

		template<typename Result, typename BidirectionalIterator, typename Predicate>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
		stable_partition_copy(BidirectionalIterator first, BidirectionalIterator last, Predicate pred) {
			return sprout::fixed::stable_partition_copy(first, last, sprout::pit<Result>(), pred);
		}
	}	// namespace fixed

	using sprout::fixed::stable_partition_copy;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_STABLE_PARTITION_COPY_HPP
