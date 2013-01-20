#ifndef SPROUT_ALGORITHM_FIXED_PARTITION_COPY_HPP
#define SPROUT_ALGORITHM_FIXED_PARTITION_COPY_HPP

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
			template<typename InputIterator, typename Result, typename Predicate, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			partition_copy_impl(
				InputIterator first, InputIterator last, Result const& result, Predicate pred,
				typename sprout::container_traits<Result>::size_type size,
				Args const&... args
				)
			{
				return sprout::remake<Result>(result, sprout::size(result), args...);
			}
			template<typename InputIterator, typename Result, typename Predicate, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
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
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
		partition_copy(InputIterator first, InputIterator last, Result const& result, Predicate pred) {
			return sprout::fixed::detail::partition_copy_impl(first, last, result, pred, sprout::size(result));
		}

		template<typename Result, typename InputIterator, typename Predicate>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
		partition_copy(InputIterator first, InputIterator last, Predicate pred) {
			return sprout::fixed::partition_copy(first, last, sprout::pit<Result>(), pred);
		}
	}	// namespace fixed

	using sprout::fixed::partition_copy;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_PARTITION_COPY_HPP
