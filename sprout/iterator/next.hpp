#ifndef SPROUT_ITERATOR_NEXT_HPP
#define SPROUT_ITERATOR_NEXT_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			std::is_literal_type<typename std::decay<RandomAccessIterator>::type>::value,
			typename std::decay<RandomAccessIterator>::type
		>::type next_impl(
			RandomAccessIterator&& it,
			std::random_access_iterator_tag*
			)
		{
			return sprout::forward<RandomAccessIterator>(it) + 1;
		}
		template<typename ForwardIterator>
		inline SPROUT_CONSTEXPR typename std::decay<ForwardIterator>::type next_impl(
			ForwardIterator&& it,
			void*
			)
		{
			return std::next(sprout::forward<ForwardIterator>(it));
		}

		template<typename RandomAccessIterator>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			std::is_literal_type<typename std::decay<RandomAccessIterator>::type>::value,
			typename std::decay<RandomAccessIterator>::type
		>::type next_impl(
			RandomAccessIterator&& it,
			typename std::iterator_traits<typename std::decay<RandomAccessIterator>::type>::difference_type n,
			std::random_access_iterator_tag*
			)
		{
			return sprout::forward<RandomAccessIterator>(it) + n;
		}
		template<typename ForwardIterator>
		inline SPROUT_CONSTEXPR typename std::decay<ForwardIterator>::type next_impl(
			ForwardIterator it,
			typename std::iterator_traits<typename std::decay<ForwardIterator>::type>::difference_type n,
			void*
			)
		{
			return std::next(sprout::forward<ForwardIterator>(it), n);
		}
	}	// namespace detail
	//
	// next
	//
	template<typename ForwardIterator>
	inline SPROUT_CONSTEXPR typename std::decay<ForwardIterator>::type
	next(ForwardIterator&& it) {
		typedef typename std::iterator_traits<typename std::decay<ForwardIterator>::type>::iterator_category* category;
		return sprout::detail::next_impl(
			sprout::forward<ForwardIterator>(it),
			category()
			);
	}
	template<typename ForwardIterator>
	inline SPROUT_CONSTEXPR typename std::decay<ForwardIterator>::type
	next(ForwardIterator&& it, typename std::iterator_traits<typename std::decay<ForwardIterator>::type>::difference_type n) {
		typedef typename std::iterator_traits<typename std::decay<ForwardIterator>::type>::iterator_category* category;
		return sprout::detail::next_impl(
			sprout::forward<ForwardIterator>(it),
			n,
			category()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_NEXT_HPP
