#ifndef SPROUT_ALGORITHM_FIXED_PARTITION_COPY_HPP
#define SPROUT_ALGORITHM_FIXED_PARTITION_COPY_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename Result, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type partition_copy_impl_3(
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
			>::type partition_copy_impl_3(
				Result const& result,
				Args const&... args
				)
			{
				return partition_copy_impl_3(result, args..., *(sprout::fixed_begin(result) + sizeof...(Args)));
			}
			template<typename Iterator, typename Result, typename Predicate, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type partition_copy_impl_2(
				Iterator first,
				Iterator last,
				Result const& result,
				Predicate pred,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return sprout::remake_clone<Result, Result>(result, sprout::size(result), args...);
			}
			template<typename Iterator, typename Result, typename Predicate, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type partition_copy_impl_2(
				Iterator first,
				Iterator last,
				Result const& result,
				Predicate pred,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return first != last && sizeof...(Args) < offset
					? pred(*first)
						? partition_copy_impl_2(first + 1, last, result, pred, offset, *first, args...)
						: partition_copy_impl_2(first + 1, last, result, pred, offset, args..., *first)
					: partition_copy_impl_3(result, args...)
					;
			}
			template<typename Iterator, typename Result, typename Predicate, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type partition_copy_impl_1(
				Iterator first,
				Iterator last,
				Result const& result,
				Predicate pred,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return sprout::remake_clone<Result, Result>(result, sprout::size(result), args...);
			}
			template<typename Iterator, typename Result, typename Predicate, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type partition_copy_impl_1(
				Iterator first,
				Iterator last,
				Result const& result,
				Predicate pred,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return sizeof...(Args) < offset
					? partition_copy_impl_1(first, last, result, pred, offset, args..., *(sprout::fixed_begin(result) + sizeof...(Args)))
					: partition_copy_impl_2(first, last, result, pred, offset + sprout::size(result), args...)
					;
			}
			template<typename Iterator, typename Result, typename Predicate>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type partition_copy_impl(
				Iterator first,
				Iterator last,
				Result const& result,
				Predicate pred
				)
			{
				return partition_copy_impl_1(first, last, result, pred, sprout::fixed_begin_offset(result));
			}
		}	// namespace detail
		//
		// partition_copy
		//
		template<typename Iterator, typename Result, typename Predicate>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type partition_copy(
			Iterator first,
			Iterator last,
			Result const& result,
			Predicate pred
			)
		{
			return sprout::fixed::detail::partition_copy_impl(first, last, result, pred);
		}
	}	// namespace fixed

	using sprout::fixed::partition_copy;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_PARTITION_COPY_HPP
