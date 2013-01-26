#ifndef SPROUT_ALGORITHM_FIXED_SET_SYMMETRIC_DIFFERENCE_HPP
#define SPROUT_ALGORITHM_FIXED_SET_SYMMETRIC_DIFFERENCE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/set_symmetric_difference_iterator.hpp>
#include <sprout/functional/less.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/pit.hpp>
#include <sprout/detail/container_complate.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename InputIterator1, typename InputIterator2, typename Result, typename Compare, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			set_symmetric_difference_impl(
				InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2, InputIterator2 last2,
				Result const& result, Compare comp,
				typename sprout::container_traits<Result>::size_type size,
				Args const&... args
				)
			{
				return sprout::remake<Result>(result, sprout::size(result), args...);
			}
			template<typename InputIterator1, typename InputIterator2, typename Result, typename Compare, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			set_symmetric_difference_impl(
				InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2, InputIterator2 last2,
				Result const& result, Compare comp,
				typename sprout::container_traits<Result>::size_type size,
				Args const&... args
				)
			{
				return sizeof...(Args) < size
					? first1 != last1
						? first2 != last2
							? comp(*first1, *first2)
								? sprout::fixed::detail::set_symmetric_difference_impl(
									sprout::next(first1), last1, first2, last2, result, comp,
									size, args..., *first1
									)
								: comp(*first2, *first1)
									? sprout::fixed::detail::set_symmetric_difference_impl(
										first1, last1, sprout::next(first2), last2, result, comp,
										size, args..., *first2
										)
									: sprout::fixed::detail::set_symmetric_difference_impl(
										sprout::next(first1), last1, sprout::next(first2), last2, result, comp,
										size, args...
										)
							: sprout::fixed::detail::set_symmetric_difference_impl(
								sprout::next(first1), last1, first2, last2, result, comp,
								size, args..., *first1
								)
						: first2 != last2
							? sprout::fixed::detail::set_symmetric_difference_impl(
								first1, last1, sprout::next(first2), last2, result, comp,
								size, args..., *first2
								)
							: sprout::detail::container_complate(result, args...)
					: sprout::detail::container_complate(result, args...)
					;
			}

			template<typename InputIterator1, typename InputIterator2, typename Result, typename Compare>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::is_fixed_container<Result>::value,
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			set_symmetric_difference(
				InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2, InputIterator2 last2,
				Result const& result, Compare comp
				)
			{
				return sprout::fixed::detail::set_symmetric_difference_impl(
					first1, last1,
					first2, last2,
					result, comp,
					sprout::size(result)
					);
			}

			template<typename InputIterator1, typename InputIterator2, typename Result, typename Compare>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				!sprout::is_fixed_container<Result>::value,
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			set_symmetric_difference(
				InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2, InputIterator2 last2,
				Result const& result, Compare comp
				)
			{
				return sprout::remake<Result>(
					result, sprout::size(result),
					sprout::make_set_symmetric_difference_iterator(first1, last1, first2, last2, comp),
					sprout::make_set_symmetric_difference_iterator(last1, last1, last2, last2, comp)
					);
			}
		}	// namespace detail
		//
		// set_symmetric_difference
		//
		template<typename InputIterator1, typename InputIterator2, typename Result, typename Compare>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
		set_symmetric_difference(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2,
			Result const& result, Compare comp
			)
		{
			return sprout::fixed::detail::set_symmetric_difference(first1, last1, first2, last2, result, comp);
		}
		template<typename InputIterator1, typename InputIterator2, typename Result>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
		set_symmetric_difference(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2,
			Result const& result
			)
		{
			return sprout::fixed::set_symmetric_difference(first1, last1, first2, last2, result, sprout::less<>());
		}

		template<typename Result, typename InputIterator1, typename InputIterator2, typename Compare>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
		set_symmetric_difference(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2,
			Compare comp
			)
		{
			return sprout::fixed::set_symmetric_difference(first1, last1, first2, last2, sprout::pit<Result>(), comp);
		}
		template<typename Result, typename InputIterator1, typename InputIterator2>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
		set_symmetric_difference(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2
			)
		{
			return sprout::fixed::set_symmetric_difference(first1, last1, first2, last2, sprout::pit<Result>());
		}
	}	// namespace fixed

	using sprout::fixed::set_symmetric_difference;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_SET_SYMMETRIC_DIFFERENCE_HPP
