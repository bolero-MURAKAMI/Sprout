#ifndef SPROUT_DETAIL_ALGORITHM_COUNT_N_IF_HPP
#define SPROUT_DETAIL_ALGORITHM_COUNT_N_IF_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/type_traits/is_iterator.hpp>
#include <sprout/utility/pair/pair.hpp>
#include <sprout/algorithm/count_if.hpp>

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator, typename Predicate>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_constant_distance_iterator<RandomAccessIterator>::pred,
			typename std::iterator_traits<RandomAccessIterator>::difference_type
		>::type
		count_n_if(
			RandomAccessIterator first, typename std::iterator_traits<RandomAccessIterator>::difference_type n, Predicate pred,
			std::random_access_iterator_tag*
			)
		{
			return sprout::count(first, sprout::next(first, n), pred);
		}

		template<typename InputIterator, typename Predicate>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator, typename std::iterator_traits<InputIterator>::difference_type>
		count_n_if_impl(
			sprout::pair<InputIterator, typename std::iterator_traits<InputIterator>::difference_type> const& current,
			Predicate pred, typename std::iterator_traits<InputIterator>::difference_type n
			)
		{
			typedef sprout::pair<InputIterator, typename std::iterator_traits<InputIterator>::difference_type> type;
			return n == 1 ? type(sprout::next(current.first), current.second + (pred(*current.first) ? 1 : 0))
				: sprout::detail::count_n_if_impl(
					sprout::detail::count_n_if_impl(
						current,
						pred, n / 2
						),
					pred, n - n / 2
					)
				;
		}
		template<typename InputIterator, typename Predicate>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
		count_n_if(
			InputIterator first, typename std::iterator_traits<InputIterator>::difference_type n, Predicate pred,
			void*
			)
		{
			typedef sprout::pair<InputIterator, typename std::iterator_traits<InputIterator>::difference_type> type;
			return n == 0 ? 0
				: sprout::detail::count_n_if_impl(type(first, 0), pred, n).second
				;
		}

		//
		// count_n_if
		//
		//	recursion depth:
		//		O(log N)
		//
		template<typename InputIterator, typename Predicate>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
		count_n_if(InputIterator first, typename std::iterator_traits<InputIterator>::difference_type n, Predicate pred) {
			typedef typename std::iterator_traits<InputIterator>::iterator_category* category;
			return sprout::detail::count_n_if(first, n, pred, category());

		}
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_ALGORITHM_COUNT_N_IF_HPP
