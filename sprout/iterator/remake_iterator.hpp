#ifndef SPROUT_ITERATOR_REMAKE_ITERATOR_HPP
#define SPROUT_ITERATOR_REMAKE_ITERATOR_HPP

#include <iterator>
#include <utility>
#include <sprout/config.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/iterator/prev.hpp>
#include <sprout/iterator/distance.hpp>
#include <sprout/iterator/type_traits/common.hpp>
#include <sprout/utility/swap.hpp>
#include HDR_ALGORITHM_MIN_MAX_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	//
	// remake_iterator
	//
	template<typename DstIterator, typename SrcIterator>
	class remake_iterator
		: public std::iterator<
			typename sprout::common_iterator_category<DstIterator, SrcIterator>::type,
			typename sprout::common_iterator_value_type<DstIterator, SrcIterator>::type,
			typename sprout::common_iterator_difference_type<DstIterator, SrcIterator>::type,
			typename sprout::common_iterator_pointer<DstIterator, SrcIterator>::type,
			typename sprout::common_iterator_reference<DstIterator, SrcIterator>::type
		>
	{
	public:
		typedef DstIterator iterator_type;
		typedef SrcIterator iterator2_type;
		typedef typename sprout::common_iterator_category<DstIterator, SrcIterator>::type iterator_category;
		typedef typename sprout::common_iterator_value_type<DstIterator, SrcIterator>::type value_type;
		typedef typename sprout::common_iterator_difference_type<DstIterator, SrcIterator>::type difference_type;
		typedef typename sprout::common_iterator_pointer<DstIterator, SrcIterator>::type pointer;
		typedef typename sprout::common_iterator_reference<DstIterator, SrcIterator>::type reference;
	private:
		SPROUT_CONSTEXPR remake_iterator advance_impl(difference_type n) const {
			return n >= 0
				? remake_iterator(
					sprout::next(current, n),
					begin_off - n >= 0 ? fst
						: (end_off - begin_off >= sprout::distance(fst, lst) && begin_off - n <= -sprout::distance(fst, lst)) ? lst
						: begin_off <= 0
							? sprout::next(current2, NS_SSCRISK_CEL_OR_SPROUT::min(NS_SSCRISK_CEL_OR_SPROUT::min(n, end_off), sprout::distance(current2, lst)))
							: sprout::next(current2, NS_SSCRISK_CEL_OR_SPROUT::min(NS_SSCRISK_CEL_OR_SPROUT::min(n - begin_off, end_off), sprout::distance(current2, lst)))
						,
					fst, lst,
					begin_off - n, end_off - n
					)
				: remake_iterator(
					sprout::next(current, n),
					begin_off - n >= 0 ? fst
						: (end_off - begin_off >= sprout::distance(fst, lst) && begin_off - n <= -sprout::distance(fst, lst)) ? lst
						: begin_off >= -sprout::distance(fst, lst)
							? sprout::next(current2, n)
							: sprout::next(current2, n - (begin_off + sprout::distance(fst, lst)))
						,
					fst, lst,
					begin_off - n, end_off - n
					)
				;
		}
	protected:
		iterator_type current;
		iterator2_type current2;
		iterator2_type fst;
		iterator2_type lst;
		difference_type begin_off;
		difference_type end_off;
	public:
		remake_iterator() = default;
		SPROUT_CONSTEXPR remake_iterator(remake_iterator const& other)
			: current(other.current), current2(other.current2)
			, fst(other.fst) , lst(other.lst)
			, begin_off(other.begin_off) , end_off(other.end_off)
		{}
		SPROUT_CONSTEXPR remake_iterator(iterator_type it, iterator2_type it2, iterator2_type fst, iterator2_type lst, difference_type begin_off, difference_type end_off)
			: current(it), current2(it2)
			, fst(fst), lst(lst)
			, begin_off(begin_off) , end_off(end_off)
		{}
		template<typename U, typename V>
		SPROUT_CONSTEXPR remake_iterator(remake_iterator<U, V> const& it)
			: current(it.base()), current2(it.base2())
			, fst(it.first()), lst(it.last())
			, begin_off(it.begin_offset()) , end_off(it.end_offset())
		{}
		template<typename U, typename V>
		remake_iterator& operator=(remake_iterator<U, V> const& it) {
			remake_iterator temp(it);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR iterator_type base() const {
			return current;
		}
		SPROUT_CONSTEXPR iterator2_type base2() const {
			return current2;
		}
		SPROUT_CONSTEXPR iterator2_type first() const {
			return fst;
		}
		SPROUT_CONSTEXPR iterator2_type last() const {
			return lst;
		}
		SPROUT_CONSTEXPR difference_type begin_offset() const {
			return begin_off;
		}
		SPROUT_CONSTEXPR difference_type end_offset() const {
			return end_off;
		}
		SPROUT_CONSTEXPR bool is_in_copying() const {
			return begin_off <= 0 && end_off > 0 && current2 != lst;
		}
		SPROUT_CONSTEXPR reference operator*() const {
			return is_in_copying() ? *current2 : *current;
		}
		SPROUT_CONSTEXPR pointer operator->() const {
			return &*(*this);
		}
		remake_iterator& operator++() {
			++current;
			if (is_in_copying()) {
				++current2;
			}
			--begin_off;
			--end_off;
			return *this;
		}
		remake_iterator operator++(int) {
			remake_iterator result(*this);
			++current;
			if (is_in_copying()) {
				++current2;
			}
			--begin_off;
			--end_off;
			return result;
		}
		remake_iterator& operator--() {
			--current;
			if (begin_off < 0 && end_off >= 0) {
				--current2;
			}
			++begin_off;
			++end_off;
			return *this;
		}
		remake_iterator operator--(int) {
			remake_iterator temp(*this);
			--current;
			if (begin_off < 0 && end_off >= 0) {
				--current2;
			}
			++begin_off;
			++end_off;
			return temp;
		}
		SPROUT_CONSTEXPR remake_iterator operator+(difference_type n) const {
			return advance_impl(n);
		}
		SPROUT_CONSTEXPR remake_iterator operator-(difference_type n) const {
			return advance_impl(-n);
		}
		remake_iterator& operator+=(difference_type n) {
			remake_iterator temp(*this + n);
			temp.swap(*this);
			return *this;
		}
		remake_iterator& operator-=(difference_type n) {
			remake_iterator temp(*this - n);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR reference operator[](difference_type n) const {
			return *(*this + n);
		}
		SPROUT_CONSTEXPR remake_iterator next() const {
			return remake_iterator(
				sprout::next(current), (is_in_copying() ? sprout::next(current2) : current2),
				fst, lst,
				begin_off - 1, end_off - 1
				);
		}
		SPROUT_CONSTEXPR remake_iterator prev() const {
			return remake_iterator(
				sprout::prev(current), (begin_off < 0 && end_off >= 0 ? sprout::prev(current2) : current2),
				fst, lst,
				begin_off + 1, end_off + 1
				);
		}
		void swap(remake_iterator& other)
		SPROUT_NOEXCEPT_EXPR(
			SPROUT_NOEXCEPT_EXPR(swap(current, other.current))
			&& SPROUT_NOEXCEPT_EXPR(swap(current2, other.current2))
			&& SPROUT_NOEXCEPT_EXPR(swap(fst, other.fst))
			&& SPROUT_NOEXCEPT_EXPR(swap(lst, other.lst))
			&& SPROUT_NOEXCEPT_EXPR(swap(begin_off, other.begin_off))
			&& SPROUT_NOEXCEPT_EXPR(swap(end_off, other.end_off))
			)
		{
			swap(current, other.current);
			swap(current2, other.current2);
			swap(fst, other.fst);
			swap(lst, other.lst);
			swap(begin_off, other.begin_off);
			swap(end_off, other.end_off);
		}
	};

	template<
		typename DstIterator1, typename SrcIterator1,
		typename DstIterator2, typename SrcIterator2
	>
	inline SPROUT_CONSTEXPR bool operator==(
		sprout::remake_iterator<DstIterator1, SrcIterator1> const& lhs,
		sprout::remake_iterator<DstIterator2, SrcIterator2> const& rhs
		)
	{
		return lhs.base() == rhs.base();
	}
	template<
		typename DstIterator1, typename SrcIterator1,
		typename DstIterator2, typename SrcIterator2
	>
	inline SPROUT_CONSTEXPR bool operator!=(
		sprout::remake_iterator<DstIterator1, SrcIterator1> const& lhs,
		sprout::remake_iterator<DstIterator2, SrcIterator2> const& rhs
		)
	{
		return !(lhs == rhs);
	}
	template<
		typename DstIterator1, typename SrcIterator1,
		typename DstIterator2, typename SrcIterator2
	>
	inline SPROUT_CONSTEXPR bool operator<(
		sprout::remake_iterator<DstIterator1, SrcIterator1> const& lhs,
		sprout::remake_iterator<DstIterator2, SrcIterator2> const& rhs
		)
	{
		return lhs.base() < rhs.base();
	}
	template<
		typename DstIterator1, typename SrcIterator1,
		typename DstIterator2, typename SrcIterator2
	>
	inline SPROUT_CONSTEXPR bool operator>(
		sprout::remake_iterator<DstIterator1, SrcIterator1> const& lhs,
		sprout::remake_iterator<DstIterator2, SrcIterator2> const& rhs
		)
	{
		return rhs < lhs;
	}
	template<
		typename DstIterator1, typename SrcIterator1,
		typename DstIterator2, typename SrcIterator2
	>
	inline SPROUT_CONSTEXPR bool operator<=(
		sprout::remake_iterator<DstIterator1, SrcIterator1> const& lhs,
		sprout::remake_iterator<DstIterator2, SrcIterator2> const& rhs
		)
	{
		return !(rhs < lhs);
	}
	template<
		typename DstIterator1, typename SrcIterator1,
		typename DstIterator2, typename SrcIterator2
	>
	inline SPROUT_CONSTEXPR bool operator>=(
		sprout::remake_iterator<DstIterator1, SrcIterator1> const& lhs,
		sprout::remake_iterator<DstIterator2, SrcIterator2> const& rhs
		)
	{
		return !(lhs < rhs);
	}
	template<
		typename DstIterator1, typename SrcIterator1,
		typename DstIterator2, typename SrcIterator2
	>
	inline SPROUT_CONSTEXPR decltype(std::declval<DstIterator1>() - std::declval<DstIterator2>())
	operator-(
		sprout::remake_iterator<DstIterator1, SrcIterator1> const& lhs,
		sprout::remake_iterator<DstIterator2, SrcIterator2> const& rhs
		)
	{
		return lhs.base() - rhs.base();
	}
	template<typename DstIterator, typename SrcIterator>
	inline SPROUT_CONSTEXPR sprout::remake_iterator<DstIterator, SrcIterator> operator+(
		typename sprout::remake_iterator<DstIterator, SrcIterator>::difference_type n,
		sprout::remake_iterator<DstIterator, SrcIterator> const& it
		)
	{
		return it + n;
	}

	//
	// make_remake_iterator
	//
	template<typename DstIterator, typename SrcIterator>
	inline SPROUT_CONSTEXPR sprout::remake_iterator<DstIterator, SrcIterator>
	make_remake_iterator(
		DstIterator it, SrcIterator it2,
		SrcIterator fst, SrcIterator lst,
		typename sprout::remake_iterator<DstIterator, SrcIterator>::difference_type begin_off,
		typename sprout::remake_iterator<DstIterator, SrcIterator>::difference_type end_off
		)
	{
		return sprout::remake_iterator<DstIterator, SrcIterator>(it, it2, fst, lst, begin_off, end_off);
	}

	//
	// swap
	//
	template<typename DstIterator, typename SrcIterator>
	inline void
	swap(sprout::remake_iterator<DstIterator, SrcIterator>& lhs, sprout::remake_iterator<DstIterator, SrcIterator>& rhs)
	SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs)))
	{
		lhs.swap(rhs);
	}

	//
	// iterator_next
	//
	template<typename DstIterator, typename SrcIterator>
	inline SPROUT_CONSTEXPR sprout::remake_iterator<DstIterator, SrcIterator>
	iterator_next(sprout::remake_iterator<DstIterator, SrcIterator> const& it) {
		return it.next();
	}

	//
	// iterator_prev
	//
	template<typename DstIterator, typename SrcIterator>
	inline SPROUT_CONSTEXPR sprout::remake_iterator<DstIterator, SrcIterator>
	iterator_prev(sprout::remake_iterator<DstIterator, SrcIterator> const& it) {
		return it.prev();
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_REMAKE_ITERATOR_HPP
