#ifndef SPROUT_DETAIL_ALGORITHM_HPP
#define SPROUT_DETAIL_ALGORITHM_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>

namespace sprout {
	namespace detail {
		//
		// min
		//
		template<typename T>
		SPROUT_CONSTEXPR T const& min(T const& a, T const& b) {
			return b < a ? b : a;
		}
		template<typename T, typename Compare>
		SPROUT_CONSTEXPR T const& min(T const& a, T const& b, Compare comp) {
			return comp(b, a) ? b : a;
		}

		//
		// max
		//
		template<typename T>
		SPROUT_CONSTEXPR T const& max(T const& a, T const& b) {
			return a < b ? b : a;
		}
		template<typename T, typename Compare>
		SPROUT_CONSTEXPR T const& max(T const& a, T const& b, Compare comp) {
			return comp(a, b) ? b : a;
		}

		//
		// count
		//
		template<typename InputIterator, typename T>
		SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type count(
			InputIterator first,
			InputIterator last,
			T const& value
			)
		{
			return first == last
				? 0
				: (*first == value ? 1 : 0) + sprout::detail::count(sprout::next(first), last, value)
				;
		}

		//
		// count_if
		//
		template<typename InputIterator, typename Predicate>
		SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type count_if(
			InputIterator first,
			InputIterator last,
			Predicate pred
			)
		{
			return first == last
				? 0
				: (pred(*first) ? 1 : 0) + sprout::detail::count_if(sprout::next(first), last, pred)
				;
		}

		//
		// equal
		//
		template<typename InputIterator1, typename InputIterator2>
		SPROUT_CONSTEXPR bool equal(
			InputIterator1 first1,
			InputIterator1 last1,
			InputIterator2 first2
			)
		{
			return first1 == last1
				? true
				: *first1 == *first2 && sprout::detail::equal(sprout::next(first1), last1, sprout::next(first2))
				;
		}
		template<typename InputIterator1, typename InputIterator2, typename Predicate>
		SPROUT_CONSTEXPR bool equal(
			InputIterator1 first1,
			InputIterator1 last1,
			InputIterator2 first2,
			Predicate pred
			)
		{
			return first1 == last1
				? true
				: pred(*first1, *first2) && sprout::detail::equal(sprout::next(first1), last1, sprout::next(first2), pred)
				;
		}

		//
		// lexicographical_compare
		//
		template<typename InputIterator1, typename InputIterator2>
		SPROUT_CONSTEXPR bool lexicographical_compare(
			InputIterator1 first1,
			InputIterator1 last1,
			InputIterator2 first2,
			InputIterator2 last2
			)
		{
			return first2 == last2
				? false
				: first1 == last1 || *first1 < *first2
				? true
				: *first2 < *first1
				? false
				: sprout::detail::lexicographical_compare(sprout::next(first1), last1, sprout::next(first2), last2)
				;
		}
		template<typename InputIterator1, typename InputIterator2, typename Compare>
		SPROUT_CONSTEXPR bool lexicographical_compare(
			InputIterator1 first1,
			InputIterator1 last1,
			InputIterator2 first2,
			InputIterator2 last2,
			Compare comp
			)
		{
			return first2 == last2
				? false
				: first1 == last1 || comp(*first1, *first2)
				? true
				: comp(*first2, *first1)
				? false
				: sprout::detail::lexicographical_compare(sprout::next(first1), last1, sprout::next(first2), last2, comp)
				;
		}

		//
		// find
		//
		template<typename InputIterator, typename T>
		SPROUT_CONSTEXPR InputIterator find(InputIterator first, InputIterator last, T const& value) {
			return first == last || *first == value
				? first
				: sprout::detail::find(sprout::next(first), last, value)
				;
		}
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_ALGORITHM_HPP
