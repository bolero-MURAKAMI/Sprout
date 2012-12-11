#ifndef SPROUT_ALGORITHM_FIND_END_HPP
#define SPROUT_ALGORITHM_FIND_END_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/search.hpp>

namespace sprout {
	namespace detail {
		// Copyright (C) 2011 RiSK (sscrisk)

		template<typename Iterator1, typename Iterator2>
		struct iter_equal_to {
		public:
			SPROUT_CONSTEXPR bool
			operator()(
				typename std::iterator_traits<Iterator1>::value_type const& x,
				typename std::iterator_traits<Iterator2>::value_type const& y
				) const
			{
				return x == y;
			}
		};
	}	// namespace detail

	namespace detail {
		template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR ForwardIterator1
		find_end_impl(
			ForwardIterator1 first1, ForwardIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2,
			BinaryPredicate pred,
			ForwardIterator1 result
			)
		{
			return first1 == last1 ? result
				: sprout::detail::find_end_impl(
					sprout::search(sprout::next(first1), last1, first2, last2, pred), last1, first2, last2, pred,
					first1 
					)
				;
		}
		template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR ForwardIterator1
		find_end(
			ForwardIterator1 first1, ForwardIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2,
			BinaryPredicate pred,
			void*
			)
		{
			return first2 == last2 ? last1
				: sprout::detail::find_end_impl(
					sprout::search(first1, last1, first2, last2, pred), last1, first2, last2, pred,
					last1
					)
				;
		}
	}	// namespace detail

	// 25.2.6 Find end
	template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
	inline SPROUT_CONSTEXPR ForwardIterator1
	find_end(
		ForwardIterator1 first1, ForwardIterator1 last1,
		ForwardIterator2 first2, ForwardIterator2 last2,
		BinaryPredicate pred
		)
	{
		typedef typename std::iterator_traits<ForwardIterator1>::iterator_category* category;
		return sprout::detail::find_end(first1, last1, first2, last2, pred, category());
	}

	template<typename ForwardIterator1, typename ForwardIterator2>
	inline SPROUT_CONSTEXPR ForwardIterator1
	find_end(
		ForwardIterator1 first1, ForwardIterator1 last1,
		ForwardIterator2 first2, ForwardIterator2 last2
		)
	{
		return sprout::find_end(
			first1, last1,
			first2, last2,
			sprout::detail::iter_equal_to<ForwardIterator1, ForwardIterator2>()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIND_END_HPP
