#ifndef SPROUT_ALGORITHM_FIXED_STABLE_PARTITION_COPY_HPP
#define SPROUT_ALGORITHM_FIXED_STABLE_PARTITION_COPY_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename Result, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type stable_partition_copy_impl_4(
				Result const& result,
				Args const&... args
				)
			{
				return sprout::remake_clone<Result, Result>(result, sprout::size(result), args...);
			}
			template<typename Result, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type stable_partition_copy_impl_4(
				Result const& result,
				Args const&... args
				)
			{
				return stable_partition_copy_impl_4(result, args..., *sprout::next(sprout::fixed_begin(result), sizeof...(Args)));
			}

			template<typename BidirectionalIterator, typename Result, typename Predicate, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type stable_partition_copy_impl_3(
				BidirectionalIterator first,
				BidirectionalIterator last,
				Result const& result,
				Predicate pred,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return sprout::remake_clone<Result, Result>(result, sprout::size(result), args...);
			}
			template<typename BidirectionalIterator, typename Result, typename Predicate, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type stable_partition_copy_impl_3(
				BidirectionalIterator first,
				BidirectionalIterator last,
				Result const& result,
				Predicate pred,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return first != last && sizeof...(Args) < static_cast<std::size_t>(offset)
					? !pred(*first)
						? stable_partition_copy_impl_3(sprout::next(first), last, result, pred, offset, args..., *first)
						: stable_partition_copy_impl_3(sprout::next(first), last, result, pred, offset, args...)
					: stable_partition_copy_impl_4(result, args...)
					;
			}

			template<typename BidirectionalIterator, typename Result, typename Predicate, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type stable_partition_copy_impl_2(
				BidirectionalIterator first,
				BidirectionalIterator last,
				Result const& result,
				Predicate pred,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				BidirectionalIterator origin,
				Args const&... args
				)
			{
				return sprout::remake_clone<Result, Result>(result, sprout::size(result), args...);
			}
			template<typename BidirectionalIterator, typename Result, typename Predicate, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type stable_partition_copy_impl_2(
				BidirectionalIterator first,
				BidirectionalIterator last,
				Result const& result,
				Predicate pred,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				BidirectionalIterator origin,
				Args const&... args
				)
			{
				return first != last && sizeof...(Args) < static_cast<std::size_t>(offset)
					? pred(*first)
						? stable_partition_copy_impl_2(sprout::next(first), last, result, pred, offset, origin, args..., *first)
						: stable_partition_copy_impl_2(sprout::next(first), last, result, pred, offset, origin, args...)
					: stable_partition_copy_impl_3(origin, last, result, pred, offset, args...)
					;
			}
			template<typename BidirectionalIterator, typename Result, typename Predicate, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type stable_partition_copy_impl_1(
				BidirectionalIterator first,
				BidirectionalIterator last,
				Result const& result,
				Predicate pred,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				BidirectionalIterator origin,
				Args const&... args
				)
			{
				return sprout::remake_clone<Result, Result>(result, sprout::size(result), args...);
			}
			template<typename BidirectionalIterator, typename Result, typename Predicate, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type stable_partition_copy_impl_1(
				BidirectionalIterator first,
				BidirectionalIterator last,
				Result const& result,
				Predicate pred,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				BidirectionalIterator origin,
				Args const&... args
				)
			{
				return sizeof...(Args) < static_cast<std::size_t>(offset)
					? stable_partition_copy_impl_1(first, last, result, pred, offset, origin, args..., *sprout::next(sprout::fixed_begin(result), sizeof...(Args)))
					: stable_partition_copy_impl_2(first, last, result, pred, offset + sprout::size(result), origin, args...)
					;
			}
			template<typename BidirectionalIterator, typename Result, typename Predicate>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type stable_partition_copy_impl(
				BidirectionalIterator first,
				BidirectionalIterator last,
				Result const& result,
				Predicate pred
				)
			{
				return stable_partition_copy_impl_1(first, last, result, pred, sprout::fixed_begin_offset(result), first);
			}
		}	// namespace detail
		//
		// stable_partition_copy
		//
		template<typename BidirectionalIterator, typename Result, typename Predicate>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type stable_partition_copy(
			BidirectionalIterator first,
			BidirectionalIterator last,
			Result const& result,
			Predicate pred
			)
		{
			return sprout::fixed::detail::stable_partition_copy_impl(first, last, result, pred);
		}
	}	// namespace fixed

	using sprout::fixed::stable_partition_copy;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_STABLE_PARTITION_COPY_HPP
