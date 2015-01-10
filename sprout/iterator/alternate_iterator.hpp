/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ITERATOR_ALTERNATE_ITERATOR_HPP
#define SPROUT_ITERATOR_ALTERNATE_ITERATOR_HPP

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

namespace sprout {
	//
	// alternate_iterator
	//
	template<typename LIterator, typename RIterator>
	class alternate_iterator
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
		iterator2_type current2;
		bool in_left;
	private:
		SPROUT_CONSTEXPR alternate_iterator advance_impl_1(difference_type n) const {
			return alternate_iterator(sprout::next(current1, n / 2), sprout::next(current2, n / 2), !(n % 2));
		}
		SPROUT_CONSTEXPR alternate_iterator advance_impl(difference_type n) const {
			return advance_impl_1(n + (!is_in_left() ? 1 : 0));
		}
		SPROUT_CONSTEXPR alternate_iterator(iterator_type it1, iterator2_type it2, bool in_left)
			: current1(it1), current2(it2), in_left(in_left)
		{}
	public:
		SPROUT_CONSTEXPR alternate_iterator()
			: current1(), current2(), in_left(true)
		{}
		alternate_iterator(alternate_iterator const&) = default;
		SPROUT_CONSTEXPR alternate_iterator(iterator_type it1, iterator2_type it2)
			: current1(it1), current2(it2), in_left(true)
		{}
		template<typename U, typename V>
		SPROUT_CONSTEXPR alternate_iterator(alternate_iterator<U, V> const& it)
			: current1(it.base()), current2(it.base2()), in_left(it.is_in_left())
		{}
		template<typename U, typename V>
		SPROUT_CXX14_CONSTEXPR alternate_iterator& operator=(alternate_iterator<U, V> const& it) {
			alternate_iterator temp(it);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR iterator_type base() const {
			return current1;
		}
		SPROUT_CONSTEXPR iterator2_type base2() const {
			return current2;
		}
		SPROUT_CONSTEXPR bool is_in_left() const {
			return in_left;
		}
		SPROUT_CONSTEXPR reference operator*() const {
			return is_in_left() ? *current1 : *current2;
		}
		SPROUT_CONSTEXPR pointer operator->() const {
			return &*(*this);
		}
		SPROUT_CXX14_CONSTEXPR alternate_iterator& operator++() {
			if (is_in_left()) {
				in_left = false;
			} else {
				in_left = true;
				++current1;
				++current2;
			}
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR alternate_iterator operator++(int) {
			alternate_iterator result(*this);
			if (is_in_left()) {
				in_left = false;
			} else {
				in_left = true;
				++current1;
				++current2;
			}
			return result;
		}
		SPROUT_CXX14_CONSTEXPR alternate_iterator& operator--() {
			if (is_in_left()) {
				in_left = false;
				--current1;
				--current2;
			} else {
				in_left = true;
			}
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR alternate_iterator operator--(int) {
			alternate_iterator temp(*this);
			if (is_in_left()) {
				in_left = false;
				--current1;
				--current2;
			} else {
				in_left = true;
			}
			return temp;
		}
		SPROUT_CONSTEXPR alternate_iterator operator+(difference_type n) const {
			return advance_impl(n);
		}
		SPROUT_CONSTEXPR alternate_iterator operator-(difference_type n) const {
			return advance_impl(-n);
		}
		SPROUT_CXX14_CONSTEXPR alternate_iterator& operator+=(difference_type n) {
			alternate_iterator temp(*this + n);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR alternate_iterator& operator-=(difference_type n) {
			alternate_iterator temp(*this - n);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR reference operator[](difference_type n) const {
			return *(*this + n);
		}
		SPROUT_CONSTEXPR alternate_iterator next() const {
			return is_in_left() ? alternate_iterator(current1, current2, false)
				: alternate_iterator(sprout::next(current1), sprout::next(current2), true)
				;
		}
		SPROUT_CONSTEXPR alternate_iterator prev() const {
			return is_in_left() ? alternate_iterator(sprout::prev(current1), sprout::prev(current2), false)
				: alternate_iterator(current1, current2, true)
				;
		}
		SPROUT_CXX14_CONSTEXPR void swap(alternate_iterator& other)
		SPROUT_NOEXCEPT_IF(
			SPROUT_NOEXCEPT_EXPR(sprout::swap(current1, other.current1))
			&& SPROUT_NOEXCEPT_EXPR(sprout::swap(current2, other.current2))
			&& SPROUT_NOEXCEPT_EXPR(sprout::swap(in_left, other.in_left))
			)
		{
			sprout::swap(current1, other.current1);
			sprout::swap(current2, other.current2);
			sprout::swap(in_left, other.in_left);
		}
	};

	template<
		typename LIterator1, typename RIterator1,
		typename LIterator2, typename RIterator2
	>
	inline SPROUT_CONSTEXPR bool operator==(
		sprout::alternate_iterator<LIterator1, RIterator1> const& lhs,
		sprout::alternate_iterator<LIterator2, RIterator2> const& rhs
		)
	{
		return lhs.base() == rhs.base() && (lhs.is_in_left() == rhs.is_in_left());
	}
	template<
		typename LIterator1, typename RIterator1,
		typename LIterator2, typename RIterator2
	>
	inline SPROUT_CONSTEXPR bool operator!=(
		sprout::alternate_iterator<LIterator1, RIterator1> const& lhs,
		sprout::alternate_iterator<LIterator2, RIterator2> const& rhs
		)
	{
		return !(lhs == rhs);
	}
	template<
		typename LIterator1, typename RIterator1,
		typename LIterator2, typename RIterator2
	>
	inline SPROUT_CONSTEXPR bool operator<(
		sprout::alternate_iterator<LIterator1, RIterator1> const& lhs,
		sprout::alternate_iterator<LIterator2, RIterator2> const& rhs
		)
	{
		return lhs.base() < rhs.base() || (lhs.base() == rhs.base() && lhs.is_in_left() && !rhs.is_in_left());
	}
	template<
		typename LIterator1, typename RIterator1,
		typename LIterator2, typename RIterator2
	>
	inline SPROUT_CONSTEXPR bool operator>(
		sprout::alternate_iterator<LIterator1, RIterator1> const& lhs,
		sprout::alternate_iterator<LIterator2, RIterator2> const& rhs
		)
	{
		return rhs < lhs;
	}
	template<
		typename LIterator1, typename RIterator1,
		typename LIterator2, typename RIterator2
	>
	inline SPROUT_CONSTEXPR bool operator<=(
		sprout::alternate_iterator<LIterator1, RIterator1> const& lhs,
		sprout::alternate_iterator<LIterator2, RIterator2> const& rhs
		)
	{
		return !(rhs < lhs);
	}
	template<
		typename LIterator1, typename RIterator1,
		typename LIterator2, typename RIterator2
	>
	inline SPROUT_CONSTEXPR bool operator>=(
		sprout::alternate_iterator<LIterator1, RIterator1> const& lhs,
		sprout::alternate_iterator<LIterator2, RIterator2> const& rhs
		)
	{
		return !(lhs < rhs);
	}
	template<
		typename LIterator1, typename RIterator1,
		typename LIterator2, typename RIterator2
	>
	inline SPROUT_CONSTEXPR decltype(std::declval<LIterator1>() - std::declval<LIterator2>())
	operator-(
		sprout::alternate_iterator<LIterator1, RIterator1> const& lhs,
		sprout::alternate_iterator<LIterator2, RIterator2> const& rhs
		)
	{
		return sprout::limited::plus(
			sprout::limited::multiplies(lhs.base() - rhs.base(), 2),
			lhs.is_in_left() ? (rhs.is_in_left() ? 0 : 1) : (rhs.is_in_left() ? 1 : 0)
			);
	}
	template<typename LIterator, typename RIterator>
	inline SPROUT_CONSTEXPR sprout::alternate_iterator<LIterator, RIterator> operator+(
		typename sprout::alternate_iterator<LIterator, RIterator>::difference_type n,
		sprout::alternate_iterator<LIterator, RIterator> const& it
		)
	{
		return it + n;
	}

	//
	// make_alternate_iterator
	//
	template<typename LIterator, typename RIterator>
	inline SPROUT_CONSTEXPR sprout::alternate_iterator<LIterator, RIterator>
	make_alternate_iterator(LIterator it1, RIterator it2) {
		return sprout::alternate_iterator<LIterator, RIterator>(it1, it2);
	}

	//
	// swap
	//
	template<typename LIterator, typename RIterator>
	inline SPROUT_CXX14_CONSTEXPR void
	swap(
		sprout::alternate_iterator<LIterator, RIterator>& lhs,
		sprout::alternate_iterator<LIterator, RIterator>& rhs
		)
	SPROUT_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
	{
		lhs.swap(rhs);
	}

	//
	// iterator_next
	//
	template<typename LIterator, typename RIterator>
	inline SPROUT_CONSTEXPR sprout::alternate_iterator<LIterator, RIterator>
	iterator_next(sprout::alternate_iterator<LIterator, RIterator> const& it) {
		return it.next();
	}

	//
	// iterator_prev
	//
	template<typename LIterator, typename RIterator>
	inline SPROUT_CONSTEXPR sprout::alternate_iterator<LIterator, RIterator>
	iterator_prev(sprout::alternate_iterator<LIterator, RIterator> const& it) {
		return it.prev();
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_ALTERNATE_ITERATOR_HPP
