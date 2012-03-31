#ifndef SPROUT_ALGORITHM_FIXED_REMOVE_COPY_HPP
#define SPROUT_ALGORITHM_FIXED_REMOVE_COPY_HPP

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
			template<typename InputIterator, typename Result, typename T, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type remove_copy_impl(
				InputIterator first,
				InputIterator last,
				Result const& result,
				T const& value,
				typename sprout::container_traits<Result>::size_type size,
				Args const&... args
				)
			{
				return sprout::remake<Result>(result, sprout::size(result), args...);
			}
			template<typename InputIterator, typename Result, typename T, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type remove_copy_impl(
				InputIterator first,
				InputIterator last,
				Result const& result,
				T const& value,
				typename sprout::container_traits<Result>::size_type size,
				Args const&... args
				)
			{
				return first != last && sizeof...(Args) < size
					? *first == value
						? sprout::fixed::detail::remove_copy_impl(sprout::next(first), last, result, value, size, args...)
						: sprout::fixed::detail::remove_copy_impl(sprout::next(first), last, result, value, size, args..., *first)
					: sprout::detail::container_complate(result, args...)
					;
			}
		}	// namespace detail
		//
		// remove_copy
		//
		template<typename InputIterator, typename Result, typename T>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type remove_copy(
			InputIterator first,
			InputIterator last,
			Result const& result,
			T const& value
			)
		{
			return sprout::fixed::detail::remove_copy_impl(first, last, result, value, sprout::size(result));
		}
	}	// namespace fixed

	using sprout::fixed::remove_copy;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_REMOVE_COPY_HPP
