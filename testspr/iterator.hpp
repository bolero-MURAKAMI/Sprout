/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef TESTSPR_ITERATOR_HPP
#define TESTSPR_ITERATOR_HPP

#include <iterator>
#include <utility>
#include <sprout/config.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/iterator/prev.hpp>
#include <sprout/iterator/distance.hpp>
#include <sprout/utility/swap.hpp>
#include <sprout/type_traits/is_convert_constructible.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace testspr {
	//
	// reduce_iterator
	//
	template<typename Iterator, typename Category = typename std::iterator_traits<Iterator>::iterator_category>
	class reduce_iterator
		: public std::iterator<
			Category,
			typename std::iterator_traits<Iterator>::value_type,
			typename std::iterator_traits<Iterator>::difference_type,
			typename std::iterator_traits<Iterator>::pointer,
			typename std::iterator_traits<Iterator>::reference
		>
	{
	public:
		typedef Iterator iterator_type;
		typedef Category iterator_category;
		typedef typename std::iterator_traits<iterator_type>::value_type value_type;
		typedef typename std::iterator_traits<iterator_type>::difference_type difference_type;
		typedef typename std::iterator_traits<iterator_type>::pointer pointer;
		typedef typename std::iterator_traits<iterator_type>::reference reference;
	protected:
		iterator_type current;
	public:
		SPROUT_CONSTEXPR reduce_iterator()
			: current()
		{}
		reduce_iterator(reduce_iterator const& other) = default;
		explicit SPROUT_CONSTEXPR reduce_iterator(iterator_type it)
			: current(it)
		{}
		template<typename U, typename V, typename sprout::enabler_if<sprout::is_convert_constructible<Iterator, U>::value>::type = sprout::enabler>
		SPROUT_CONSTEXPR reduce_iterator(reduce_iterator<U, V> const& it)
			: current(it.base())
		{}
		template<typename U, typename V, typename sprout::enabler_if<sprout::is_convert_constructible<Iterator, U>::value>::type = sprout::enabler>
		SPROUT_CXX14_CONSTEXPR reduce_iterator& operator=(reduce_iterator<U, V> const& it) {
			reduce_iterator temp(it);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR iterator_type base() const {
			return current;
		}
		SPROUT_CONSTEXPR reference operator*() const {
			return *current;
		}
		SPROUT_CONSTEXPR pointer operator->() const {
			return &*current;
		}
		SPROUT_CXX14_CONSTEXPR reduce_iterator& operator++() {
			++current;
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR reduce_iterator operator++(int) {
			reduce_iterator result(*this);
			++current;
			return result;
		}
		SPROUT_CXX14_CONSTEXPR reduce_iterator& operator--() {
			--current;
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR reduce_iterator operator--(int) {
			reduce_iterator temp(*this);
			--current;
			return temp;
		}
		SPROUT_CONSTEXPR reduce_iterator operator+(difference_type n) const {
			return reduce_iterator(current + n);
		}
		SPROUT_CONSTEXPR reduce_iterator operator-(difference_type n) const {
			return reduce_iterator(current - n);
		}
		SPROUT_CXX14_CONSTEXPR reduce_iterator& operator+=(difference_type n) {
			reduce_iterator temp(current + n);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR reduce_iterator& operator-=(difference_type n) {
			reduce_iterator temp(current - n);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR reference operator[](difference_type n) const {
			return current[n];
		}
		SPROUT_CONSTEXPR reduce_iterator next() const {
			return reduce_iterator(sprout::next(current));
		}
		SPROUT_CONSTEXPR reduce_iterator prev() const {
			return reduce_iterator(sprout::prev(current));
		}
		SPROUT_CXX14_CONSTEXPR void swap(reduce_iterator& other)
		SPROUT_NOEXCEPT_IF(
			SPROUT_NOEXCEPT_EXPR(swap(current, other.current))
			)
		{
			using std::swap;
			swap(current, other.current);
		}
	};

	template<typename Iterator1, typename Category1, typename Iterator2, typename Category2>
	inline SPROUT_CONSTEXPR bool
	operator==(testspr::reduce_iterator<Iterator1, Category1> const& lhs, testspr::reduce_iterator<Iterator2, Category2> const& rhs) {
		return lhs.base() == rhs.base();
	}
	template<typename Iterator1, typename Category1, typename Iterator2, typename Category2>
	inline SPROUT_CONSTEXPR bool
	operator!=(testspr::reduce_iterator<Iterator1, Category1> const& lhs, testspr::reduce_iterator<Iterator2, Category2> const& rhs) {
		return !(lhs == rhs);
	}
	template<typename Iterator1, typename Category1, typename Iterator2, typename Category2>
	inline SPROUT_CONSTEXPR bool
	operator<(testspr::reduce_iterator<Iterator1, Category1> const& lhs, testspr::reduce_iterator<Iterator2, Category2> const& rhs) {
		return lhs.base() < rhs.base();
	}
	template<typename Iterator1, typename Category1, typename Iterator2, typename Category2>
	inline SPROUT_CONSTEXPR bool
	operator>(testspr::reduce_iterator<Iterator1, Category1> const& lhs, testspr::reduce_iterator<Iterator2, Category2> const& rhs) {
		return rhs < lhs;
	}
	template<typename Iterator1, typename Category1, typename Iterator2, typename Category2>
	inline SPROUT_CONSTEXPR bool
	operator<=(testspr::reduce_iterator<Iterator1, Category1> const& lhs, testspr::reduce_iterator<Iterator2, Category2> const& rhs) {
		return !(rhs < lhs);
	}
	template<typename Iterator1, typename Category1, typename Iterator2, typename Category2>
	inline SPROUT_CONSTEXPR bool
	operator>=(testspr::reduce_iterator<Iterator1, Category1> const& lhs, testspr::reduce_iterator<Iterator2, Category2> const& rhs) {
		return !(lhs < rhs);
	}
	template<typename Iterator1, typename Category1, typename Iterator2, typename Category2>
	inline SPROUT_CONSTEXPR decltype(std::declval<Iterator1>() - std::declval<Iterator2>())
	operator-(testspr::reduce_iterator<Iterator1, Category1> const& lhs, testspr::reduce_iterator<Iterator2, Category2> const& rhs) {
		return lhs.base() - rhs.base();
	}
	template<typename Iterator, typename Category>
	inline SPROUT_CONSTEXPR testspr::reduce_iterator<Iterator, Category>
	operator+(
		typename testspr::reduce_iterator<Iterator, Category>::difference_type n,
		testspr::reduce_iterator<Iterator, Category> const& it
		)
	{
		return it + n;
	}

	//
	// make_reduce_iterator
	//
	template<typename Iterator>
	inline SPROUT_CONSTEXPR testspr::reduce_iterator<Iterator>
	make_reduce_iterator(Iterator it) {
		return testspr::reduce_iterator<Iterator>(it);
	}
	template<typename Category, typename Iterator>
	inline SPROUT_CONSTEXPR testspr::reduce_iterator<Iterator, Category>
	make_reduce_iterator(Iterator it) {
		return testspr::reduce_iterator<Iterator, Category>(it);
	}

	//
	// reduce_input
	// reduce_forward
	// reduce_bidirectional
	// reduce_random_access
	//
	template<typename Iterator>
	inline SPROUT_CONSTEXPR testspr::reduce_iterator<Iterator, std::input_iterator_tag>
	reduce_input(Iterator it) {
		return testspr::reduce_iterator<Iterator, std::input_iterator_tag>(it);
	}
	template<typename Iterator>
	inline SPROUT_CONSTEXPR testspr::reduce_iterator<Iterator, std::forward_iterator_tag>
	reduce_forward(Iterator it) {
		return testspr::reduce_iterator<Iterator, std::forward_iterator_tag>(it);
	}
	template<typename Iterator>
	inline SPROUT_CONSTEXPR testspr::reduce_iterator<Iterator, std::bidirectional_iterator_tag>
	reduce_bidirectional(Iterator it) {
		return testspr::reduce_iterator<Iterator, std::bidirectional_iterator_tag>(it);
	}
	template<typename Iterator>
	inline SPROUT_CONSTEXPR testspr::reduce_iterator<Iterator, std::random_access_iterator_tag>
	reduce_random_access(Iterator it) {
		return testspr::reduce_iterator<Iterator, std::random_access_iterator_tag>(it);
	}

	//
	// swap
	//
	template<typename Category, typename Iterator>
	inline SPROUT_CXX14_CONSTEXPR void
	swap(testspr::reduce_iterator<Iterator, Category>& lhs, testspr::reduce_iterator<Iterator, Category>& rhs)
	SPROUT_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
	{
		lhs.swap(rhs);
	}

	//
	// iterator_distance
	//
	template<typename Category, typename Iterator>
	inline SPROUT_CONSTEXPR typename std::iterator_traits<testspr::reduce_iterator<Iterator, Category> >::difference_type
	iterator_distance(testspr::reduce_iterator<Iterator, Category> first, testspr::reduce_iterator<Iterator, Category> last) {
		return sprout::distance(first.base(), last.base());
	}

	//
	// iterator_next
	//
	template<typename Category, typename Iterator>
	inline SPROUT_CONSTEXPR testspr::reduce_iterator<Iterator, Category>
	iterator_next(testspr::reduce_iterator<Iterator, Category> const& it) {
		return it.next();
	}
	template<typename Category, typename Iterator>
	inline SPROUT_CONSTEXPR testspr::reduce_iterator<Iterator, Category>
	iterator_next(
		testspr::reduce_iterator<Iterator, Category> const& it,
		typename testspr::reduce_iterator<Iterator, Category>::difference_type n
		)
	{
		return testspr::reduce_iterator<Iterator, Category>(sprout::next(it.base(), n));
	}

	//
	// iterator_prev
	//
	template<typename Category, typename Iterator>
	inline SPROUT_CONSTEXPR testspr::reduce_iterator<Iterator, Category>
	iterator_prev(testspr::reduce_iterator<Iterator, Category> const& it) {
		return it.prev();
	}
	template<typename Category, typename Iterator>
	inline SPROUT_CONSTEXPR testspr::reduce_iterator<Iterator, Category>
	iterator_prev(
		testspr::reduce_iterator<Iterator, Category> const& it,
		typename testspr::reduce_iterator<Iterator, Category>::difference_type n
		)
	{
		return testspr::reduce_iterator<Iterator, Category>(sprout::next(it.base(), n));
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_ITERATOR_HPP
