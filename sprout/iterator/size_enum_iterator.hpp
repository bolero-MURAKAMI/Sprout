/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ITERATOR_SIZE_ENUM_ITERATOR_HPP
#define SPROUT_ITERATOR_SIZE_ENUM_ITERATOR_HPP

#include <iterator>
#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/iterator/prev.hpp>
#include <sprout/iterator/distance.hpp>
#include <sprout/container/size.hpp>
#include <sprout/utility/swap.hpp>

namespace sprout {
	//
	// size_enum_iterator
	//
	template<typename Iterator, bool Separated = false>
	class size_enum_iterator
		: public std::iterator<
			typename std::iterator_traits<Iterator>::iterator_category,
			typename sprout::container_traits<
				typename std::iterator_traits<Iterator>::value_type
			>::difference_type,
			typename std::iterator_traits<Iterator>::difference_type,
			typename sprout::container_traits<
				typename std::iterator_traits<Iterator>::value_type
			>::difference_type*,
			typename sprout::container_traits<
				typename std::iterator_traits<Iterator>::value_type
			>::difference_type
		>
	{
	public:
		typedef Iterator iterator_type;
		typedef typename std::iterator_traits<iterator_type>::iterator_category iterator_category;
		typedef typename sprout::container_traits<
			typename std::iterator_traits<Iterator>::value_type
		>::difference_type value_type;
		typedef value_type reference;
		typedef typename std::iterator_traits<iterator_type>::difference_type difference_type;
		typedef value_type* pointer;
	protected:
		iterator_type current;
	public:
		SPROUT_CONSTEXPR size_enum_iterator()
			: current()
		{}
		size_enum_iterator(size_enum_iterator const&) = default;
		explicit SPROUT_CONSTEXPR size_enum_iterator(iterator_type it)
			: current(it)
		{}
		template<typename U>
		SPROUT_CONSTEXPR size_enum_iterator(size_enum_iterator<U> const& it)
			: current(it.current)
		{}
		template<typename U>
		SPROUT_CXX14_CONSTEXPR size_enum_iterator& operator=(size_enum_iterator<U> const& it) {
			size_enum_iterator temp(it);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR iterator_type base() const {
			return current;
		}
		SPROUT_CONSTEXPR bool is_separator() const {
			return false;
		}
		SPROUT_CONSTEXPR reference operator*() const {
			return sprout::size(*current);
		}
		SPROUT_CONSTEXPR pointer operator->() const {
			return &sprout::size(*current);
		}
		SPROUT_CXX14_CONSTEXPR size_enum_iterator& operator++() {
			++current;
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR size_enum_iterator operator++(int) {
			size_enum_iterator result(*this);
			++current;
			return result;
		}
		SPROUT_CXX14_CONSTEXPR size_enum_iterator& operator--() {
			--current;
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR size_enum_iterator operator--(int) {
			size_enum_iterator temp(*this);
			--current;
			return temp;
		}
		SPROUT_CONSTEXPR size_enum_iterator operator+(difference_type n) const {
			return size_enum_iterator(current + n);
		}
		SPROUT_CONSTEXPR size_enum_iterator operator-(difference_type n) const {
			return size_enum_iterator(current - n);
		}
		SPROUT_CXX14_CONSTEXPR size_enum_iterator& operator+=(difference_type n) {
			size_enum_iterator temp(current + n);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR size_enum_iterator& operator-=(difference_type n) {
			size_enum_iterator temp(current - n);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR reference operator[](difference_type n) const {
			return sprout::size(current[n]);
		}
		SPROUT_CONSTEXPR size_enum_iterator next() const {
			return size_enum_iterator(sprout::next(current));
		}
		SPROUT_CONSTEXPR size_enum_iterator prev() const {
			return size_enum_iterator(sprout::prev(current));
		}
		SPROUT_CXX14_CONSTEXPR void swap(size_enum_iterator& other)
		SPROUT_NOEXCEPT_IF_EXPR(sprout::swap(current, other.current))
		{
			sprout::swap(current, other.current);
		}
	};

	//
	// size_enum_iterator
	//
	template<typename Iterator>
	class size_enum_iterator<Iterator, true>
		: public std::iterator<
			typename std::iterator_traits<Iterator>::iterator_category,
			typename sprout::container_traits<
				typename std::iterator_traits<Iterator>::value_type
			>::difference_type,
			typename std::iterator_traits<Iterator>::difference_type,
			typename sprout::container_traits<
				typename std::iterator_traits<Iterator>::value_type
			>::difference_type*,
			typename sprout::container_traits<
				typename std::iterator_traits<Iterator>::value_type
			>::difference_type
		>
	{
	public:
		typedef Iterator iterator_type;
		typedef typename std::iterator_traits<iterator_type>::iterator_category iterator_category;
		typedef typename sprout::container_traits<
			typename std::iterator_traits<Iterator>::value_type
		>::difference_type value_type;
		typedef value_type reference;
		typedef typename std::iterator_traits<iterator_type>::difference_type difference_type;
		typedef value_type* pointer;
	protected:
		iterator_type current;
		value_type sep_size;
		bool is_sep;
	public:
		SPROUT_CONSTEXPR size_enum_iterator()
			: current(), sep_size(), is_sep()
		{}
		size_enum_iterator(size_enum_iterator const&) = default;
		explicit SPROUT_CONSTEXPR size_enum_iterator(iterator_type it, value_type size = 0, bool sep = false)
			: current(it)
			, sep_size(size)
			, is_sep(sep)
		{}
		template<typename U, bool V>
		SPROUT_CONSTEXPR size_enum_iterator(size_enum_iterator<U, V> const& it)
			: current(it.current)
			, sep_size(it.sep_size)
			, is_sep(it.is_sep)
		{}
		template<typename U, bool V>
		SPROUT_CXX14_CONSTEXPR size_enum_iterator& operator=(size_enum_iterator<U, V> const& it) {
			size_enum_iterator temp(it);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR iterator_type base() const {
			return current;
		}
		SPROUT_CONSTEXPR value_type separator_size() const {
			return sep_size;
		}
		SPROUT_CONSTEXPR bool is_separator() const {
			return is_sep;
		}
		SPROUT_CONSTEXPR reference operator*() const {
			return is_sep ? sep_size : sprout::size(*current);
		}
		SPROUT_CONSTEXPR pointer operator->() const {
			return &(is_sep ? sep_size : sprout::size(*current));
		}
		SPROUT_CXX14_CONSTEXPR size_enum_iterator& operator++() {
			if (is_sep) {
				++current;
				is_sep = false;
			} else {
				is_sep = true;
			}
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR size_enum_iterator operator++(int) {
			size_enum_iterator result(*this);
			if (is_sep) {
				++current;
				is_sep = false;
			} else {
				is_sep = true;
			}
			return result;
		}
		SPROUT_CXX14_CONSTEXPR size_enum_iterator& operator--() {
			if (is_sep) {
				is_sep = false;
			} else {
				--current;
				is_sep = true;
			}
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR size_enum_iterator operator--(int) {
			size_enum_iterator temp(*this);
			if (is_sep) {
				is_sep = false;
			} else {
				--current;
				is_sep = true;
			}
			return temp;
		}
		SPROUT_CONSTEXPR size_enum_iterator operator+(difference_type n) const {
			return size_enum_iterator(current + (n + is_sep) / 2, sep_size, (n + is_sep) % 2);
		}
		SPROUT_CONSTEXPR size_enum_iterator operator-(difference_type n) const {
			return size_enum_iterator(current - (n - is_sep) / 2, sep_size, (n - is_sep) % 2);
		}
		SPROUT_CXX14_CONSTEXPR size_enum_iterator& operator+=(difference_type n) {
			size_enum_iterator temp(current + (n + is_sep) / 2, sep_size, (n + is_sep) % 2);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR size_enum_iterator& operator-=(difference_type n) {
			size_enum_iterator temp(current - (n - is_sep) / 2, sep_size, (n - is_sep) % 2);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR reference operator[](difference_type n) const {
			return sprout::size(current[(n + is_sep) / 2]);
		}
		SPROUT_CONSTEXPR size_enum_iterator next() const {
			return is_sep
				? size_enum_iterator(sprout::next(current), sep_size, false)
				: size_enum_iterator(current, sep_size, true)
				;
		}
		SPROUT_CONSTEXPR size_enum_iterator prev() const {
			return is_sep
				? size_enum_iterator(current, sep_size, false)
				: size_enum_iterator(sprout::prev(current), sep_size, true)
				;
		}
		SPROUT_CXX14_CONSTEXPR void swap(size_enum_iterator& other)
		SPROUT_NOEXCEPT_IF_EXPR(sprout::swap(current, other.current))
		{
			sprout::swap(current, other.current);
			sprout::swap(sep_size, other.sep_size);
			sprout::swap(is_sep, other.is_sep);
		}
	};

	template<
		typename Iterator1, bool Separated1,
		typename Iterator2, bool Separated2
	>
	inline SPROUT_CONSTEXPR bool
	operator==(
		sprout::size_enum_iterator<Iterator1, Separated1> const& lhs,
		sprout::size_enum_iterator<Iterator2, Separated2> const& rhs
		)
	{
		return lhs.base() == rhs.base() && lhs.is_separator() == rhs.is_separator();
	}
	template<
		typename Iterator1, bool Separated1,
		typename Iterator2, bool Separated2
	>
	inline SPROUT_CONSTEXPR bool
	operator!=(
		sprout::size_enum_iterator<Iterator1, Separated1> const& lhs,
		sprout::size_enum_iterator<Iterator2, Separated2> const& rhs
		)
	{
		return !(lhs == rhs);
	}
	template<
		typename Iterator1, bool Separated1,
		typename Iterator2, bool Separated2
	>
	inline SPROUT_CONSTEXPR bool
	operator<(
		sprout::size_enum_iterator<Iterator1, Separated1> const& lhs,
		sprout::size_enum_iterator<Iterator2, Separated2> const& rhs
		)
	{
		return lhs.base() < rhs.base()
			|| (lhs.base() == rhs.base() && !lhs.is_separator() && rhs.is_separator())
			;
	}
	template<
		typename Iterator1, bool Separated1,
		typename Iterator2, bool Separated2
	>
	inline SPROUT_CONSTEXPR bool
	operator>(
		sprout::size_enum_iterator<Iterator1, Separated1> const& lhs,
		sprout::size_enum_iterator<Iterator2, Separated2> const& rhs
		)
	{
		return rhs < lhs;
	}
	template<
		typename Iterator1, bool Separated1,
		typename Iterator2, bool Separated2
	>
	inline SPROUT_CONSTEXPR bool
	operator<=(
		sprout::size_enum_iterator<Iterator1, Separated1> const& lhs,
		sprout::size_enum_iterator<Iterator2, Separated2> const& rhs
		)
	{
		return !(rhs < lhs);
	}
	template<
		typename Iterator1, bool Separated1,
		typename Iterator2, bool Separated2
	>
	inline SPROUT_CONSTEXPR bool
	operator>=(
		sprout::size_enum_iterator<Iterator1, Separated1> const& lhs,
		sprout::size_enum_iterator<Iterator2, Separated2> const& rhs
		)
	{
		return !(lhs < rhs);
	}
	template<typename Iterator1, typename Iterator2>
	inline SPROUT_CONSTEXPR decltype(std::declval<Iterator1>() - std::declval<Iterator2>())
	operator-(
		sprout::size_enum_iterator<Iterator1> const& lhs,
		sprout::size_enum_iterator<Iterator2> const& rhs
		)
	{
		return lhs.base() - rhs.base();
	}
	template<typename Iterator1, typename Iterator2>
	inline SPROUT_CONSTEXPR decltype(std::declval<Iterator1>() - std::declval<Iterator2>())
	operator-(
		sprout::size_enum_iterator<Iterator1, true> const& lhs,
		sprout::size_enum_iterator<Iterator2, true> const& rhs
		)
	{
		return lhs.base() - rhs.base() + (
			lhs.is_separator()
				? rhs.is_separator() ? 0 : -1
				: rhs.is_separator() ? 1 : 0
				)
		;
	}
	template<typename Iterator, bool Separated>
	inline SPROUT_CONSTEXPR sprout::size_enum_iterator<Iterator, Separated>
	operator+(
		typename sprout::size_enum_iterator<Iterator, Separated>::difference_type n,
		sprout::size_enum_iterator<Iterator, Separated> const& it
		)
	{
		return it + n;
	}

	//
	// make_size_enum_iterator
	//
	template<typename Iterator>
	inline SPROUT_CONSTEXPR sprout::size_enum_iterator<Iterator>
	make_size_enum_iterator(Iterator it) {
		return sprout::size_enum_iterator<Iterator>(it);
	}
	template<typename Iterator>
	inline SPROUT_CONSTEXPR sprout::size_enum_iterator<Iterator, true>
	make_size_enum_iterator(
		Iterator it,
		typename sprout::size_enum_iterator<Iterator, true>::value_type sep_size,
		bool sep = false
		)
	{
		return sprout::size_enum_iterator<Iterator, true>(it, sep_size, sep);
	}

	//
	// swap
	//
	template<typename Iterator, bool Separated>
	inline SPROUT_CXX14_CONSTEXPR void
	swap(sprout::size_enum_iterator<Iterator, Separated>& lhs, sprout::size_enum_iterator<Iterator, Separated>& rhs)
	SPROUT_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
	{
		lhs.swap(rhs);
	}

	//
	// iterator_next
	//
	template<typename Iterator, bool Separated>
	inline SPROUT_CONSTEXPR sprout::size_enum_iterator<Iterator, Separated>
	iterator_next(sprout::size_enum_iterator<Iterator, Separated> const& it) {
		return it.next();
	}

	//
	// iterator_prev
	//
	template<typename Iterator, bool Separated>
	inline SPROUT_CONSTEXPR sprout::size_enum_iterator<Iterator, Separated>
	iterator_prev(sprout::size_enum_iterator<Iterator, Separated> const& it) {
		return it.prev();
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_SIZE_ENUM_ITERATOR_HPP
