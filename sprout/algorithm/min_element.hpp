#ifndef SPROUT_ALGORITHM_MIN_ELEMENT_HPP
#define SPROUT_ALGORITHM_MIN_ELEMENT_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/type_traits/category.hpp>
#include <sprout/utility/pair/pair.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace detail {
		template<typename ForwardIterator, typename Compare>
		inline SPROUT_CONSTEXPR ForwardIterator
		iter_min(ForwardIterator a, ForwardIterator b, Compare comp) {
			return comp(*b, *a) ? b : a;
		}

		template<typename RandomAccessIterator, typename Compare>
		inline SPROUT_CONSTEXPR RandomAccessIterator
		min_element_impl_ra(
			RandomAccessIterator first, RandomAccessIterator last, Compare comp,
			typename std::iterator_traits<RandomAccessIterator>::difference_type pivot
			)
		{
			return pivot == 0 ? first
				: sprout::detail::iter_min(
					sprout::detail::min_element_impl_ra(
						first, sprout::next(first, pivot), comp,
						pivot / 2
						),
					sprout::detail::min_element_impl_ra(
						sprout::next(first, pivot), last, comp,
						(sprout::distance(first, last) - pivot) / 2
						),
					comp
					)
				;
		}
		template<typename RandomAccessIterator, typename Compare>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_constant_distance_iterator<RandomAccessIterator>::value,
			RandomAccessIterator
		>::type
		min_element(
			RandomAccessIterator first, RandomAccessIterator last, Compare comp,
			std::random_access_iterator_tag*
			)
		{
			return first == last ? last
				: sprout::detail::min_element_impl_ra(
					first, last, comp,
					sprout::distance(first, last) / 2
					)
				;
		}

		template<typename ForwardIterator, typename Compare>
		inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator, ForwardIterator>
		min_element_impl_1(
			sprout::pair<ForwardIterator, ForwardIterator> const& current,
			ForwardIterator last, Compare comp, typename std::iterator_traits<ForwardIterator>::difference_type n
			)
		{
			typedef sprout::pair<ForwardIterator, ForwardIterator> type;
			return current.first == last ? current
				: n == 1 ? type(sprout::next(current.first), sprout::detail::iter_min(current.second, current.first, comp))
				: sprout::detail::min_element_impl_1(
					sprout::detail::min_element_impl_1(
						current,
						last, comp, n / 2
						),
					last, comp, n - n / 2
					)
				;
		}
		template<typename ForwardIterator, typename Compare>
		inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator, ForwardIterator>
		min_element_impl(
			sprout::pair<ForwardIterator, ForwardIterator> const& current,
			ForwardIterator last, Compare comp, typename std::iterator_traits<ForwardIterator>::difference_type n
			)
		{
			typedef sprout::pair<ForwardIterator, ForwardIterator> type;
			return current.first == last ? current
				: sprout::detail::min_element_impl(
					sprout::detail::min_element_impl_1(
						current,
						last, comp, n
						),
					last, comp, n * 2
					)
				;
		}
		template<typename ForwardIterator, typename Compare>
		inline SPROUT_CONSTEXPR ForwardIterator
		min_element(
			ForwardIterator first, ForwardIterator last, Compare comp,
			std::forward_iterator_tag*
			)
		{
			typedef sprout::pair<ForwardIterator, ForwardIterator> type;
			return first == last ? last
				: sprout::detail::min_element_impl(type(sprout::next(first), first), last, comp, 1).second
				;
		}
	}	// namespace detail

	// 25.4.7 Minimum and maximum
	//
	//	recursion depth:
	//		O(log N)
	//
	template<typename ForwardIterator, typename Compare>
	inline SPROUT_CONSTEXPR ForwardIterator
	min_element(ForwardIterator first, ForwardIterator last, Compare comp) {
		typedef typename std::iterator_traits<ForwardIterator>::iterator_category* category;
		return sprout::detail::min_element(first, last, comp, category());
	}

	template<typename ForwardIterator>
	inline SPROUT_CONSTEXPR ForwardIterator
	min_element(ForwardIterator first, ForwardIterator last) {
		return sprout::min_element(
			first, last,
			NS_SSCRISK_CEL_OR_SPROUT::less<typename std::iterator_traits<ForwardIterator>::value_type>()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_MIN_ELEMENT_HPP
