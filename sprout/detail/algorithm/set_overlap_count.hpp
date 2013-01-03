#ifndef SPROUT_DETAIL_ALGORITHM_SET_OVERLAP_COUNT_HPP
#define SPROUT_DETAIL_ALGORITHM_SET_OVERLAP_COUNT_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/type_traits/is_iterator.hpp>
#include <sprout/iterator/type_traits/common.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/functional/less.hpp>

namespace sprout {
	namespace detail {
		template<typename InputIterator1, typename InputIterator2, typename Compare>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<InputIterator1, InputIterator2, typename std::iterator_traits<InputIterator1>::difference_type>
		set_overlap_count_impl_1(
			sprout::tuples::tuple<InputIterator1, InputIterator2, typename std::iterator_traits<InputIterator1>::difference_type> const& current,
			InputIterator1 last1, InputIterator2 last2, Compare comp, typename std::iterator_traits<InputIterator1>::difference_type n
			)
		{
			typedef sprout::tuples::tuple<InputIterator1, InputIterator2, typename std::iterator_traits<InputIterator1>::difference_type> type;
			return sprout::tuples::get<0>(current) == last1 || sprout::tuples::get<1>(current) == last2 ? current
				: n == 1 ? comp(*sprout::tuples::get<0>(current), *sprout::tuples::get<1>(current)) ? type(
						sprout::next(sprout::tuples::get<0>(current)), sprout::tuples::get<1>(current),
						sprout::tuples::get<2>(current)
						)
					: comp(*sprout::tuples::get<1>(current), *sprout::tuples::get<0>(current)) ? type(
						sprout::tuples::get<0>(current), sprout::next(sprout::tuples::get<1>(current)),
						sprout::tuples::get<2>(current)
						)
					: type(
						sprout::next(sprout::tuples::get<0>(current)), sprout::next(sprout::tuples::get<1>(current)),
						sprout::tuples::get<2>(current) + 1
						)
				: sprout::detail::set_overlap_count_impl_1(
					sprout::detail::set_overlap_count_impl_1(
						current,
						last1, last2, comp, n / 2
						),
					last1, last2, comp, n - n / 2
					)
				;
		}
		template<typename InputIterator1, typename InputIterator2, typename Compare>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<InputIterator1, InputIterator2, typename std::iterator_traits<InputIterator1>::difference_type>
		set_overlap_count_impl(
			sprout::tuples::tuple<InputIterator1, InputIterator2, typename std::iterator_traits<InputIterator1>::difference_type> const& current,
			InputIterator1 last1, InputIterator2 last2, Compare comp, typename std::iterator_traits<InputIterator1>::difference_type n
			)
		{
			typedef sprout::tuples::tuple<InputIterator1, InputIterator2, typename std::iterator_traits<InputIterator1>::difference_type> type;
			return sprout::tuples::get<0>(current) == last1 || sprout::tuples::get<1>(current) == last2 ? current
				: sprout::detail::set_overlap_count_impl(
					sprout::detail::set_overlap_count_impl_1(
						current,
						last1, last2, comp, n
						),
					last1, last2, comp, n * 2
					)
				;
		}

		//
		// set_overlap_count
		//
		//	recursion depth:
		//		O(log N)
		//
		template<typename InputIterator1, typename InputIterator2, typename Compare>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator1>::difference_type
		set_overlap_count(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2,
			Compare comp
			)
		{
			typedef sprout::tuples::tuple<InputIterator1, InputIterator2, typename std::iterator_traits<InputIterator1>::difference_type> type;
			return sprout::tuples::get<2>(
				sprout::detail::set_overlap_count_impl(type(first1, first2, 0), last1, last2, comp, 1)
				);
		}

		template<typename InputIterator1, typename InputIterator2>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator1>::difference_type
		set_overlap_count(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2
			)
		{
			return sprout::detail::set_overlap_count(first1, last1, first2, last2, sprout::less<>());
		}
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_ALGORITHM_SET_OVERLAP_COUNT_HPP
