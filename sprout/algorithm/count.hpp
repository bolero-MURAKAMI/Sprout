#ifndef SPROUT_ALGORITHM_COUNT_HPP
#define SPROUT_ALGORITHM_COUNT_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator, typename T>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<RandomAccessIterator>::difference_type
		count_impl_ra(
			RandomAccessIterator first, RandomAccessIterator last, T const& value,
			typename std::iterator_traits<RandomAccessIterator>::difference_type pivot
			)
		{
			return pivot == 0 ? (*first == value ? 1 : 0)
				: sprout::detail::count_impl_ra(
					first, sprout::next(first, pivot), value,
					pivot / 2
					)
					+ sprout::detail::count_impl_ra(
						sprout::next(first, pivot), last, value,
						(NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) - pivot) / 2
						)
				;
		}
		template<typename RandomAccessIterator, typename T>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<RandomAccessIterator>::difference_type
		count(
			RandomAccessIterator first, RandomAccessIterator last, T const& value,
			std::random_access_iterator_tag*
			)
		{
			return first == last ? 0
				: sprout::detail::count_impl_ra(first, last, value, NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) / 2)
				;
		}

		// Copyright (C) 2011 RiSK (sscrisk)
		template<typename InputIterator, typename T>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
		count_impl(InputIterator first, InputIterator last, T const& value) {
			return first == last ? 0
				: (*first == value ? 1 : 0) + sprout::detail::count_impl(sprout::next(first), last, value)
				;
		}
		template<typename InputIterator, typename T>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
		count(
			InputIterator first, InputIterator last, T const& value,
			void*
			)
		{
			return sprout::detail::count_impl(first, last, value);
		}
	}	//namespace detail

	// 25.2.9 Count
	//
	//	recursion depth:
	//		[first, last) is RandomAccessIterator -> O(log N)
	//		otherwise -> O(N)
	//
	template<typename InputIterator, typename T>
	inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
	count(InputIterator first, InputIterator last, T const& value) {
		typedef typename std::iterator_traits<InputIterator>::iterator_category* category;
		return sprout::detail::count(first, last, value, category());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_COUNT_HPP
