#ifndef SPROUT_ITERATOR_PREV_HPP
#define SPROUT_ITERATOR_PREV_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator>
		SPROUT_CONSTEXPR typename std::enable_if<
			std::is_literal_type<typename std::decay<RandomAccessIterator>::type>::value,
			typename std::decay<RandomAccessIterator>::type
		>::type prev_impl(
			RandomAccessIterator&& it,
			std::random_access_iterator_tag*
			)
		{
			return sprout::forward<RandomAccessIterator>(it) - 1;
		}
		template<typename BidirectionalIterator>
		SPROUT_CONSTEXPR typename std::decay<BidirectionalIterator>::type prev_impl(
			BidirectionalIterator&& it,
			void*
			)
		{
			using std::prev;
			return prev(sprout::forward<BidirectionalIterator>(it));
		}

		template<typename RandomAccessIterator>
		SPROUT_CONSTEXPR typename std::enable_if<
			std::is_literal_type<typename std::decay<RandomAccessIterator>::type>::value,
			typename std::decay<RandomAccessIterator>::type
		>::type prev_impl(
			RandomAccessIterator&& it,
			typename std::iterator_traits<typename std::decay<RandomAccessIterator>::type>::difference_type n,
			std::random_access_iterator_tag*
			)
		{
			return sprout::forward<RandomAccessIterator>(it) - n;
		}
		template<typename BidirectionalIterator>
		SPROUT_CONSTEXPR typename std::decay<BidirectionalIterator>::type prev_impl(
			BidirectionalIterator it,
			typename std::iterator_traits<typename std::decay<BidirectionalIterator>::type>::difference_type n,
			void*
			)
		{
			using std::prev;
			return prev(sprout::forward<BidirectionalIterator>(it), n);
		}
	}	// namespace detail
	//
	// prev
	//
	template<typename BidirectionalIterator>
	SPROUT_CONSTEXPR typename std::decay<BidirectionalIterator>::type prev(BidirectionalIterator&& it) {
		typedef typename std::iterator_traits<typename std::decay<BidirectionalIterator>::type>::iterator_category* category;
		return sprout::detail::prev_impl(
			sprout::forward<BidirectionalIterator>(it),
			category()
			);
	}
	template<typename BidirectionalIterator>
	SPROUT_CONSTEXPR typename std::decay<BidirectionalIterator>::type prev(
		BidirectionalIterator&& it,
		typename std::iterator_traits<typename std::decay<BidirectionalIterator>::type>::difference_type n
		)
	{
		typedef typename std::iterator_traits<typename std::decay<BidirectionalIterator>::type>::iterator_category* category;
		return sprout::detail::prev_impl(
			sprout::forward<BidirectionalIterator>(it),
			n,
			category()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_PREV_HPP
