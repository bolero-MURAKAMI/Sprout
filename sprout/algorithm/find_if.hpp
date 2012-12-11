#ifndef SPROUT_ALGORITHM_FIND_IF_HPP
#define SPROUT_ALGORITHM_FIND_IF_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator, typename Predicate>
		inline SPROUT_CONSTEXPR RandomAccessIterator
		find_if_impl_ra(
			RandomAccessIterator first, RandomAccessIterator last, Predicate pred,
			typename std::iterator_traits<RandomAccessIterator>::difference_type pivot, RandomAccessIterator found
			)
		{
			return found != first ? found
				: pivot == 0 ? (pred(*first) ? first : last)
				: sprout::detail::find_if_impl_ra(
					sprout::next(first, pivot), last, pred,
					(NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) - pivot) / 2,
					sprout::detail::find_if_impl_ra(
						first, sprout::next(first, pivot), pred,
						pivot / 2,
						first
						)
					)
				;
		}
		template<typename RandomAccessIterator, typename Predicate>
		inline SPROUT_CONSTEXPR RandomAccessIterator
		find_if(
			RandomAccessIterator first, RandomAccessIterator last, Predicate pred,
			std::random_access_iterator_tag*
			)
		{
			return first == last ? last
				: sprout::detail::find_if_impl_ra(first, last, pred, NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) / 2, first)
				;
		}

		// Copyright (C) 2011 RiSK (sscrisk)
		template<typename InputIterator, typename Predicate>
		inline SPROUT_CONSTEXPR InputIterator
		find_if_impl(InputIterator first, InputIterator last, Predicate pred) {
			return first == last || pred(*first) ? first
				: sprout::detail::find_if_impl(sprout::next(first), last, pred)
				;
		}
		template<typename InputIterator, typename Predicate>
		inline SPROUT_CONSTEXPR InputIterator
		find_if(
			InputIterator first, InputIterator last, Predicate pred,
			void*
			)
		{
			return sprout::detail::find_if_impl(first, last, pred);
		}
	}	//namespace detail

	// 25.2.5 Find
	template<typename InputIterator, typename Predicate>
	inline SPROUT_CONSTEXPR InputIterator
	find_if(InputIterator first, InputIterator last, Predicate pred) {
		typedef typename std::iterator_traits<InputIterator>::iterator_category* category;
		return sprout::detail::find_if(first, last, pred, category());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIND_IF_HPP
