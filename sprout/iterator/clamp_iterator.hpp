/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ITERATOR_CLAMP_ITERATOR_HPP
#define SPROUT_ITERATOR_CLAMP_ITERATOR_HPP

#include <iterator>
#include <utility>
#include <sprout/config.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/iterator/prev.hpp>
#include <sprout/algorithm/clamp.hpp>
#include <sprout/utility/swap.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	//
	// clamp_iterator
	//
	template<typename Iterator, typename Compare = NS_SSCRISK_CEL_OR_SPROUT::less<typename std::iterator_traits<Iterator>::value_type> >
	class clamp_iterator
		: public std::iterator<
			typename std::iterator_traits<Iterator>::iterator_category,
			typename std::iterator_traits<Iterator>::value_type,
			typename std::iterator_traits<Iterator>::difference_type,
			typename std::iterator_traits<Iterator>::pointer,
			typename std::iterator_traits<Iterator>::reference
		>
	{
	public:
		typedef Iterator iterator_type;
		typedef Compare compare_type;
		typedef typename std::iterator_traits<iterator_type>::iterator_category iterator_category;
		typedef typename std::iterator_traits<iterator_type>::value_type value_type;
		typedef typename std::iterator_traits<iterator_type>::difference_type difference_type;
		typedef typename std::iterator_traits<iterator_type>::pointer pointer;
		typedef typename std::iterator_traits<iterator_type>::reference reference;
	protected:
		iterator_type current;
		Compare comp;
		value_type low;
		value_type up;
	public:
		clamp_iterator() = default;
		clamp_iterator(clamp_iterator const&) = default;
		SPROUT_CONSTEXPR clamp_iterator(iterator_type it, value_type const& low, value_type const& up, Compare comp = Compare())
			: current(it), comp(comp), low(low), up(up)
		{}
		template<typename U, typename V>
		SPROUT_CONSTEXPR clamp_iterator(clamp_iterator<U, V> const& it)
			: current(it.current), comp(it.comp), low(it.low), up(it.up)
		{}
		template<typename U, typename V>
		SPROUT_CXX14_CONSTEXPR clamp_iterator& operator=(clamp_iterator<U, V> const& it) {
			clamp_iterator temp(it);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR iterator_type const& base() const {
			return current;
		}
		SPROUT_CONSTEXPR Compare const& compare() const {
			return comp;
		}
		SPROUT_CONSTEXPR value_type const& lower() const {
			return low;
		}
		SPROUT_CONSTEXPR value_type const& upper() const {
			return up;
		}
		SPROUT_CONSTEXPR reference operator*() const {
			return sprout::clamp(*current, low, up, comp);
		}
		SPROUT_CONSTEXPR pointer operator->() const {
			return &sprout::clamp(*current, low, up, comp);
		}

		SPROUT_CXX14_CONSTEXPR clamp_iterator& operator++() {
			++current;
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR clamp_iterator operator++(int) {
			clamp_iterator result(*this);
			++current;
			return result;
		}
		SPROUT_CXX14_CONSTEXPR clamp_iterator& operator--() {
			--current;
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR clamp_iterator operator--(int) {
			clamp_iterator temp(*this);
			--current;
			return temp;
		}
		SPROUT_CONSTEXPR clamp_iterator operator+(difference_type n) const {
			return clamp_iterator(sprout::next(current, n), low, up, comp);
		}
		SPROUT_CONSTEXPR clamp_iterator operator-(difference_type n) const {
			return clamp_iterator(sprout::prev(current, n), low, up, comp);
		}
		SPROUT_CXX14_CONSTEXPR clamp_iterator& operator+=(difference_type n) {
			clamp_iterator temp(sprout::next(current, n), low, up, comp);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR clamp_iterator& operator-=(difference_type n) {
			clamp_iterator temp(sprout::prev(current, n), low, up, comp);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR reference operator[](difference_type n) const {
			return sprout::clamp(*sprout::next(current, n), low, up, comp);
		}
		SPROUT_CONSTEXPR clamp_iterator next() const {
			return clamp_iterator(sprout::next(current), low, up, comp);
		}
		SPROUT_CONSTEXPR clamp_iterator prev() const {
			return clamp_iterator(sprout::prev(current), low, up, comp);
		}
		SPROUT_CXX14_CONSTEXPR void swap(clamp_iterator& other)
		SPROUT_NOEXCEPT_EXPR(
			SPROUT_NOEXCEPT_EXPR(sprout::swap(current, other.current))
			&& SPROUT_NOEXCEPT_EXPR(sprout::swap(comp, other.comp))
			&& SPROUT_NOEXCEPT_EXPR(sprout::swap(low, other.low))
			&& SPROUT_NOEXCEPT_EXPR(sprout::swap(up, other.up))
			)
		{
			sprout::swap(current, other.current);
			sprout::swap(comp, other.comp);
			sprout::swap(low, other.low);
			sprout::swap(up, other.up);
		}
	};

	template<typename Iterator1, typename Iterator2, typename Compare1, typename Compare2>
	inline SPROUT_CONSTEXPR bool operator==(
		sprout::clamp_iterator<Iterator1, Compare1> const& lhs,
		sprout::clamp_iterator<Iterator2, Compare2> const& rhs
		)
	{
		return lhs.base() == rhs.base();
	}
	template<typename Iterator1, typename Iterator2, typename Compare1, typename Compare2>
	inline SPROUT_CONSTEXPR bool
	operator!=(sprout::clamp_iterator<Iterator1, Compare1> const& lhs, sprout::clamp_iterator<Iterator2, Compare2> const& rhs) {
		return !(lhs == rhs);
	}
	template<typename Iterator1, typename Iterator2, typename Compare1, typename Compare2>
	inline SPROUT_CONSTEXPR bool
	operator<(sprout::clamp_iterator<Iterator1, Compare1> const& lhs, sprout::clamp_iterator<Iterator2, Compare2> const& rhs) {
		return lhs.base() < rhs.base();
	}
	template<typename Iterator1, typename Iterator2, typename Compare1, typename Compare2>
	inline SPROUT_CONSTEXPR bool
	operator>(sprout::clamp_iterator<Iterator1, Compare1> const& lhs, sprout::clamp_iterator<Iterator2, Compare2> const& rhs) {
		return rhs < lhs;
	}
	template<typename Iterator1, typename Iterator2, typename Compare1, typename Compare2>
	inline SPROUT_CONSTEXPR bool
	operator<=(sprout::clamp_iterator<Iterator1, Compare1> const& lhs, sprout::clamp_iterator<Iterator2, Compare2> const& rhs) {
		return !(rhs < lhs);
	}
	template<typename Iterator1, typename Iterator2, typename Compare1, typename Compare2>
	inline SPROUT_CONSTEXPR bool
	operator>=(sprout::clamp_iterator<Iterator1, Compare1> const& lhs, sprout::clamp_iterator<Iterator2, Compare2> const& rhs) {
		return !(lhs < rhs);
	}
	template<typename Iterator1, typename Iterator2, typename Compare1, typename Compare2>
	inline SPROUT_CONSTEXPR decltype(std::declval<Iterator1>() - std::declval<Iterator2>())
	operator-(sprout::clamp_iterator<Iterator1, Compare1> const& lhs, sprout::clamp_iterator<Iterator2, Compare2> const& rhs) {
		return lhs.base() - rhs.base();
	}
	template<typename Iterator, typename Compare>
	inline SPROUT_CONSTEXPR sprout::clamp_iterator<Iterator, Compare>
	operator+(
		typename sprout::clamp_iterator<Iterator, Compare>::difference_type n,
		sprout::clamp_iterator<Iterator, Compare> const& it
		)
	{
		return it + n;
	}

	//
	// make_clamp_iterator
	//
	template<typename Iterator, typename Compare>
	inline SPROUT_CONSTEXPR sprout::clamp_iterator<Iterator, Compare>
	make_clamp_iterator(
		Iterator it,
		typename std::iterator_traits<Iterator>::value_type const& low,
		typename std::iterator_traits<Iterator>::value_type const& up,
		Compare comp
		)
	{
		return sprout::clamp_iterator<Iterator, Compare>(it, low, up, comp);
	}
	template<typename Iterator, typename Compare>
	inline SPROUT_CONSTEXPR sprout::clamp_iterator<Iterator, Compare>
	make_clamp_iterator(
		Iterator it,
		typename std::iterator_traits<Iterator>::value_type const& low,
		typename std::iterator_traits<Iterator>::value_type const& up
		)
	{
		return sprout::clamp_iterator<Iterator, Compare>(it, low, up);
	}

	//
	// swap
	//
	template<typename Iterator, typename Compare>
	inline SPROUT_CXX14_CONSTEXPR void
	swap(sprout::clamp_iterator<Iterator, Compare>& lhs, sprout::clamp_iterator<Iterator, Compare>& rhs)
	SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs)))
	{
		lhs.swap(rhs);
	}

	//
	// iterator_next
	//
	template<typename Iterator, typename Compare>
	inline SPROUT_CONSTEXPR sprout::clamp_iterator<Iterator, Compare>
	iterator_next(sprout::clamp_iterator<Iterator, Compare> const& it) {
		return it.next();
	}

	//
	// iterator_prev
	//
	template<typename Iterator, typename Compare>
	inline SPROUT_CONSTEXPR sprout::clamp_iterator<Iterator, Compare>
	iterator_prev(sprout::clamp_iterator<Iterator, Compare> const& it) {
		return it.prev();
	}
}	// namespace sprout

#endif	// SPROUT_ITERATOR_CLAMP_ITERATOR_HPP
