#ifndef SPROUT_ALGORITHM_IS_HEAP_UNTIL_HPP
#define SPROUT_ALGORITHM_IS_HEAP_UNTIL_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	namespace detail {
		template<typename RandomAccessIterator, typename Compare>
		inline SPROUT_CONSTEXPR RandomAccessIterator is_heap_until_impl(
			RandomAccessIterator first,
			RandomAccessIterator last,
			Compare comp,
			std::size_t n
			)
		{
			return sprout::next(first, n) == last || !comp(first[n], first[(n - 1) / 2]) ? sprout::next(first, n)
				: sprout::detail::is_heap_until_impl(first, last, comp, n + 1)
				;
		}
	}	// namespace detail

	// 25.4.6.5 is_heap
	template<typename RandomAccessIterator>
	inline SPROUT_CONSTEXPR RandomAccessIterator is_heap_until(RandomAccessIterator first, RandomAccessIterator last) {
		return sprout::is_heap_until(first, last, NS_SSCRISK_CEL_OR_SPROUT::less<decltype(*first)>());
	}

	template<typename RandomAccessIterator, typename Compare>
	inline SPROUT_CONSTEXPR RandomAccessIterator is_heap_until(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
		return NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) < 2 ? last : sprout::detail::is_heap_until_impl(first, last, comp, 1);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_IS_HEAP_UNTIL_HPP
