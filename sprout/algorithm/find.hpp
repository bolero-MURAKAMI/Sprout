#ifndef SPROUT_ALGORITHM_FIND_HPP
#define SPROUT_ALGORITHM_FIND_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator, typename T>
		inline SPROUT_CONSTEXPR RandomAccessIterator
		find_impl_ra(
			RandomAccessIterator first, RandomAccessIterator last, T const& value,
			typename std::iterator_traits<RandomAccessIterator>::difference_type pivot, RandomAccessIterator found
			)
		{
			return found != first ? found
				: pivot == 0 ? (*first == value ? first : last)
				: sprout::detail::find_impl_ra(
					sprout::next(first, pivot), last, value,
					(NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) - pivot) / 2,
					sprout::detail::find_impl_ra(
						first, sprout::next(first, pivot), value,
						pivot / 2,
						first
						)
					)
				;
		}
		template<typename RandomAccessIterator, typename T>
		inline SPROUT_CONSTEXPR RandomAccessIterator
		find(
			RandomAccessIterator first, RandomAccessIterator last, T const& value,
			std::random_access_iterator_tag*
			)
		{
			return first == last ? first
				: sprout::detail::find_impl_ra(first, last, value, NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) / 2, first)
				;
		}

		// Copyright (C) 2011 RiSK (sscrisk)
		template<typename InputIterator, typename T>
		inline SPROUT_CONSTEXPR InputIterator
		find_impl(InputIterator first, InputIterator last, T const& value) {
			return first == last || *first == value ? first
				: sprout::detail::find_impl(sprout::next(first), last, value)
				;
		}
		template<typename InputIterator, typename T>
		inline SPROUT_CONSTEXPR InputIterator
		find(
			InputIterator first, InputIterator last, T const& value,
			void*
			)
		{
			return sprout::detail::find_impl(first, last, value);
		}
	}	//namespace detail

	// 25.2.5 Find
	template<typename InputIterator, typename T>
	inline SPROUT_CONSTEXPR InputIterator
	find(InputIterator first, InputIterator last, T const& value) {
		typedef typename std::iterator_traits<InputIterator>::iterator_category* category;
		return sprout::detail::find(first, last, value, category());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIND_HPP
