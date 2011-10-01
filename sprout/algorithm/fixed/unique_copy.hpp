#ifndef SPROUT_ALGORITHM_FIXED_UNIQUE_COPY_HPP
#define SPROUT_ALGORITHM_FIXED_UNIQUE_COPY_HPP

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
			>::type unique_copy_impl_3(
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
			>::type unique_copy_impl_3(
				Result const& result,
				Args const&... args
				)
			{
				return unique_copy_impl_3(result, args..., *(sprout::fixed_begin(result) + sizeof...(Args)));
			}
			template<typename Iterator, typename Result, typename Head, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args) + 1,
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type unique_copy_impl_2(
				Iterator first,
				Iterator last,
				Result const& result,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Head const& head,
				Args const&... args
				)
			{
				return sprout::remake_clone<Result, Result>(result, sprout::size(result), args...);
			}
			template<typename Iterator, typename Result, typename Head, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args) + 1,
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type unique_copy_impl_2(
				Iterator first,
				Iterator last,
				Result const& result,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Head const& head,
				Args const&... args
				)
			{
				return first != last && sizeof...(Args) + 1 < offset
					? !(head == *first)
						? unique_copy_impl_2(first + 1, last, result, offset, *first, args..., head)
						: unique_copy_impl_2(first + 1, last, result, offset, head, args...)
					: unique_copy_impl_3(result, args..., head)
					;
			}
			template<typename Iterator, typename Result, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type unique_copy_impl_1(
				Iterator first,
				Iterator last,
				Result const& result,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return sprout::remake_clone<Result, Result>(result, sprout::size(result), args...);
			}
			template<typename Iterator, typename Result, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type unique_copy_impl_1(
				Iterator first,
				Iterator last,
				Result const& result,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return sizeof...(Args) < offset
					? unique_copy_impl_1(first, last, result, offset, args..., *(sprout::fixed_begin(result) + sizeof...(Args)))
					: unique_copy_impl_2(first + 1, last, result, offset + sprout::size(result), *first, args...)
					;
			}
			template<typename Iterator, typename Result>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type unique_copy_impl(
				Iterator first,
				Iterator last,
				Result const& result
				)
			{
				return unique_copy_impl_1(first, last, result, sprout::fixed_begin_offset(result));
			}
		}	// namespace detail
		//
		// unique_copy
		//
		template<typename Iterator, typename Result>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type unique_copy(
			Iterator first,
			Iterator last,
			Result const& result
			)
		{
			return sprout::fixed::detail::unique_copy_impl(first, last, result);
		}

		namespace detail {
			template<typename Iterator, typename Result, typename BinaryPredicate, typename Head, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args) + 1,
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type unique_copy_impl_2(
				Iterator first,
				Iterator last,
				Result const& result,
				BinaryPredicate pred,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Head const& head,
				Args const&... args
				)
			{
				return sprout::remake_clone<Result, Result>(result, sprout::size(result), args...);
			}
			template<typename Iterator, typename Result, typename BinaryPredicate, typename Head, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args) + 1,
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type unique_copy_impl_2(
				Iterator first,
				Iterator last,
				Result const& result,
				BinaryPredicate pred,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Head const& head,
				Args const&... args
				)
			{
				return first != last && sizeof...(Args) + 1 < offset
					? !pred(head, *first)
						? unique_copy_impl_2(first + 1, last, result, pred, offset, *first, args..., head)
						: unique_copy_impl_2(first + 1, last, result, pred, offset, head, args...)
					: unique_copy_impl_3(result, args..., head)
					;
			}
			template<typename Iterator, typename Result, typename BinaryPredicate, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type unique_copy_impl_1(
				Iterator first,
				Iterator last,
				Result const& result,
				BinaryPredicate pred,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return sprout::remake_clone<Result, Result>(result, sprout::size(result), args...);
			}
			template<typename Iterator, typename Result, typename BinaryPredicate, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type unique_copy_impl_1(
				Iterator first,
				Iterator last,
				Result const& result,
				BinaryPredicate pred,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return sizeof...(Args) < offset
					? unique_copy_impl_1(first, last, result, pred, offset, args..., *(sprout::fixed_begin(result) + sizeof...(Args)))
					: unique_copy_impl_2(first + 1, last, result, pred, offset + sprout::size(result), *first, args...)
					;
			}
			template<typename Iterator, typename Result, typename BinaryPredicate>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type unique_copy_impl(
				Iterator first,
				Iterator last,
				Result const& result,
				BinaryPredicate pred
				)
			{
				return unique_copy_impl_1(first, last, result, pred, sprout::fixed_begin_offset(result));
			}
		}	// namespace detail
		//
		// unique_copy
		//
		template<typename Iterator, typename Result, typename BinaryPredicate>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type unique_copy(
			Iterator first,
			Iterator last,
			Result const& result,
			BinaryPredicate pred
			)
		{
			return sprout::fixed::detail::unique_copy_impl(first, last, result, pred);
		}
	}	// namespace fixed

	using sprout::fixed::unique_copy;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_UNIQUE_COPY_HPP
