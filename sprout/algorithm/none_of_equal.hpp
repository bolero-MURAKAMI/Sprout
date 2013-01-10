#ifndef SPROUT_ALGORITHM_NONE_OF_EQUAL_HPP
#define SPROUT_ALGORITHM_NONE_OF_EQUAL_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator, typename T>
		inline SPROUT_CONSTEXPR bool
		none_of_equal_impl_ra(
			RandomAccessIterator first, RandomAccessIterator last, T const& value,
			typename std::iterator_traits<RandomAccessIterator>::difference_type pivot
			)
		{
			return pivot == 0 ? !(*first == value)
				: sprout::detail::none_of_equal_impl_ra(
					first, sprout::next(first, pivot), value,
					pivot / 2
					)
					&& sprout::detail::none_of_equal_impl_ra(
						sprout::next(first, pivot), last, value,
						(sprout::distance(first, last) - pivot) / 2
						)
				;
		}
		template<typename RandomAccessIterator, typename T>
		inline SPROUT_CONSTEXPR bool
		none_of_equal(
			RandomAccessIterator first, RandomAccessIterator last, T const& value,
			std::random_access_iterator_tag*
			)
		{
			return first == last ? true
				: sprout::detail::none_of_equal_impl_ra(first, last, value, sprout::distance(first, last) / 2)
				;
		}

		template<typename InputIterator, typename T>
		inline SPROUT_CONSTEXPR bool
		none_of_equal_impl(InputIterator first, InputIterator last, T const& value) {
			return first == last ? true
				: !(*first == value) && sprout::detail::none_of_equal_impl(sprout::next(first), last, value)
				;
		}
		template<typename InputIterator, typename T>
		inline SPROUT_CONSTEXPR bool
		none_of_equal(
			InputIterator first, InputIterator last, T const& value,
			void*
			)
		{
			return sprout::detail::none_of_equal_impl(first, last, value);
		}
	}	// namespace detail

	//
	// none_of_equal
	//
	//	recursion depth:
	//		[first, last) is RandomAccessIterator -> O(log N)
	//		otherwise -> O(N)
	//
	template<typename InputIterator, typename T>
	inline SPROUT_CONSTEXPR bool
	none_of_equal(InputIterator first, InputIterator last, T const& value) {
		typedef typename std::iterator_traits<InputIterator>::iterator_category* category;
		return sprout::detail::none_of_equal(first, last, value, category());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_NONE_OF_EQUAL_HPP
