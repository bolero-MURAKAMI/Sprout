/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ITERATOR_JOINT_ITERATOR_HPP
#define SPROUT_ITERATOR_JOINT_ITERATOR_HPP

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
	// joint_iterator
	//
	template<typename LIterator, typename RIterator>
	class joint_iterator
		: public std::iterator<
			typename sprout::common_iterator_category<LIterator, RIterator>::type,
			typename sprout::common_iterator_value_type<LIterator, RIterator>::type,
			typename sprout::common_iterator_difference_type<LIterator, RIterator>::type,
			typename sprout::common_iterator_pointer<LIterator, RIterator>::type,
			typename sprout::common_iterator_reference<LIterator, RIterator>::type
		>
	{
	public:
		typedef LIterator iterator_type;
		typedef RIterator iterator2_type;
		typedef typename sprout::common_iterator_category<LIterator, RIterator>::type iterator_category;
		typedef typename sprout::common_iterator_value_type<LIterator, RIterator>::type value_type;
		typedef typename sprout::common_iterator_difference_type<LIterator, RIterator>::type difference_type;
		typedef typename sprout::common_iterator_pointer<LIterator, RIterator>::type pointer;
		typedef typename sprout::common_iterator_reference<LIterator, RIterator>::type reference;
	protected:
		iterator_type current1;
		iterator_type last1;
		iterator2_type first2;
		iterator2_type current2;
	private:
		SPROUT_CONSTEXPR joint_iterator advance_impl_posite(difference_type n, difference_type d) const {
			return n > d ? joint_iterator(last1, last1, first2, sprout::next(current2, n - d))
				: joint_iterator(sprout::next(current1, n), last1, first2, current2)
				;
		}
		SPROUT_CONSTEXPR joint_iterator advance_impl_negate(difference_type n, difference_type d) const {
			return !(n > d) ? joint_iterator(sprout::next(current1, n - d), last1, first2, first2)
				: joint_iterator(current1, last1, first2, sprout::next(current2, n))
				;
		}
		SPROUT_CONSTEXPR joint_iterator advance_impl(difference_type n) const {
			return n >= 0
				? is_in_left()
					? advance_impl_posite(n, sprout::distance(current1, last1))
					: joint_iterator(current1, last1, first2, sprout::next(current2, n))
				: first2 == current2
					? joint_iterator(sprout::next(current1, n), last1, first2, current2)
					: advance_impl_negate(n, -sprout::distance(first2, current2))
				;
		}
	public:
		SPROUT_CONSTEXPR joint_iterator()
			: current1(), last1(), first2(), current2()
		{}
		joint_iterator(joint_iterator const&) = default;
		SPROUT_CONSTEXPR joint_iterator(iterator_type it1, iterator_type last1, iterator2_type first2, iterator2_type it2)
			: current1(it1) , last1(last1)
			, first2(first2) , current2(it2)
		{}
		template<typename U, typename V>
		SPROUT_CONSTEXPR joint_iterator(joint_iterator<U, V> const& it)
			: current1(it.base())
			, last1(it.left_end())
			, first2(it.right_begin())
			, current2(it.base2())
		{}
		template<typename U, typename V>
		SPROUT_CXX14_CONSTEXPR joint_iterator& operator=(joint_iterator<U, V> const& it) {
			joint_iterator temp(it);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR iterator_type base() const {
			return current1;
		}
		SPROUT_CONSTEXPR iterator_type left_end() const {
			return last1;
		}
		SPROUT_CONSTEXPR iterator2_type right_begin() const {
			return first2;
		}
		SPROUT_CONSTEXPR iterator2_type base2() const {
			return current2;
		}
		SPROUT_CONSTEXPR bool is_in_left() const {
			return current1 != last1;
		}
		SPROUT_CONSTEXPR reference operator*() const {
			return is_in_left() ? *current1 : *current2;
		}
		SPROUT_CONSTEXPR pointer operator->() const {
			return &*(*this);
		}
		SPROUT_CXX14_CONSTEXPR joint_iterator& operator++() {
			if (is_in_left()) {
				++current1;
			} else {
				++current2;
			}
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR joint_iterator operator++(int) {
			joint_iterator result(*this);
			if (is_in_left()) {
				++current1;
			} else {
				++current2;
			}
			return result;
		}
		SPROUT_CXX14_CONSTEXPR joint_iterator& operator--() {
			if (first2 == current2) {
				--current1;
			} else {
				--current2;
			}
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR joint_iterator operator--(int) {
			joint_iterator temp(*this);
			if (first2 == current2) {
				--current1;
			} else {
				--current2;
			}
			return temp;
		}
		SPROUT_CONSTEXPR joint_iterator operator+(difference_type n) const {
			return advance_impl(n);
		}
		SPROUT_CONSTEXPR joint_iterator operator-(difference_type n) const {
			return advance_impl(-n);
		}
		SPROUT_CXX14_CONSTEXPR joint_iterator& operator+=(difference_type n) {
			joint_iterator temp(*this + n);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR joint_iterator& operator-=(difference_type n) {
			joint_iterator temp(*this - n);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR reference operator[](difference_type n) const {
			return *(*this + n);
		}
		SPROUT_CONSTEXPR joint_iterator next() const {
			return is_in_left() ? joint_iterator(sprout::next(current1), last1, first2, current2)
				: joint_iterator(current1, last1, first2, sprout::next(current2))
				;
		}
		SPROUT_CONSTEXPR joint_iterator prev() const {
			return first2 == current2 ? joint_iterator(sprout::prev(current1), last1, first2, current2)
				: joint_iterator(current1, last1, first2, sprout::prev(current2))
				;
		}
		SPROUT_CXX14_CONSTEXPR void swap(joint_iterator& other)
		SPROUT_NOEXCEPT_EXPR(
			SPROUT_NOEXCEPT_EXPR(sprout::swap(current1, other.current1))
			&& SPROUT_NOEXCEPT_EXPR(sprout::swap(last1, other.last1))
			&& SPROUT_NOEXCEPT_EXPR(sprout::swap(first2, other.first2))
			&& SPROUT_NOEXCEPT_EXPR(sprout::swap(current2, other.current2))
			)
		{
			sprout::swap(current1, other.current1);
			sprout::swap(last1, other.last1);
			sprout::swap(first2, other.first2);
			sprout::swap(current2, other.current2);
		}
	};

	template<
		typename LIterator1, typename RIterator1,
		typename LIterator2, typename RIterator2
	>
	inline SPROUT_CONSTEXPR bool operator==(
		sprout::joint_iterator<LIterator1, RIterator1> const& lhs,
		sprout::joint_iterator<LIterator2, RIterator2> const& rhs
		)
	{
		return lhs.base() == rhs.base() && lhs.base2() == rhs.base2();
	}
	template<
		typename LIterator1, typename RIterator1,
		typename LIterator2, typename RIterator2
	>
	inline SPROUT_CONSTEXPR bool operator!=(
		sprout::joint_iterator<LIterator1, RIterator1> const& lhs,
		sprout::joint_iterator<LIterator2, RIterator2> const& rhs
		)
	{
		return !(lhs == rhs);
	}
	template<
		typename LIterator1, typename RIterator1,
		typename LIterator2, typename RIterator2
	>
	inline SPROUT_CONSTEXPR bool operator<(
		sprout::joint_iterator<LIterator1, RIterator1> const& lhs,
		sprout::joint_iterator<LIterator2, RIterator2> const& rhs
		)
	{
		return lhs.is_in_left() && rhs.is_in_left() ? lhs.base() < rhs.base()
			: !lhs.is_in_left() && !rhs.is_in_left() ? lhs.base2() < rhs.base2()
			: lhs.is_in_left()
			;
	}
	template<
		typename LIterator1, typename RIterator1,
		typename LIterator2, typename RIterator2
	>
	inline SPROUT_CONSTEXPR bool operator>(
		sprout::joint_iterator<LIterator1, RIterator1> const& lhs,
		sprout::joint_iterator<LIterator2, RIterator2> const& rhs
		)
	{
		return rhs < lhs;
	}
	template<
		typename LIterator1, typename RIterator1,
		typename LIterator2, typename RIterator2
	>
	inline SPROUT_CONSTEXPR bool operator<=(
		sprout::joint_iterator<LIterator1, RIterator1> const& lhs,
		sprout::joint_iterator<LIterator2, RIterator2> const& rhs
		)
	{
		return !(rhs < lhs);
	}
	template<
		typename LIterator1, typename RIterator1,
		typename LIterator2, typename RIterator2
	>
	inline SPROUT_CONSTEXPR bool operator>=(
		sprout::joint_iterator<LIterator1, RIterator1> const& lhs,
		sprout::joint_iterator<LIterator2, RIterator2> const& rhs
		)
	{
		return !(lhs < rhs);
	}
	template<
		typename LIterator1, typename RIterator1,
		typename LIterator2, typename RIterator2
	>
	inline SPROUT_CONSTEXPR typename sprout::arithmetic_promote<
		typename sprout::joint_iterator<LIterator1, RIterator1>::difference_type,
		typename sprout::joint_iterator<LIterator2, RIterator2>::difference_type
	>::type
	operator-(
		sprout::joint_iterator<LIterator1, RIterator1> const& lhs,
		sprout::joint_iterator<LIterator2, RIterator2> const& rhs
		)
	{
		return lhs.is_in_left() && rhs.is_in_left() ? lhs.base() - rhs.base()
			: !lhs.is_in_left() && !rhs.is_in_left() ? lhs.base2() - rhs.base2()
			: lhs.is_in_left() ? sprout::limited::plus(lhs.left_end() - lhs.base(), rhs.base2() - rhs.right_begin())
			: sprout::limited::plus(lhs.base2() - lhs.right_begin(), rhs.left_end() - rhs.base())
			;
	}
	template<typename LIterator, typename RIterator>
	inline SPROUT_CONSTEXPR sprout::joint_iterator<LIterator, RIterator> operator+(
		typename sprout::joint_iterator<LIterator, RIterator>::difference_type n,
		sprout::joint_iterator<LIterator, RIterator> const& it
		)
	{
		return it + n;
	}

	//
	// make_joint_iterator
	//
	template<typename LIterator, typename RIterator>
	inline SPROUT_CONSTEXPR sprout::joint_iterator<LIterator, RIterator>
	make_joint_iterator(LIterator it1, LIterator last1, RIterator first2, RIterator it2) {
		return sprout::joint_iterator<LIterator, RIterator>(it1, last1, first2, it2);
	}
	template<typename LIterator, typename RIterator>
	inline SPROUT_CONSTEXPR sprout::joint_iterator<LIterator, RIterator>
	make_joint_iterator(LIterator it1, LIterator last1, RIterator first2) {
		return sprout::joint_iterator<LIterator, RIterator>(it1, last1, first2, first2);
	}
	template<typename LIterator, typename RIterator>
	inline SPROUT_CONSTEXPR sprout::joint_iterator<LIterator, RIterator>
	make_joint_iterator(LIterator last1, RIterator first2, RIterator it2) {
		return sprout::joint_iterator<LIterator, RIterator>(last1, last1, first2, it2);
	}

	//
	// swap
	//
	template<typename LIterator, typename RIterator>
	inline SPROUT_CXX14_CONSTEXPR void
	swap(
		sprout::joint_iterator<LIterator, RIterator>& lhs,
		sprout::joint_iterator<LIterator, RIterator>& rhs
		)
	SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs)))
	{
		lhs.swap(rhs);
	}

	//
	// iterator_next
	//
	template<typename LIterator, typename RIterator>
	inline SPROUT_CONSTEXPR sprout::joint_iterator<LIterator, RIterator>
	iterator_next(sprout::joint_iterator<LIterator, RIterator> const& it) {
		return it.next();
	}

	//
	// iterator_prev
	//
	template<typename LIterator, typename RIterator>
	inline SPROUT_CONSTEXPR sprout::joint_iterator<LIterator, RIterator>
	iterator_prev(sprout::joint_iterator<LIterator, RIterator> const& it) {
		return it.prev();
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_JOINT_ITERATOR_HPP
