#ifndef SPROUT_ALGORITHM_FIXED_UNIQUE_COPY_HPP
#define SPROUT_ALGORITHM_FIXED_UNIQUE_COPY_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/detail/container_complate.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename InputIterator, typename Result, typename Head, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args) + 1,
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type unique_copy_impl(
				InputIterator first,
				InputIterator last,
				Result const& result,
				typename sprout::container_traits<Result>::size_type size,
				Head const& head,
				Args const&... args
				)
			{
				return sprout::remake<Result>(result, sprout::size(result), args..., head);
			}
			template<typename InputIterator, typename Result, typename Head, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args) + 1,
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type unique_copy_impl(
				InputIterator first,
				InputIterator last,
				Result const& result,
				typename sprout::container_traits<Result>::size_type size,
				Head const& head,
				Args const&... args
				)
			{
				return first != last && sizeof...(Args) + 1 < size
					? !(head == *first)
						? unique_copy_impl(sprout::next(first), last, result, size, *first, args..., head)
						: unique_copy_impl(sprout::next(first), last, result, size, head, args...)
					: sprout::detail::container_complate(result, args..., head)
					;
			}
		}	// namespace detail
		//
		// unique_copy
		//
		template<typename InputIterator, typename Result>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type unique_copy(
			InputIterator first,
			InputIterator last,
			Result const& result
			)
		{
			return first != last
				? sprout::fixed::detail::unique_copy_impl(sprout::next(first), last, result, sprout::size(result), *first)
				: sprout::detail::container_complate(result)
				;
		}

		namespace detail {
			template<typename InputIterator, typename Result, typename BinaryPredicate, typename Head, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args) + 1,
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type unique_copy_impl(
				InputIterator first,
				InputIterator last,
				Result const& result,
				BinaryPredicate pred,
				typename sprout::container_traits<Result>::size_type size,
				Head const& head,
				Args const&... args
				)
			{
				return sprout::remake<Result>(result, sprout::size(result), args..., head);
			}
			template<typename InputIterator, typename Result, typename BinaryPredicate, typename Head, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args) + 1,
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type unique_copy_impl(
				InputIterator first,
				InputIterator last,
				Result const& result,
				BinaryPredicate pred,
				typename sprout::container_traits<Result>::size_type size,
				Head const& head,
				Args const&... args
				)
			{
				return first != last && sizeof...(Args) + 1 < size
					? !pred(head, *first)
						? sprout::fixed::detail::unique_copy_impl(sprout::next(first), last, result, pred, size, *first, args..., head)
						: sprout::fixed::detail::unique_copy_impl(sprout::next(first), last, result, pred, size, head, args...)
					: sprout::detail::container_complate(result, args..., head)
					;
			}
		}	// namespace detail
		//
		// unique_copy
		//
		template<typename InputIterator, typename Result, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type unique_copy(
			InputIterator first,
			InputIterator last,
			Result const& result,
			BinaryPredicate pred
			)
		{
			return first != last
				? sprout::fixed::detail::unique_copy_impl(sprout::next(first), last, result, pred, sprout::size(result), *first)
				: sprout::detail::container_complate(result)
				;
		}
	}	// namespace fixed

	using sprout::fixed::unique_copy;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_UNIQUE_COPY_HPP
