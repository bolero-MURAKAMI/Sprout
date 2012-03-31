#ifndef SPROUT_ALGORITHM_FIXED_MERGE_HPP
#define SPROUT_ALGORITHM_FIXED_MERGE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/detail/container_complate.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename InputIterator1, typename InputIterator2, typename Result, typename Compare, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type merge_impl(
				InputIterator1 first1,
				InputIterator1 last1,
				InputIterator2 first2,
				InputIterator2 last2,
				Result const& result,
				Compare comp,
				typename sprout::container_traits<Result>::size_type size,
				Args const&... args
				)
			{
				return sprout::remake<Result>(result, sprout::size(result), args...);
			}
			template<typename InputIterator1, typename InputIterator2, typename Result, typename Compare, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type merge_impl(
				InputIterator1 first1,
				InputIterator1 last1,
				InputIterator2 first2,
				InputIterator2 last2,
				Result const& result,
				Compare comp,
				typename sprout::container_traits<Result>::size_type size,
				Args const&... args
				)
			{
				return sizeof...(Args) < size
					? first1 != last1
						? first2 != last2
							? comp(*first2, *first1)
								? sprout::fixed::detail::merge_impl(first1, last1, sprout::next(first2), last2, result, comp, size, args..., *first2)
								: sprout::fixed::detail::merge_impl(sprout::next(first1), last1, first2, last2, result, comp, size, args..., *first1)
							: sprout::fixed::detail::merge_impl(sprout::next(first1), last1, first2, last2, result, comp, size, args..., *first1)
						: first2 != last2
							? sprout::fixed::detail::merge_impl(first1, last1, sprout::next(first2), last2, result, comp, size, args..., *first2)
						: sprout::detail::container_complate(result, args...)
					: sprout::detail::container_complate(result, args...)
					;
			}
		}	// namespace detail
		//
		// merge
		//
		template<typename InputIterator1, typename InputIterator2, typename Result, typename Compare>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type merge(
			InputIterator1 first1,
			InputIterator1 last1,
			InputIterator2 first2,
			InputIterator2 last2,
			Result const& result,
			Compare comp
			)
		{
			return sprout::fixed::detail::merge_impl(
				first1,
				last1,
				first2,
				last2,
				result,
				comp,
				sprout::size(result)
				);
		}
		//
		// merge
		//
		template<typename InputIterator1, typename InputIterator2, typename Result>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type merge(
			InputIterator1 first1,
			InputIterator1 last1,
			InputIterator2 first2,
			InputIterator2 last2,
			Result const& result
			)
		{
			return sprout::fixed::detail::merge_impl(
				first1,
				last1,
				first2,
				last2,
				result,
				NS_SSCRISK_CEL_OR_SPROUT_DETAIL::less<typename sprout::container_traits<Result>::value_type>(),
				sprout::size(result)
				);
		}
	}	// namespace fixed

	using sprout::fixed::merge;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_MERGE_HPP
