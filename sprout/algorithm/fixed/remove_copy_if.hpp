#ifndef SPROUT_ALGORITHM_FIXED_REMOVE_COPY_IF_HPP
#define SPROUT_ALGORITHM_FIXED_REMOVE_COPY_IF_HPP

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
			template<typename InputIterator, typename Result, typename Predicate, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type remove_copy_if_impl(
				InputIterator first,
				InputIterator last,
				Result const& result,
				Predicate pred,
				typename sprout::container_traits<Result>::size_type size,
				Args const&... args
				)
			{
				return sprout::remake<Result>(result, sprout::size(result), args...);
			}
			template<typename InputIterator, typename Result, typename Predicate, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type remove_copy_if_impl(
				InputIterator first,
				InputIterator last,
				Result const& result,
				Predicate pred,
				typename sprout::container_traits<Result>::size_type size,
				Args const&... args
				)
			{
				return first != last && sizeof...(Args) < size
					? pred(*first)
						? sprout::fixed::detail::remove_copy_if_impl(sprout::next(first), last, result, pred, size, args...)
						: sprout::fixed::detail::remove_copy_if_impl(sprout::next(first), last, result, pred, size, args..., *first)
					: sprout::detail::container_complate(result, args...)
					;
			}
		}	// namespace detail
		//
		// remove_copy_if
		//
		template<typename InputIterator, typename Result, typename Predicate>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type remove_copy_if(
			InputIterator first,
			InputIterator last,
			Result const& result,
			Predicate pred
			)
		{
			return sprout::fixed::detail::remove_copy_if_impl(first, last, result, pred, sprout::size(result));
		}
	}	// namespace fixed

	using sprout::fixed::remove_copy_if;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_REMOVE_COPY_IF_HPP
