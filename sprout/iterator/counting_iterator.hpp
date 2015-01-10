/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ITERATOR_COUNTING_ITERATOR_HPP
#define SPROUT_ITERATOR_COUNTING_ITERATOR_HPP

#include <iterator>
#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/iterator/prev.hpp>
#include <sprout/iterator/distance.hpp>
#include <sprout/utility/swap.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	//
	// counting_iterator
	//
	template<typename Incrementable>
	class counting_iterator
		: public std::iterator<
			std::random_access_iterator_tag,
			Incrementable,
			std::ptrdiff_t,
			Incrementable*,
			Incrementable
		>
	{
	public:
		typedef std::random_access_iterator_tag iterator_category;
		typedef Incrementable value_type;
		typedef std::ptrdiff_t difference_type;
		typedef value_type* pointer;
		typedef value_type reference;
	private:
		template<typename T, typename sprout::enabler_if<std::is_integral<T>::value>::type = sprout::enabler>
		static SPROUT_CONSTEXPR T
		default_value() {
			return sprout::numeric_limits<value_type>::max();
		}
		template<typename T, typename sprout::enabler_if<!std::is_integral<T>::value>::type = sprout::enabler>
		static SPROUT_CONSTEXPR T
		default_value() {
			return T();
		}
	private:
		value_type current_;
	public:
		SPROUT_CONSTEXPR counting_iterator()
			: current_(default_value<value_type>())
		{}
		counting_iterator(counting_iterator const&) = default;
		explicit SPROUT_CONSTEXPR counting_iterator(value_type const& v)
			: current_(v)
		{}
		template<typename U>
		SPROUT_CONSTEXPR counting_iterator(counting_iterator<U> const& it)
			: current_(it.current_)
		{}
		template<typename U>
		SPROUT_CXX14_CONSTEXPR counting_iterator& operator=(counting_iterator<U> const& it) {
			counting_iterator temp(it);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR reference operator*() const {
			return current_;
		}
		SPROUT_CONSTEXPR pointer operator->() const {
			return &current_;
		}
		SPROUT_CXX14_CONSTEXPR counting_iterator& operator++() {
			++current_;
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR counting_iterator operator++(int) {
			counting_iterator result(*this);
			++current_;
			return result;
		}
		SPROUT_CXX14_CONSTEXPR counting_iterator& operator--() {
			--current_;
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR counting_iterator operator--(int) {
			counting_iterator temp(*this);
			--current_;
			return temp;
		}
		SPROUT_CONSTEXPR counting_iterator operator+(difference_type n) const {
			return counting_iterator(current_ + n);
		}
		SPROUT_CONSTEXPR counting_iterator operator-(difference_type n) const {
			return counting_iterator(current_ - n);
		}
		SPROUT_CXX14_CONSTEXPR counting_iterator& operator+=(difference_type n) {
			counting_iterator temp(current_ + n);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR counting_iterator& operator-=(difference_type n) {
			counting_iterator temp(current_ - n);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR reference operator[](difference_type n) const {
			return current_ + n;
		}
		SPROUT_CONSTEXPR counting_iterator next() const {
			return counting_iterator(current_ + 1);
		}
		SPROUT_CONSTEXPR counting_iterator prev() const {
			return counting_iterator(current_ - 1);
		}
		SPROUT_CXX14_CONSTEXPR void swap(counting_iterator& other)
		SPROUT_NOEXCEPT_IF_EXPR(sprout::swap(current_, other.current_))
		{
			sprout::swap(current_, other.current_);
		}
	};

	template<typename Incrementable1, typename Incrementable2>
	inline SPROUT_CONSTEXPR bool
	operator==(sprout::counting_iterator<Incrementable1> const& lhs, sprout::counting_iterator<Incrementable2> const& rhs) {
		return *lhs == *rhs;
	}
	template<typename Incrementable1, typename Incrementable2>
	inline SPROUT_CONSTEXPR bool
	operator!=(sprout::counting_iterator<Incrementable1> const& lhs, sprout::counting_iterator<Incrementable2> const& rhs) {
		return !(lhs == rhs);
	}
	template<typename Incrementable1, typename Incrementable2>
	inline SPROUT_CONSTEXPR bool
	operator<(sprout::counting_iterator<Incrementable1> const& lhs, sprout::counting_iterator<Incrementable2> const& rhs) {
		return *lhs < *rhs;
	}
	template<typename Incrementable1, typename Incrementable2>
	inline SPROUT_CONSTEXPR bool
	operator>(sprout::counting_iterator<Incrementable1> const& lhs, sprout::counting_iterator<Incrementable2> const& rhs) {
		return rhs < lhs;
	}
	template<typename Incrementable1, typename Incrementable2>
	inline SPROUT_CONSTEXPR bool
	operator<=(sprout::counting_iterator<Incrementable1> const& lhs, sprout::counting_iterator<Incrementable2> const& rhs) {
		return !(rhs < lhs);
	}
	template<typename Incrementable1, typename Incrementable2>
	inline SPROUT_CONSTEXPR bool
	operator>=(sprout::counting_iterator<Incrementable1> const& lhs, sprout::counting_iterator<Incrementable2> const& rhs) {
		return !(lhs < rhs);
	}
	template<typename Incrementable1, typename Incrementable2>
	inline SPROUT_CONSTEXPR typename sprout::counting_iterator<Incrementable1>::difference_type
	operator-(sprout::counting_iterator<Incrementable1> const& lhs, sprout::counting_iterator<Incrementable2> const& rhs) {
		return static_cast<typename sprout::counting_iterator<Incrementable1>::difference_type>(*lhs - *rhs);
	}
	template<typename Incrementable>
	inline SPROUT_CONSTEXPR sprout::counting_iterator<Incrementable>
	operator+(
		typename sprout::counting_iterator<Incrementable>::difference_type n,
		sprout::counting_iterator<Incrementable> const& it
		)
	{
		return it + n;
	}

	//
	// make_counting_iterator
	//
	template<typename Incrementable>
	inline SPROUT_CONSTEXPR sprout::counting_iterator<Incrementable>
	make_counting_iterator(Incrementable const& v) {
		return sprout::counting_iterator<Incrementable>(v);
	}

	//
	// swap
	//
	template<typename Incrementable>
	inline SPROUT_CXX14_CONSTEXPR void
	swap(sprout::counting_iterator<Incrementable>& lhs, sprout::counting_iterator<Incrementable>& rhs)
	SPROUT_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
	{
		lhs.swap(rhs);
	}

	//
	// iterator_next
	//
	template<typename Incrementable>
	inline SPROUT_CONSTEXPR sprout::counting_iterator<Incrementable>
	iterator_next(sprout::counting_iterator<Incrementable> const& it) {
		return it.next();
	}

	//
	// iterator_prev
	//
	template<typename Incrementable>
	inline SPROUT_CONSTEXPR sprout::counting_iterator<Incrementable>
	iterator_prev(sprout::counting_iterator<Incrementable> const& it) {
		return it.prev();
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_COUNTING_ITERATOR_HPP
