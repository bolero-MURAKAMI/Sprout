#ifndef SPROUT_ALGORITHM_SEARCH_N_HPP
#define SPROUT_ALGORITHM_SEARCH_N_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/value_iterator.hpp>
#include <sprout/functional/equal_to.hpp>
#include <sprout/algorithm/search.hpp>

namespace sprout {
	// 25.2.13 Search
	//
	//	recursion depth:
	//		O(log(N1+N2))
	//
	template<typename ForwardIterator, typename Size, typename T, typename BinaryPredicate>
	inline SPROUT_CONSTEXPR ForwardIterator
	search_n(ForwardIterator first, ForwardIterator last, Size count, T const& value, BinaryPredicate pred) {
		typedef sprout::value_iterator<T const&> iterator;
		return sprout::search(
			first, last,
			iterator(value, static_cast<typename std::iterator_traits<iterator>::difference_type>(count)), iterator(value, 0),
			pred
			);
	}

	template<typename ForwardIterator, typename Size, typename T>
	inline SPROUT_CONSTEXPR ForwardIterator
	search_n(ForwardIterator first, ForwardIterator last, Size count, T const& value) {
		return sprout::search_n(first, last, count, value, sprout::equal_to<>());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_SEARCH_N_HPP
