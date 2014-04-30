/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ITERATOR_VALUE_ITERATOR_HPP
#define SPROUT_ITERATOR_VALUE_ITERATOR_HPP

#include <iterator>
#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/limits.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/iterator/prev.hpp>
#include <sprout/iterator/distance.hpp>
#include <sprout/utility/value_holder/value_holder.hpp>
#include <sprout/utility/swap.hpp>

namespace sprout {
	//
	// value_iterator
	//
	template<typename T>
	class value_iterator
		: public std::iterator<
			std::random_access_iterator_tag,
			typename sprout::value_holder<T>::value_type,
			std::ptrdiff_t,
			typename sprout::value_holder<T>::mutable_or_const_pointer,
			typename sprout::value_holder<T>::mutable_or_const_reference
		>
	{
	public:
		typedef T type;
		typedef typename std::conditional<
			std::is_reference<type>::value,
			typename std::decay<type>::type const&,
			typename std::decay<type>::type const
		>::type const_type;
	private:
		typedef std::iterator<
			std::random_access_iterator_tag,
			typename sprout::value_holder<T>::value_type,
			std::ptrdiff_t,
			typename sprout::value_holder<T>::mutable_or_const_pointer,
			typename sprout::value_holder<T>::mutable_or_const_reference
		> base_type;
	public:
		typedef typename base_type::iterator_category iterator_category;
		typedef typename base_type::value_type value_type;
		typedef typename base_type::difference_type difference_type;
		typedef typename base_type::pointer pointer;
		typedef typename base_type::reference reference;
	private:
		sprout::value_holder<T> holder_;
		difference_type index_;
	private:
		SPROUT_CONSTEXPR value_iterator(sprout::value_holder<T> const& r, difference_type index)
			: holder_(r), index_(index)
		{}
	public:
		SPROUT_CONSTEXPR value_iterator()
			: holder_(), index_()
		{}
		value_iterator(value_iterator const&) = default;
		explicit SPROUT_CONSTEXPR value_iterator(
			typename sprout::value_holder<T>::param_type p,
			difference_type index = sprout::numeric_limits<difference_type>::max()
			)
			: holder_(p), index_(index)
		{}
		SPROUT_CONSTEXPR operator value_iterator<const_type>() const {
			return value_iterator<const_type>(holder_.get(), index_);
		}
		SPROUT_CONSTEXPR difference_type index() const {
			return index_;
		}
		SPROUT_CONSTEXPR value_iterator next() const {
			return value_iterator(holder_, index_ - 1);
		}
		SPROUT_CONSTEXPR value_iterator prev() const {
			return value_iterator(holder_, index_ + 1);
		}
		SPROUT_CXX14_CONSTEXPR void swap(value_iterator& other)
		SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::swap(holder_, other.holder_)))
		{
			sprout::swap(holder_, other.holder_);
			sprout::swap(index_, other.index_);
		}
		SPROUT_CONSTEXPR reference operator*() const {
			return holder_.get();
		}
		SPROUT_CONSTEXPR pointer operator->() const {
			return holder_.get_pointer();
		}
		SPROUT_CXX14_CONSTEXPR value_iterator& operator++() {
			value_iterator temp(next());
			temp.swap(*this);
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR value_iterator operator++(int) {
			value_iterator result(*this);
			++*this;
			return result;
		}
		SPROUT_CXX14_CONSTEXPR value_iterator& operator--() {
			value_iterator temp(prev());
			temp.swap(*this);
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR value_iterator operator--(int) {
			value_iterator result(*this);
			--*this;
			return result;
		}
		SPROUT_CONSTEXPR value_iterator operator+(difference_type n) const {
			return value_iterator(holder_, index_ - n);
		}
		SPROUT_CONSTEXPR value_iterator operator-(difference_type n) const {
			return value_iterator(holder_, index_ + n);
		}
		SPROUT_CXX14_CONSTEXPR value_iterator& operator+=(difference_type n) {
			value_iterator temp(holder_, index_ - n);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR value_iterator& operator-=(difference_type n) {
			value_iterator temp(holder_, index_ + n);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR reference operator[](difference_type) const {
			return holder_.get();
		}
	};

	template<typename T>
	inline SPROUT_CONSTEXPR bool
	operator==(sprout::value_iterator<T> const& lhs, sprout::value_iterator<T> const& rhs) {
		return lhs.index() == rhs.index();
	}
	template<typename T>
	inline SPROUT_CONSTEXPR bool
	operator!=(sprout::value_iterator<T> const& lhs, sprout::value_iterator<T> const& rhs) {
		return !(lhs == rhs);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR bool
	operator<(sprout::value_iterator<T> const& lhs, sprout::value_iterator<T> const& rhs) {
		return rhs.index() < lhs.index();
	}
	template<typename T>
	inline SPROUT_CONSTEXPR bool
	operator>(sprout::value_iterator<T> const& lhs, sprout::value_iterator<T> const& rhs) {
		return rhs < lhs;
	}
	template<typename T>
	inline SPROUT_CONSTEXPR bool
	operator<=(sprout::value_iterator<T> const& lhs, sprout::value_iterator<T> const& rhs) {
		return !(rhs < lhs);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR bool
	operator>=(sprout::value_iterator<T> const& lhs, sprout::value_iterator<T> const& rhs) {
		return !(lhs < rhs);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR typename sprout::value_iterator<T>::difference_type
	operator-(sprout::value_iterator<T> const& lhs, sprout::value_iterator<T> const& rhs) {
		return rhs.index() - lhs.index();
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::value_iterator<T>
	operator+(typename sprout::value_iterator<T>::difference_type n, sprout::value_iterator<T> const& it) {
		return it + n;
	}

	//
	// swap
	//
	template<typename T>
	inline SPROUT_CXX14_CONSTEXPR void
	swap(sprout::value_iterator<T>& lhs, sprout::value_iterator<T>& rhs)
	SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs)))
	{
		lhs.swap(rhs);
	}

	//
	// iterator_next
	//
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::value_iterator<T>
	iterator_next(sprout::value_iterator<T> const& it) {
		return it.next();
	}

	//
	// iterator_prev
	//
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::value_iterator<T>
	iterator_prev(sprout::value_iterator<T> const& it) {
		return it.prev();
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_VALUE_ITERATOR_HPP
