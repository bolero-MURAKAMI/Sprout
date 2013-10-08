/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ITERATOR_PTR_INDEX_ITERATOR_HPP
#define SPROUT_ITERATOR_PTR_INDEX_ITERATOR_HPP

#include <iterator>
#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/iterator/prev.hpp>
#include <sprout/iterator/distance.hpp>
#include <sprout/iterator/detail/iterator_to_pointer.hpp>
#include <sprout/utility/swap.hpp>

namespace sprout {
	//
	// ptr_index_iterator
	//
	template<typename T, bool ConvertibleToPointer = false>
	class ptr_index_iterator
		: public std::iterator<
			typename std::iterator_traits<T*>::iterator_category,
			typename std::iterator_traits<T*>::value_type,
			typename std::iterator_traits<T*>::difference_type,
			typename std::iterator_traits<T*>::pointer,
			typename std::iterator_traits<T*>::reference
		>
		, public sprout::detail::iterator_to_pointer_base<
			sprout::ptr_index_iterator<T, ConvertibleToPointer>,
			typename std::iterator_traits<T*>::pointer,
			ConvertibleToPointer
		>
	{
	public:
		typedef T type;
	private:
		typedef std::iterator<
			typename std::iterator_traits<T*>::iterator_category,
			typename std::iterator_traits<T*>::value_type,
			typename std::iterator_traits<T*>::difference_type,
			typename std::iterator_traits<T*>::pointer,
			typename std::iterator_traits<T*>::reference
		> base_type;
	public:
		typedef typename base_type::iterator_category iterator_category;
		typedef typename base_type::value_type value_type;
		typedef typename base_type::difference_type difference_type;
		typedef typename base_type::pointer pointer;
		typedef typename base_type::reference reference;
		typedef typename std::remove_pointer<pointer>::type const* const_pointer;
	private:
		pointer p_;
		difference_type index_;
	public:
		SPROUT_CONSTEXPR ptr_index_iterator()
			: p_(), index_()
		{}
		ptr_index_iterator(ptr_index_iterator const&) = default;
		explicit SPROUT_CONSTEXPR ptr_index_iterator(pointer p)
			: p_(p), index_(0)
		{}
		SPROUT_CONSTEXPR ptr_index_iterator(pointer p, difference_type index)
			: p_(p), index_(index)
		{}
		SPROUT_CONSTEXPR operator ptr_index_iterator<const_pointer>() const {
			return ptr_index_iterator<const_pointer>(p_, index_);
		}
		SPROUT_CONSTEXPR pointer base() const {
			return p_;
		}
		SPROUT_CONSTEXPR difference_type index() const {
			return index_;
		}
		SPROUT_CONSTEXPR pointer ptr() const {
			return p_ + index_;
		}
		SPROUT_CONSTEXPR ptr_index_iterator next() const {
			return ptr_index_iterator(p_, index_ + 1);
		}
		SPROUT_CONSTEXPR ptr_index_iterator prev() const {
			return ptr_index_iterator(p_, index_ - 1);
		}
		SPROUT_CXX14_CONSTEXPR void swap(ptr_index_iterator& other)
		SPROUT_NOEXCEPT
		{
			sprout::swap(p_, other.p_);
			sprout::swap(index_, other.index_);
		}
		SPROUT_CONSTEXPR reference operator*() const {
			return p_[index_];
		}
		SPROUT_CONSTEXPR pointer operator->() const {
			return p_ + index_;
		}
		SPROUT_CXX14_CONSTEXPR ptr_index_iterator& operator++() {
			ptr_index_iterator temp(next());
			temp.swap(*this);
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR ptr_index_iterator operator++(int) {
			ptr_index_iterator result(*this);
			++*this;
			return result;
		}
		SPROUT_CXX14_CONSTEXPR ptr_index_iterator& operator--() {
			ptr_index_iterator temp(prev());
			temp.swap(*this);
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR ptr_index_iterator operator--(int) {
			ptr_index_iterator result(*this);
			--*this;
			return result;
		}
		SPROUT_CONSTEXPR ptr_index_iterator operator+(difference_type n) const {
			return ptr_index_iterator(p_, index_ + n);
		}
		SPROUT_CONSTEXPR ptr_index_iterator operator-(difference_type n) const {
			return ptr_index_iterator(p_, index_ - n);
		}
		SPROUT_CXX14_CONSTEXPR ptr_index_iterator& operator+=(difference_type n) {
			ptr_index_iterator temp(p_, index_ + n);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR ptr_index_iterator& operator-=(difference_type n) {
			ptr_index_iterator temp(p_, index_ - n);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR reference operator[](difference_type n) const {
			return p_[index_ + n];
		}
	};

	template<typename T1, typename T2, bool C>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		std::is_same<typename std::decay<T1>::type, typename std::decay<T2>::type>::value,
		bool
	>::type
	operator==(sprout::ptr_index_iterator<T1, C> const& lhs, sprout::ptr_index_iterator<T2, C> const& rhs) {
		return lhs.index() == rhs.index();
	}
	template<typename T1, typename T2, bool C>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		std::is_same<typename std::decay<T1>::type, typename std::decay<T2>::type>::value,
		bool
	>::type
	operator!=(sprout::ptr_index_iterator<T1, C> const& lhs, sprout::ptr_index_iterator<T2, C> const& rhs) {
		return !(lhs == rhs);
	}
	template<typename T1, typename T2, bool C>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		std::is_same<typename std::decay<T1>::type, typename std::decay<T2>::type>::value,
		bool
	>::type
	operator<(sprout::ptr_index_iterator<T1, C> const& lhs, sprout::ptr_index_iterator<T2, C> const& rhs) {
		return lhs.index() < rhs.index();
	}
	template<typename T1, typename T2, bool C>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		std::is_same<typename std::decay<T1>::type, typename std::decay<T2>::type>::value,
		bool
	>::type
	operator>(sprout::ptr_index_iterator<T1, C> const& lhs, sprout::ptr_index_iterator<T2, C> const& rhs) {
		return rhs < lhs;
	}
	template<typename T1, typename T2, bool C>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		std::is_same<typename std::decay<T1>::type, typename std::decay<T2>::type>::value,
		bool
	>::type
	operator<=(sprout::ptr_index_iterator<T1, C> const& lhs, sprout::ptr_index_iterator<T2, C> const& rhs) {
		return !(rhs < lhs);
	}
	template<typename T1, typename T2, bool C>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		std::is_same<typename std::decay<T1>::type, typename std::decay<T2>::type>::value,
		bool
	>::type
	operator>=(sprout::ptr_index_iterator<T1, C> const& lhs, sprout::ptr_index_iterator<T2, C> const& rhs) {
		return !(lhs < rhs);
	}
	template<typename T1, typename T2, bool C>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		std::is_same<typename std::decay<T1>::type, typename std::decay<T2>::type>::value,
		decltype(
			std::declval<typename std::iterator_traits<sprout::ptr_index_iterator<T1, C> >::difference_type>()
				- std::declval<typename std::iterator_traits<sprout::ptr_index_iterator<T2, C> >::difference_type>()
			)
	>::type
	operator-(sprout::ptr_index_iterator<T1, C> const& lhs, sprout::ptr_index_iterator<T2, C> const& rhs) {
		return lhs.index() - rhs.index();
	}
	template<typename T, bool C>
	inline SPROUT_CONSTEXPR sprout::ptr_index_iterator<T, C>
	operator+(typename sprout::ptr_index_iterator<T, C>::difference_type n, sprout::ptr_index_iterator<T, C> const& it) {
		return it + n;
	}

	//
	// swap
	//
	template<typename T>
	inline SPROUT_CXX14_CONSTEXPR void
	swap(sprout::ptr_index_iterator<T>& lhs, sprout::ptr_index_iterator<T>& rhs)
	SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs)))
	{
		lhs.swap(rhs);
	}

	//
	// make_ptr_index_iterator
	//
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::ptr_index_iterator<T>
	make_ptr_index_iterator(T* p) {
		return sprout::ptr_index_iterator<T>(p);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::ptr_index_iterator<T>
	make_ptr_index_iterator(T* p, typename sprout::ptr_index_iterator<T>::difference_type index) {
		return sprout::ptr_index_iterator<T>(p, index);
	}

	//
	// ptr_index
	//
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::ptr_index_iterator<T>
	ptr_index(T* p) {
		return sprout::make_ptr_index_iterator(p);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::ptr_index_iterator<T>
	ptr_index(T* p, typename std::iterator_traits<T*>::difference_type n) {
		return sprout::make_ptr_index_iterator(p, n);
	}

	template<typename Iterator>
	inline SPROUT_CONSTEXPR Iterator
	ptr_index(Iterator const& it) {
		return it;
	}
	template<typename Iterator>
	inline SPROUT_CONSTEXPR Iterator
	ptr_index(Iterator const& it, typename std::iterator_traits<Iterator>::difference_type n) {
		return sprout::next(it, n);
	}

	//
	// ptr_unindex
	//
	template<typename T>
	inline SPROUT_CONSTEXPR typename sprout::ptr_index_iterator<T>::pointer
	ptr_unindex(sprout::ptr_index_iterator<T> const& it) {
		return it.ptr();
	}
	template<typename Iterator>
	inline SPROUT_CONSTEXPR Iterator
	ptr_unindex(Iterator const& it) {
		return it;
	}

	//
	// is_ptr_index_iterator
	//
	template<typename T>
	struct is_ptr_index_iterator
		: public std::false_type
	{};
	template<typename T>
	struct is_ptr_index_iterator<T const>
		: public sprout::is_ptr_index_iterator<T>
	{};
	template<typename T>
	struct is_ptr_index_iterator<T const volatile>
		: public sprout::is_ptr_index_iterator<T>
	{};
	template<typename T>
	struct is_ptr_index_iterator<sprout::ptr_index_iterator<T> >
		: public std::true_type
	{};

	//
	// iterator_next
	//
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::ptr_index_iterator<T>
	iterator_next(sprout::ptr_index_iterator<T> const& it) {
		return it.next();
	}

	//
	// iterator_prev
	//
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::ptr_index_iterator<T>
	iterator_prev(sprout::ptr_index_iterator<T> const& it) {
		return it.prev();
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_PTR_INDEX_ITERATOR_HPP
