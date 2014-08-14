/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ITERATOR_MOVE_ITERATOR_HPP
#define SPROUT_ITERATOR_MOVE_ITERATOR_HPP

#include <iterator>
#include <utility>
#include <sprout/config.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/iterator/prev.hpp>
#include <sprout/iterator/distance.hpp>
#include <sprout/iterator/const_iterator_cast.hpp>
#include <sprout/utility/swap.hpp>
#include <sprout/utility/move.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	//
	// move_iterator
	//
	template<typename Iterator>
	class move_iterator
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
		typedef typename std::iterator_traits<iterator_type>::iterator_category iterator_category;
		typedef typename std::iterator_traits<iterator_type>::value_type value_type;
		typedef typename std::iterator_traits<iterator_type>::difference_type difference_type;
		typedef Iterator pointer;
		typedef value_type&& reference;
	protected:
		iterator_type current;
	public:
		SPROUT_CONSTEXPR move_iterator() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
		SPROUT_CONSTEXPR move_iterator(move_iterator const& other)
			: current(other.current)
		{}
		explicit SPROUT_CONSTEXPR move_iterator(iterator_type it)
			: current(it)
		{}
		template<typename U>
		SPROUT_CONSTEXPR move_iterator(move_iterator<U> const& it)
			: current(it.base())
		{}
		template<typename U>
		SPROUT_CXX14_CONSTEXPR move_iterator& operator=(move_iterator<U> const& it) {
			move_iterator temp(it);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR iterator_type base() const {
			return current;
		}
		SPROUT_CONSTEXPR reference operator*() const {
			return sprout::move(*current);
		}
		SPROUT_CONSTEXPR pointer operator->() const {
			return current;
		}
		SPROUT_CXX14_CONSTEXPR move_iterator& operator++() {
			++current;
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR move_iterator operator++(int) {
			move_iterator result(*this);
			++current;
			return result;
		}
		SPROUT_CXX14_CONSTEXPR move_iterator& operator--() {
			--current;
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR move_iterator operator--(int) {
			move_iterator temp(*this);
			--current;
			return temp;
		}
		SPROUT_CONSTEXPR move_iterator operator+(difference_type n) const {
			return move_iterator(current + n);
		}
		SPROUT_CONSTEXPR move_iterator operator-(difference_type n) const {
			return move_iterator(current - n);
		}
		SPROUT_CXX14_CONSTEXPR move_iterator& operator+=(difference_type n) {
			move_iterator temp(current + n);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR move_iterator& operator-=(difference_type n) {
			move_iterator temp(current - n);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR reference operator[](difference_type n) const {
			return sprout::move(current[n]);
		}
		SPROUT_CONSTEXPR move_iterator next() const {
			return move_iterator(sprout::next(current));
		}
		SPROUT_CONSTEXPR move_iterator prev() const {
			return move_iterator(sprout::prev(current));
		}
		SPROUT_CXX14_CONSTEXPR void swap(move_iterator& other)
		SPROUT_NOEXCEPT_IF(
			SPROUT_NOEXCEPT_EXPR(swap(current, other.current))
			)
		{
			swap(current, other.current);
		}
	};

	template<typename Iterator1, typename Iterator2>
	inline SPROUT_CONSTEXPR bool
	operator==(sprout::move_iterator<Iterator1> const& lhs, sprout::move_iterator<Iterator2> const& rhs) {
		return lhs.base() == rhs.base();
	}
	template<typename Iterator1, typename Iterator2>
	inline SPROUT_CONSTEXPR bool
	operator!=(sprout::move_iterator<Iterator1> const& lhs, sprout::move_iterator<Iterator2> const& rhs) {
		return !(lhs == rhs);
	}
	template<typename Iterator1, typename Iterator2>
	inline SPROUT_CONSTEXPR bool
	operator<(sprout::move_iterator<Iterator1> const& lhs, sprout::move_iterator<Iterator2> const& rhs) {
		return lhs.base() < rhs.base();
	}
	template<typename Iterator1, typename Iterator2>
	inline SPROUT_CONSTEXPR bool
	operator>(sprout::move_iterator<Iterator1> const& lhs, sprout::move_iterator<Iterator2> const& rhs) {
		return rhs < lhs;
	}
	template<typename Iterator1, typename Iterator2>
	inline SPROUT_CONSTEXPR bool
	operator<=(sprout::move_iterator<Iterator1> const& lhs, sprout::move_iterator<Iterator2> const& rhs) {
		return !(rhs < lhs);
	}
	template<typename Iterator1, typename Iterator2>
	inline SPROUT_CONSTEXPR bool
	operator>=(sprout::move_iterator<Iterator1> const& lhs, sprout::move_iterator<Iterator2> const& rhs) {
		return !(lhs < rhs);
	}
	template<typename Iterator1, typename Iterator2>
	inline SPROUT_CONSTEXPR decltype(std::declval<Iterator1>() - std::declval<Iterator2>())
	operator-(sprout::move_iterator<Iterator1> const& lhs, sprout::move_iterator<Iterator2> const& rhs) {
		return lhs.base() - rhs.base();
	}
	template<typename Iterator>
	inline SPROUT_CONSTEXPR sprout::move_iterator<Iterator>
	operator+(
		typename sprout::move_iterator<Iterator>::difference_type n,
		sprout::move_iterator<Iterator> const& it
		)
	{
		return it + n;
	}

	//
	// make_move_iterator
	//
	template<typename Iterator>
	inline SPROUT_CONSTEXPR sprout::move_iterator<Iterator>
	make_move_iterator(Iterator it) {
		return sprout::move_iterator<Iterator>(it);
	}

	//
	// swap
	//
	template<typename Iterator>
	inline SPROUT_CXX14_CONSTEXPR void
	swap(sprout::move_iterator<Iterator>& lhs, sprout::move_iterator<Iterator>& rhs)
	SPROUT_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
	{
		lhs.swap(rhs);
	}

	//
	// iterator_next
	//
	template<typename Iterator>
	inline SPROUT_CONSTEXPR sprout::move_iterator<Iterator>
	iterator_next(sprout::move_iterator<Iterator> const& it) {
		return it.next();
	}

	//
	// iterator_prev
	//
	template<typename Iterator>
	inline SPROUT_CONSTEXPR sprout::move_iterator<Iterator>
	iterator_prev(sprout::move_iterator<Iterator> const& it) {
		return it.prev();
	}

	//
	// is_const_iterator_cast_convertible
	//
	template<typename FromIterator, typename ToIterator>
	struct is_const_iterator_cast_convertible<sprout::move_iterator<FromIterator>, sprout::move_iterator<ToIterator> >
		: public sprout::is_const_iterator_cast_convertible<FromIterator, ToIterator>
	{};
	//
	// const_iterator_conversion
	//
	template<
		typename T,
		typename Iterator,
		typename sprout::enabler_if<sprout::is_const_iterator_cast_convertible<sprout::move_iterator<Iterator>, T>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR T
	const_iterator_conversion(sprout::move_iterator<Iterator> const& it) {
		return T(sprout::const_iterator_cast<typename T::iterator_type>(it.base()));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_MOVE_ITERATOR_HPP
