#ifndef SPROUT_ITERATOR_NEXT_HPP
#define SPROUT_ITERATOR_NEXT_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	namespace iterator_detail {
		template<typename RandomAccessIterator>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			std::is_literal_type<RandomAccessIterator>::value,
			RandomAccessIterator
		>::type next_impl(
			RandomAccessIterator const& it,
			std::random_access_iterator_tag*
			)
		{
			return it + 1;
		}
		template<typename ForwardIterator>
		inline SPROUT_CONSTEXPR ForwardIterator next_impl(
			ForwardIterator const& it,
			void*
			)
		{
			return std::next(it);
		}

		template<typename RandomAccessIterator>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			std::is_literal_type<RandomAccessIterator>::value,
			RandomAccessIterator
		>::type next_impl(
			RandomAccessIterator const& it,
			typename std::iterator_traits<RandomAccessIterator>::difference_type n,
			std::random_access_iterator_tag*
			)
		{
			return it + n;
		}
		template<typename ForwardIterator>
		inline SPROUT_CONSTEXPR ForwardIterator next_impl(
			ForwardIterator const& it,
			typename std::iterator_traits<ForwardIterator>::difference_type n,
			void*
			)
		{
			return std::next(it, n);
		}

		template<typename ForwardIterator>
		inline SPROUT_CONSTEXPR ForwardIterator
		iterator_next(ForwardIterator const& it) {
			typedef typename std::iterator_traits<ForwardIterator>::iterator_category* category;
			return sprout::iterator_detail::next_impl(it, category());
		}
		template<typename ForwardIterator>
		inline SPROUT_CONSTEXPR ForwardIterator
		iterator_next(ForwardIterator const& it, typename std::iterator_traits<ForwardIterator>::difference_type n) {
			typedef typename std::iterator_traits<ForwardIterator>::iterator_category* category;
			return sprout::iterator_detail::next_impl(it, n, category());
		}
	}	// namespace iterator_detail
}	// namespace sprout

namespace sprout_iterator_detail {
	template<typename ForwardIterator>
	inline SPROUT_CONSTEXPR ForwardIterator
	next(ForwardIterator const& it) {
		using sprout::iterator_detail::iterator_next;
		return iterator_next(it);
	}
	template<typename ForwardIterator>
	inline SPROUT_CONSTEXPR ForwardIterator
	next(ForwardIterator const& it, typename std::iterator_traits<ForwardIterator>::difference_type n) {
		using sprout::iterator_detail::iterator_next;
		return iterator_next(it, n);
	}
}	// namespace sprout_iterator_detail

namespace sprout {
	//
	// next
	//
	template<typename ForwardIterator>
	inline SPROUT_CONSTEXPR ForwardIterator
	next(ForwardIterator const& it) {
		return sprout_iterator_detail::next(it);
	}
	template<typename ForwardIterator>
	inline SPROUT_CONSTEXPR ForwardIterator
	next(ForwardIterator const& it, typename std::iterator_traits<ForwardIterator>::difference_type n) {
		return sprout_iterator_detail::next(it, n);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_NEXT_HPP
