/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ITERATOR_INSERT_RANGE_ITERATOR_HPP
#define SPROUT_ITERATOR_INSERT_RANGE_ITERATOR_HPP

#include <iterator>
#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/iterator/prev.hpp>
#include <sprout/iterator/distance.hpp>
#include <sprout/iterator/type_traits/common.hpp>
#include <sprout/utility/swap.hpp>
#include <sprout/utility/limited.hpp>
#include <sprout/type_traits/arithmetic_promote.hpp>

namespace sprout {
	//
	// insert_range_iterator
	//
	template<typename DstIterator, typename SrcIterator>
	class insert_range_iterator
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
	protected:
		iterator_type current1;
		iterator_type pos1;
		iterator2_type current2;
		iterator2_type first2;
		iterator2_type last2;
	private:
		SPROUT_CONSTEXPR insert_range_iterator advance_impl(difference_type n) const {
			return n >= 0
				? current1 > pos1 ? insert_range_iterator(sprout::next(current1, n), pos1, current2, first2, last2)
					: current1 == pos1 ? current2 == last2 ? insert_range_iterator(sprout::next(current1, n), pos1, current2, first2, last2)
						: n <= sprout::distance(current2, last2) ? insert_range_iterator(current1, pos1, last2, sprout::next(current2, n), first2, last2)
						: insert_range_iterator(sprout::next(current1, n - sprout::distance(current2, last2)), pos1, last2, first2, last2)
					: n <= sprout::distance(current1, pos1) ? insert_range_iterator(sprout::next(current1, n), pos1, current2, first2, last2)
					: n <= sprout::distance(current1, pos1) + sprout::distance(current2, last2)
						? insert_range_iterator(pos1, pos1, last2, sprout::next(current2, n - sprout::distance(current1, pos1)), first2, last2)
					: insert_range_iterator(sprout::next(current1, n - sprout::distance(current1, pos1) - sprout::distance(current2, last2)), pos1, last2, first2, last2)
				: current1 < pos1 ? insert_range_iterator(sprout::next(current1, n), pos1, current2, first2, last2)
					: current1 == pos1 ? current2 == first2 ? insert_range_iterator(sprout::next(current1, n), pos1, current2, first2, last2)
						: -n <= sprout::distance(first2, current2) ? insert_range_iterator(current1, pos1, last2, sprout::next(current2, n), first2, last2)
						: insert_range_iterator(sprout::next(current1, n - sprout::distance(first2, current2)), pos1, first2, first2, last2)
					: -n <= sprout::distance(pos1, current1) ? insert_range_iterator(sprout::next(current1, n), pos1, current2, first2, last2)
					: -n <= sprout::distance(pos1, current1) + sprout::distance(first2, current2)
						? insert_range_iterator(pos1, pos1, last2, sprout::next(current2, n - sprout::distance(pos1, current1)), first2, last2)
					: insert_range_iterator(sprout::next(current1, n - sprout::distance(pos1, current1) - sprout::distance(first2, current2)), pos1, first2, first2, last2)
				;
		}
	public:
		SPROUT_CONSTEXPR insert_range_iterator()
			: current1(), pos1(), current2(), first2(), last2()
		{}
		insert_range_iterator(insert_range_iterator const&) = default;
		SPROUT_CONSTEXPR insert_range_iterator(iterator_type it1, iterator_type pos1, iterator2_type it2, iterator2_type first2, iterator2_type last2)
			: current1(it1), pos1(pos1)
			, current2(it2), first2(first2), last2(last2)
		{}
		template<typename U, typename V>
		SPROUT_CONSTEXPR insert_range_iterator(insert_range_iterator<U, V> const& it)
			: current1(it.base()), pos1(it.position())
			, current2(it.base2()), first2(it.first()), last2(it.last())
		{}
		template<typename U, typename V>
		SPROUT_CXX14_CONSTEXPR insert_range_iterator& operator=(insert_range_iterator<U, V> const& it) {
			insert_range_iterator temp(it);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR iterator_type base() const {
			return current1;
		}
		SPROUT_CONSTEXPR iterator_type position() const {
			return pos1;
		}
		SPROUT_CONSTEXPR iterator2_type base2() const {
			return current2;
		}
		SPROUT_CONSTEXPR iterator2_type first() const {
			return first2;
		}
		SPROUT_CONSTEXPR iterator2_type last() const {
			return last2;
		}
		SPROUT_CONSTEXPR bool is_in_base() const {
			return current1 != pos1 || current2 == last2;
		}
		SPROUT_CONSTEXPR reference operator*() const {
			return is_in_base() ? *current1 : *current2;
		}
		SPROUT_CONSTEXPR pointer operator->() const {
			return &*(*this);
		}
		SPROUT_CXX14_CONSTEXPR insert_range_iterator& operator++() {
			if (is_in_base()) {
				++current1;
			} else {
				++current2;
			}
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR insert_range_iterator operator++(int) {
			insert_range_iterator result(*this);
			if (is_in_base()) {
				++current1;
			} else {
				++current2;
			}
			return result;
		}
		SPROUT_CXX14_CONSTEXPR insert_range_iterator& operator--() {
			if (current1 != pos1 || current2 == first2) {
				--current1;
			} else {
				--current2;
			}
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR insert_range_iterator operator--(int) {
			insert_range_iterator temp(*this);
			if (current1 != pos1 || current2 == first2) {
				--current1;
			} else {
				--current2;
			}
			return temp;
		}
		SPROUT_CONSTEXPR insert_range_iterator operator+(difference_type n) const {
			return advance_impl(n);
		}
		SPROUT_CONSTEXPR insert_range_iterator operator-(difference_type n) const {
			return advance_impl(-n);
		}
		SPROUT_CXX14_CONSTEXPR insert_range_iterator& operator+=(difference_type n) {
			insert_range_iterator temp(*this + n);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR insert_range_iterator& operator-=(difference_type n) {
			insert_range_iterator temp(*this - n);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR reference operator[](difference_type n) const {
			return *(*this + n);
		}
		SPROUT_CONSTEXPR insert_range_iterator next() const {
			return is_in_base() ? insert_range_iterator(sprout::next(current1), pos1, current2, first2, last2)
				: insert_range_iterator(current1, pos1, sprout::next(current2), first2, last2)
				;
		}
		SPROUT_CONSTEXPR insert_range_iterator prev() const {
			return current1 != pos1 || current2 == first2 ? insert_range_iterator(sprout::prev(current1), pos1, current2, first2, last2)
				: insert_range_iterator(current1, pos1, sprout::prev(current2), first2, last2)
				;
		}
		SPROUT_CXX14_CONSTEXPR void swap(insert_range_iterator& other)
		SPROUT_NOEXCEPT_IF(
			SPROUT_NOEXCEPT_EXPR(sprout::swap(current1, other.current1))
			&& SPROUT_NOEXCEPT_EXPR(sprout::swap(pos1, other.pos1))
			&& SPROUT_NOEXCEPT_EXPR(sprout::swap(current2, other.current2))
			&& SPROUT_NOEXCEPT_EXPR(sprout::swap(first2, other.first2))
			&& SPROUT_NOEXCEPT_EXPR(sprout::swap(last2, other.last2))
			)
		{
			sprout::swap(current1, other.current1);
			sprout::swap(pos1, other.pos1);
			sprout::swap(current2, other.current2);
			sprout::swap(first2, other.first2);
			sprout::swap(last2, other.last2);
		}
	};

	template<
		typename DstIterator1, typename SrcIterator1,
		typename DstIterator2, typename SrcIterator2
	>
	inline SPROUT_CONSTEXPR bool operator==(
		sprout::insert_range_iterator<DstIterator1, SrcIterator1> const& lhs,
		sprout::insert_range_iterator<DstIterator2, SrcIterator2> const& rhs
		)
	{
		return lhs.base() == rhs.base() && lhs.base2() == rhs.base2();
	}
	template<
		typename DstIterator1, typename SrcIterator1,
		typename DstIterator2, typename SrcIterator2
	>
	inline SPROUT_CONSTEXPR bool operator!=(
		sprout::insert_range_iterator<DstIterator1, SrcIterator1> const& lhs,
		sprout::insert_range_iterator<DstIterator2, SrcIterator2> const& rhs
		)
	{
		return !(lhs == rhs);
	}
	template<
		typename DstIterator1, typename SrcIterator1,
		typename DstIterator2, typename SrcIterator2
	>
	inline SPROUT_CONSTEXPR bool operator<(
		sprout::insert_range_iterator<DstIterator1, SrcIterator1> const& lhs,
		sprout::insert_range_iterator<DstIterator2, SrcIterator2> const& rhs
		)
	{
		return lhs.is_in_base() && rhs.is_in_base() ? lhs.base() < rhs.base()
			: !lhs.is_in_base() && !rhs.is_in_base() ? lhs.base2() < rhs.base2()
			: lhs.is_in_base()
			;
	}
	template<
		typename DstIterator1, typename SrcIterator1,
		typename DstIterator2, typename SrcIterator2
	>
	inline SPROUT_CONSTEXPR bool operator>(
		sprout::insert_range_iterator<DstIterator1, SrcIterator1> const& lhs,
		sprout::insert_range_iterator<DstIterator2, SrcIterator2> const& rhs
		)
	{
		return rhs < lhs;
	}
	template<
		typename DstIterator1, typename SrcIterator1,
		typename DstIterator2, typename SrcIterator2
	>
	inline SPROUT_CONSTEXPR bool operator<=(
		sprout::insert_range_iterator<DstIterator1, SrcIterator1> const& lhs,
		sprout::insert_range_iterator<DstIterator2, SrcIterator2> const& rhs
		)
	{
		return !(rhs < lhs);
	}
	template<
		typename DstIterator1, typename SrcIterator1,
		typename DstIterator2, typename SrcIterator2
	>
	inline SPROUT_CONSTEXPR bool operator>=(
		sprout::insert_range_iterator<DstIterator1, SrcIterator1> const& lhs,
		sprout::insert_range_iterator<DstIterator2, SrcIterator2> const& rhs
		)
	{
		return !(lhs < rhs);
	}
	template<
		typename DstIterator1, typename SrcIterator1,
		typename DstIterator2, typename SrcIterator2
	>
	inline SPROUT_CONSTEXPR typename sprout::arithmetic_promote<
		typename sprout::insert_range_iterator<DstIterator1, SrcIterator1>::difference_type,
		typename sprout::insert_range_iterator<DstIterator2, SrcIterator2>::difference_type
	>::type
	operator-(
		sprout::insert_range_iterator<DstIterator1, SrcIterator1> const& lhs,
		sprout::insert_range_iterator<DstIterator2, SrcIterator2> const& rhs
		)
	{
		return sprout::limited::plus(lhs.base() - rhs.base(), lhs.base2() - rhs.base2());
	}
	template<typename DstIterator, typename SrcIterator>
	inline SPROUT_CONSTEXPR sprout::insert_range_iterator<DstIterator, SrcIterator> operator+(
		typename sprout::insert_range_iterator<DstIterator, SrcIterator>::difference_type n,
		sprout::insert_range_iterator<DstIterator, SrcIterator> const& it
		)
	{
		return it + n;
	}

	//
	// make_insert_range_iterator
	//
	template<typename DstIterator, typename SrcIterator>
	inline SPROUT_CONSTEXPR sprout::insert_range_iterator<DstIterator, SrcIterator>
	make_insert_range_iterator(DstIterator it1, DstIterator pos1, SrcIterator it2, SrcIterator first2, SrcIterator last2) {
		return sprout::insert_range_iterator<DstIterator, SrcIterator>(it1, pos1, it2, first2, last2);
	}

	//
	// swap
	//
	template<typename DstIterator, typename SrcIterator>
	inline SPROUT_CXX14_CONSTEXPR void
	swap(
		sprout::insert_range_iterator<DstIterator, SrcIterator>& lhs,
		sprout::insert_range_iterator<DstIterator, SrcIterator>& rhs
		)
	SPROUT_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
	{
		lhs.swap(rhs);
	}

	//
	// iterator_next
	//
	template<typename DstIterator, typename SrcIterator>
	inline SPROUT_CONSTEXPR sprout::insert_range_iterator<DstIterator, SrcIterator>
	iterator_next(sprout::insert_range_iterator<DstIterator, SrcIterator> const& it) {
		return it.next();
	}

	//
	// iterator_prev
	//
	template<typename DstIterator, typename SrcIterator>
	inline SPROUT_CONSTEXPR sprout::insert_range_iterator<DstIterator, SrcIterator>
	iterator_prev(sprout::insert_range_iterator<DstIterator, SrcIterator> const& it) {
		return it.prev();
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_INSERT_RANGE_ITERATOR_HPP
