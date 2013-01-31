#ifndef SPROUT_ALGORITHM_FIXED_UNIQUE_COPY_HPP
#define SPROUT_ALGORITHM_FIXED_UNIQUE_COPY_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/unique_iterator.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/pit.hpp>
#include <sprout/detail/container_complate.hpp>
#include <sprout/iterator/type_traits/is_iterator.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename InputIterator, typename Result, typename Head, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args) + 1,
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			unique_copy_impl(
				InputIterator first, InputIterator last,
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
			>::type
			unique_copy_impl(
				InputIterator first, InputIterator last,
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

			template<typename InputIterator, typename Result>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::is_fixed_container<Result>::value,
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			unique_copy(InputIterator first, InputIterator last, Result const& result) {
				return first != last
					? sprout::fixed::detail::unique_copy_impl(sprout::next(first), last, result, sprout::size(result), *first)
					: sprout::detail::container_complate(result)
					;
			}

			template<typename InputIterator, typename Result>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				!sprout::is_fixed_container<Result>::value,
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			unique_copy(InputIterator first, InputIterator last, Result const& result) {
				static_assert(sprout::is_forward_iterator<InputIterator>::value, "Sorry, not implemented.");
				return sprout::remake<Result>(
					result, sprout::size(result),
					sprout::make_unique_iterator(first, last),
					sprout::make_unique_iterator(last, last)
					);
			}
		}	// namespace detail
		//
		// unique_copy
		//
		template<typename InputIterator, typename Result>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
		unique_copy(InputIterator first, InputIterator last, Result const& result) {
			return sprout::fixed::detail::unique_copy(first, last, result);
		}

		template<typename Result, typename InputIterator>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
		unique_copy(InputIterator first, InputIterator last) {
			return sprout::fixed::unique_copy(first, last, sprout::pit<Result>());
		}

		namespace detail {
			template<typename InputIterator, typename Result, typename BinaryPredicate, typename Head, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args) + 1,
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			unique_copy_impl(
				InputIterator first, InputIterator last,
				Result const& result, BinaryPredicate pred,
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
			>::type
			unique_copy_impl(
				InputIterator first, InputIterator last,
				Result const& result, BinaryPredicate pred,
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

			template<typename InputIterator, typename Result, typename BinaryPredicate>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::is_fixed_container<Result>::value,
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			unique_copy(InputIterator first, InputIterator last, Result const& result, BinaryPredicate pred) {
				return first != last
					? sprout::fixed::detail::unique_copy_impl(sprout::next(first), last, result, pred, sprout::size(result), *first)
					: sprout::detail::container_complate(result)
					;
			}

			template<typename InputIterator, typename Result, typename BinaryPredicate>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				!sprout::is_fixed_container<Result>::value,
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			unique_copy(InputIterator first, InputIterator last, Result const& result, BinaryPredicate pred) {
				static_assert(sprout::is_forward_iterator<InputIterator>::value, "Sorry, not implemented.");
				return sprout::remake<Result>(
					result, sprout::size(result),
					sprout::make_unique_iterator(pred, first, last),
					sprout::make_unique_iterator(pred, last, last)
					);
			}
		}	// namespace detail
		//
		// unique_copy
		//
		template<typename InputIterator, typename Result, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
		unique_copy(InputIterator first, InputIterator last, Result const& result, BinaryPredicate pred) {
			return sprout::fixed::detail::unique_copy(first, last, result, pred);
		}

		template<typename Result, typename InputIterator, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
		unique_copy(InputIterator first, InputIterator last, BinaryPredicate pred) {
			return sprout::fixed::unique_copy(first, last, sprout::pit<Result>(), pred);
		}
	}	// namespace fixed

	using sprout::fixed::unique_copy;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_UNIQUE_COPY_HPP
