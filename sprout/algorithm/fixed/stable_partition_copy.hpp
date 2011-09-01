#ifndef SPROUT_ALGORITHM_FIXED_STABLE_PARTITION_COPY_HPP
#define SPROUT_ALGORITHM_FIXED_STABLE_PARTITION_COPY_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename Result, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed_container_traits<Result>::fixed_container_type
			>::type stable_partition_copy_impl_4(
				Result const& result,
				Args const&... args
				)
			{
				return typename sprout::fixed_container_traits<Result>::fixed_container_type{args...};
			}
			template<typename Result, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args),
				typename sprout::fixed_container_traits<Result>::fixed_container_type
			>::type stable_partition_copy_impl_4(
				Result const& result,
				Args const&... args
				)
			{
				return stable_partition_copy_impl_4(result, args..., *(sprout::fixed_begin(result) + sizeof...(Args)));
			}

			template<typename Iterator, typename Result, typename Predicate, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed_container_traits<Result>::fixed_container_type
			>::type stable_partition_copy_impl_3(
				Iterator first,
				Iterator last,
				Result const& result,
				Predicate pred,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return typename sprout::fixed_container_traits<Result>::fixed_container_type{args...};
			}
			template<typename Iterator, typename Result, typename Predicate, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args),
				typename sprout::fixed_container_traits<Result>::fixed_container_type
			>::type stable_partition_copy_impl_3(
				Iterator first,
				Iterator last,
				Result const& result,
				Predicate pred,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return first != last && sizeof...(Args) < offset
					? !pred(*first)
						? stable_partition_copy_impl_3(first + 1, last, result, pred, offset, args..., *first)
						: stable_partition_copy_impl_3(first + 1, last, result, pred, offset, args...)
					: stable_partition_copy_impl_4(result, args...)
					;
			}

			template<typename Iterator, typename Result, typename Predicate, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed_container_traits<Result>::fixed_container_type
			>::type stable_partition_copy_impl_2(
				Iterator first,
				Iterator last,
				Result const& result,
				Predicate pred,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Iterator origin,
				Args const&... args
				)
			{
				return typename sprout::fixed_container_traits<Result>::fixed_container_type{args...};
			}
			template<typename Iterator, typename Result, typename Predicate, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args),
				typename sprout::fixed_container_traits<Result>::fixed_container_type
			>::type stable_partition_copy_impl_2(
				Iterator first,
				Iterator last,
				Result const& result,
				Predicate pred,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Iterator origin,
				Args const&... args
				)
			{
				return first != last && sizeof...(Args) < offset
					? pred(*first)
						? stable_partition_copy_impl_2(first + 1, last, result, pred, offset, origin, args..., *first)
						: stable_partition_copy_impl_2(first + 1, last, result, pred, offset, origin, args...)
					: stable_partition_copy_impl_3(origin, last, result, pred, offset, args...)
					;
			}
			template<typename Iterator, typename Result, typename Predicate, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed_container_traits<Result>::fixed_container_type
			>::type stable_partition_copy_impl_1(
				Iterator first,
				Iterator last,
				Result const& result,
				Predicate pred,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Iterator origin,
				Args const&... args
				)
			{
				return typename sprout::fixed_container_traits<Result>::fixed_container_type{args...};
			}
			template<typename Iterator, typename Result, typename Predicate, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args),
				typename sprout::fixed_container_traits<Result>::fixed_container_type
			>::type stable_partition_copy_impl_1(
				Iterator first,
				Iterator last,
				Result const& result,
				Predicate pred,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Iterator origin,
				Args const&... args
				)
			{
				return sizeof...(Args) < offset
					? stable_partition_copy_impl_1(first, last, result, pred, offset, origin, args..., *(sprout::fixed_begin(result) + sizeof...(Args)))
					: stable_partition_copy_impl_2(first, last, result, pred, offset + sprout::size(result), origin, args...)
					;
			}
			template<typename Iterator, typename Result, typename Predicate>
			SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Result>::fixed_container_type stable_partition_copy_impl(
				Iterator first,
				Iterator last,
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
		template<typename Iterator, typename Result, typename Predicate>
		SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Result>::fixed_container_type stable_partition_copy(
			Iterator first,
			Iterator last,
			Result const& result,
			Predicate pred
			)
		{
			return sprout::fixed::detail::stable_partition_copy_impl(first, last, result, pred);
		}
	}	// namespace fixed
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_STABLE_PARTITION_COPY_HPP
