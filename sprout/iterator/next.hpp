#ifndef SPROUT_ITERATOR_NEXT_HPP
#define SPROUT_ITERATOR_NEXT_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/next_fwd.hpp>
#include <sprout/iterator/prev_fwd.hpp>
#include <sprout/adl/not_found.hpp>
#include <sprout/assert.hpp>

namespace sprout_adl {
	sprout::not_found_via_adl iterator_next(...);
}	// namespace sprout_adl

namespace sprout {
	namespace iterator_detail {
		template<typename RandomAccessIterator>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			std::is_literal_type<RandomAccessIterator>::value,
			RandomAccessIterator
		>::type
		next_impl(RandomAccessIterator const& it, std::random_access_iterator_tag*) {
			return it + 1;
		}
		template<typename ForwardIterator>
		inline SPROUT_CONSTEXPR ForwardIterator
		next_impl(ForwardIterator const& it, std::forward_iterator_tag*) {
			return std::next(it);
		}

		template<typename RandomAccessIterator>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			std::is_literal_type<RandomAccessIterator>::value,
			RandomAccessIterator
		>::type
		next_impl(
			RandomAccessIterator const& it, typename std::iterator_traits<RandomAccessIterator>::difference_type n,
			std::random_access_iterator_tag*
			)
		{
			return it + n;
		}

		template<typename BidirectionalIterator>
		inline SPROUT_CONSTEXPR BidirectionalIterator
		next_impl_2_neg(BidirectionalIterator const& it, typename std::iterator_traits<BidirectionalIterator>::difference_type n) {
			return n == -1 ? sprout::prev(it)
				: sprout::iterator_detail::next_impl_2_neg(
					sprout::iterator_detail::next_impl_2_neg(it, n / 2),
					n - (n / 2)
					)
				;
		}
		template<typename ForwardIterator>
		inline SPROUT_CONSTEXPR ForwardIterator
		next_impl_2(ForwardIterator const& it, typename std::iterator_traits<ForwardIterator>::difference_type n) {
			return n == 1 ? sprout::next(it)
				: sprout::iterator_detail::next_impl_2(
					sprout::iterator_detail::next_impl_2(it, n / 2),
					n - (n / 2)
					)
				;
		}

		template<typename BidirectionalIterator>
		inline SPROUT_CONSTEXPR BidirectionalIterator
		next_impl_1(
			BidirectionalIterator const& it, typename std::iterator_traits<BidirectionalIterator>::difference_type n,
			std::bidirectional_iterator_tag*
			)
		{
			return n == 0 ? it
				: n > 0 ? sprout::iterator_detail::next_impl_2(it, n)
				: sprout::iterator_detail::next_impl_2_neg(it, n)
				;
		}
		template<typename ForwardIterator>
		inline SPROUT_CONSTEXPR ForwardIterator
		next_impl_1(
			ForwardIterator const& it, typename std::iterator_traits<ForwardIterator>::difference_type n,
			std::forward_iterator_tag*
			)
		{
			return SPROUT_ASSERT(n >= 0),
				n == 0 ? it
					: sprout::iterator_detail::next_impl_2(it, n)
				;
		}

		template<typename ForwardIterator>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			std::is_literal_type<ForwardIterator>::value,
			ForwardIterator
		>::type
		next_impl(
			ForwardIterator const& it, typename std::iterator_traits<ForwardIterator>::difference_type n,
			std::forward_iterator_tag*
			)
		{
			typedef typename std::iterator_traits<ForwardIterator>::iterator_category* category;
			return sprout::iterator_detail::next_impl_1(it, n, category());
		}
		template<typename ForwardIterator>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!std::is_literal_type<ForwardIterator>::value,
			ForwardIterator
		>::type
		next_impl(
			ForwardIterator const& it, typename std::iterator_traits<ForwardIterator>::difference_type n,
			std::forward_iterator_tag*
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
		using sprout_adl::iterator_next;
		return iterator_next(it);
	}
	template<typename ForwardIterator>
	inline SPROUT_CONSTEXPR ForwardIterator
	next(ForwardIterator const& it, typename std::iterator_traits<ForwardIterator>::difference_type n) {
		using sprout::iterator_detail::iterator_next;
		using sprout_adl::iterator_next;
		return iterator_next(it, n);
	}
}	// namespace sprout_iterator_detail

namespace sprout {
	//
	// next
	//
	//	effect:
	//		ADL callable iterator_next(it) -> iterator_next(it)
	//		it is RandomAccessIterator && LiteralType -> it + 1
	//		otherwise -> std::next(it)
	//
	template<typename ForwardIterator>
	inline SPROUT_CONSTEXPR ForwardIterator
	next(ForwardIterator const& it) {
		return sprout_iterator_detail::next(it);
	}
	//
	//	effect:
	//		ADL callable iterator_next(it, n) -> iterator_next(it, n)
	//		it is RandomAccessIterator && LiteralType -> it + n
	//		it is LiteralType -> sprout::next(it)... || sprout::prev(it)...
	//		otherwise -> std::next(it, n)
	//
	template<typename ForwardIterator>
	inline SPROUT_CONSTEXPR ForwardIterator
	next(ForwardIterator const& it, typename std::iterator_traits<ForwardIterator>::difference_type n) {
		return sprout_iterator_detail::next(it, n);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_NEXT_HPP
