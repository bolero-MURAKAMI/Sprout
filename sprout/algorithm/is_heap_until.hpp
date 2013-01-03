#ifndef SPROUT_ALGORITHM_IS_HEAP_UNTIL_HPP
#define SPROUT_ALGORITHM_IS_HEAP_UNTIL_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator, typename Compare>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<RandomAccessIterator>::difference_type
		is_heap_until_impl(
			RandomAccessIterator it, Compare comp,
			typename std::iterator_traits<RandomAccessIterator>::difference_type first, typename std::iterator_traits<RandomAccessIterator>::difference_type last,
			typename std::iterator_traits<RandomAccessIterator>::difference_type pivot, typename std::iterator_traits<RandomAccessIterator>::difference_type found
			)
		{
			return found != first ? found
				: pivot == 0 ? (!comp(it[first], it[(first - 1) / 2]) ? first : last)
				: sprout::detail::is_heap_until_impl(
					it, comp, first + pivot, last,
					((last - first) - pivot) / 2,
					sprout::detail::is_heap_until_impl(
						it, comp, first, first + pivot,
						pivot / 2,
						first
						)
					)
				;
		}

		template<typename RandomAccessIterator, typename Compare>
		inline SPROUT_CONSTEXPR RandomAccessIterator
		is_heap_until_impl(
			RandomAccessIterator first, RandomAccessIterator last, Compare comp,
			typename std::iterator_traits<RandomAccessIterator>::difference_type size
			)
		{
			return size < 2 ? last
				: sprout::next(first, sprout::detail::is_heap_until_impl(first, comp, 1, size, (size - 1) / 2, 1))
				;
		}
	}	// namespace detail

	// 25.4.6.5 is_heap
	//
	//	recursion depth:
	//		O(log N)
	//
	template<typename RandomAccessIterator, typename Compare>
	inline SPROUT_CONSTEXPR RandomAccessIterator
	is_heap_until(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
		return sprout::detail::is_heap_until_impl(
			first, last, comp,
			sprout::distance(first, last)
			);
	}

	template<typename RandomAccessIterator>
	inline SPROUT_CONSTEXPR RandomAccessIterator
	is_heap_until(RandomAccessIterator first, RandomAccessIterator last) {
		return sprout::is_heap_until(
			first, last,
			NS_SSCRISK_CEL_OR_SPROUT::less<typename std::iterator_traits<RandomAccessIterator>::value_type>()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_IS_HEAP_UNTIL_HPP
