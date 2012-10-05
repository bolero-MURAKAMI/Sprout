#ifndef SPROUT_ITERATOR_PREV_HPP
#define SPROUT_ITERATOR_PREV_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/adl/not_found.hpp>

namespace sprout_adl {
	sprout::not_found_via_adl iterator_prev(...);
}	// namespace sprout_adl

namespace sprout {
	namespace iterator_detail {
		template<typename RandomAccessIterator>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			std::is_literal_type<RandomAccessIterator>::value,
			RandomAccessIterator
		>::type
		prev_impl(RandomAccessIterator const& it, std::random_access_iterator_tag*) {
			return it - 1;
		}
		template<typename BidirectionalIterator>
		inline SPROUT_CONSTEXPR BidirectionalIterator
		prev_impl(BidirectionalIterator const& it, void*) {
			return std::prev(it);
		}

		template<typename RandomAccessIterator>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			std::is_literal_type<RandomAccessIterator>::value,
			RandomAccessIterator
		>::type
		prev_impl(
			RandomAccessIterator const& it, typename std::iterator_traits<RandomAccessIterator>::difference_type n,
			std::random_access_iterator_tag*
			)
		{
			return it - n;
		}
		template<typename BidirectionalIterator>
		inline SPROUT_CONSTEXPR BidirectionalIterator
		prev_impl(
			BidirectionalIterator const& it, typename std::iterator_traits<BidirectionalIterator>::difference_type n,
			void*
			)
		{
			return std::prev(it, n);
		}

		template<typename BidirectionalIterator>
		inline SPROUT_CONSTEXPR BidirectionalIterator
		iterator_prev(BidirectionalIterator const& it) {
			typedef typename std::iterator_traits<BidirectionalIterator>::iterator_category* category;
			return sprout::iterator_detail::prev_impl(it, category());
		}
		template<typename BidirectionalIterator>
		inline SPROUT_CONSTEXPR BidirectionalIterator
		iterator_prev(BidirectionalIterator const& it, typename std::iterator_traits<BidirectionalIterator>::difference_type n) {
			typedef typename std::iterator_traits<BidirectionalIterator>::iterator_category* category;
			return sprout::iterator_detail::prev_impl(it, n, category());
		}
	}	// namespace iterator_detail
}	// namespace sprout

namespace sprout_iterator_detail {
	template<typename BidirectionalIterator>
	inline SPROUT_CONSTEXPR BidirectionalIterator
	prev(BidirectionalIterator const& it) {
		using sprout::iterator_detail::iterator_prev;
		using sprout_adl::iterator_prev;
		return iterator_prev(it);
	}
	template<typename BidirectionalIterator>
	inline SPROUT_CONSTEXPR BidirectionalIterator
	prev(BidirectionalIterator const& it, typename std::iterator_traits<BidirectionalIterator>::difference_type n) {
		using sprout::iterator_detail::iterator_prev;
		using sprout_adl::iterator_prev;
		return iterator_prev(it, n);
	}
}	// namespace sprout_iterator_detail

namespace sprout {
	//
	// prev
	//
	template<typename BidirectionalIterator>
	inline SPROUT_CONSTEXPR BidirectionalIterator
	prev(BidirectionalIterator const& it) {
		return sprout_iterator_detail::prev(it);
	}
	template<typename BidirectionalIterator>
	inline SPROUT_CONSTEXPR BidirectionalIterator
	prev(BidirectionalIterator const& it, typename std::iterator_traits<BidirectionalIterator>::difference_type n) {
		return sprout_iterator_detail::prev(it, n);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_PREV_HPP
