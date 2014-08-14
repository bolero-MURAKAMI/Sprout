/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ITERATOR_SET_INTERSECTION_ITERATOR_HPP
#define SPROUT_ITERATOR_SET_INTERSECTION_ITERATOR_HPP

#include <iterator>
#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/iterator/type_traits/common.hpp>
#include <sprout/functional/less.hpp>
#include <sprout/utility/swap.hpp>
#include <sprout/utility/pair/pair.hpp>
#include <sprout/algorithm/find_intersection.hpp>
#include <sprout/algorithm/next_intersection.hpp>

namespace sprout {
	//
	// set_intersection_iterator
	//
	template<
		typename LIterator, typename RIterator,
		typename Compare = sprout::less<>
	>
	class set_intersection_iterator
		: public std::iterator<
			typename sprout::min_iterator_category<
				typename sprout::common_iterator_category<LIterator, RIterator>::type,
				std::forward_iterator_tag
			>::type,
			typename sprout::common_iterator_value_type<LIterator, RIterator>::type,
			typename sprout::common_iterator_difference_type<LIterator, RIterator>::type,
			typename sprout::common_iterator_pointer<LIterator, RIterator>::type,
			typename sprout::common_iterator_reference<LIterator, RIterator>::type
		>
	{
	public:
		typedef LIterator iterator_type;
		typedef RIterator iterator2_type;
		typedef Compare compare_type;
		typedef typename sprout::min_iterator_category<
			typename sprout::common_iterator_category<LIterator, RIterator>::type,
			std::forward_iterator_tag
		>::type iterator_category;
		typedef typename sprout::common_iterator_value_type<LIterator, RIterator>::type value_type;
		typedef typename sprout::common_iterator_difference_type<LIterator, RIterator>::type difference_type;
		typedef typename sprout::common_iterator_pointer<LIterator, RIterator>::type pointer;
		typedef typename sprout::common_iterator_reference<LIterator, RIterator>::type reference;
	protected:
		typedef sprout::pair<iterator_type, iterator2_type> pair_type;
	protected:
		pair_type current;
		iterator_type lst1;
		iterator2_type lst2;
		Compare comp;
	private:
		SPROUT_CONSTEXPR set_intersection_iterator(set_intersection_iterator const& other, pair_type const& next)
			: current(next)
			, lst1(other.lst1), lst2(other.lst2)
			, comp(other.comp)
		{}
	public:
		SPROUT_CONSTEXPR set_intersection_iterator()
			: current(), lst1(), lst2(), comp()
		{}
		set_intersection_iterator(set_intersection_iterator const&) = default;
		SPROUT_CONSTEXPR set_intersection_iterator(
			iterator_type it1, iterator_type lst1,
			iterator2_type it2, iterator2_type lst2,
			Compare comp = Compare()
			)
			: current(sprout::find_intersection(it1, lst1, it2, lst2, comp))
			, lst1(lst1), lst2(lst2)
			, comp(comp)
		{}
		template<typename U, typename V, typename W>
		SPROUT_CONSTEXPR set_intersection_iterator(set_intersection_iterator<U, V, W> const& it)
			: current(it.base(), it.base2())
			, lst1(it.last1()), lst2(it.last2())
			, comp(it.compare())
		{}
		template<typename U, typename V, typename W>
		SPROUT_CXX14_CONSTEXPR set_intersection_iterator& operator=(set_intersection_iterator<U, V, W> const& it) {
			set_intersection_iterator temp(it);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR iterator_type base() const {
			return current.first;
		}
		SPROUT_CONSTEXPR iterator_type last1() const {
			return lst1;
		}
		SPROUT_CONSTEXPR iterator2_type base2() const {
			return current.second;
		}
		SPROUT_CONSTEXPR iterator2_type last2() const {
			return lst2;
		}
		SPROUT_CONSTEXPR Compare compare() const {
			return comp;
		}
		SPROUT_CONSTEXPR bool is_in_left() const {
			return true;
		}
		SPROUT_CONSTEXPR reference operator*() const {
			return *current.first;
		}
		SPROUT_CONSTEXPR pointer operator->() const {
			return &*(*this);
		}
		SPROUT_CXX14_CONSTEXPR set_intersection_iterator& operator++() {
			current = sprout::next_intersection(current.first, lst1, current.second, lst2, comp);
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR set_intersection_iterator operator++(int) {
			set_intersection_iterator result(*this);
			current = sprout::next_intersection(current.first, lst1, current.second, lst2, comp);
			return result;
		}
		SPROUT_CONSTEXPR set_intersection_iterator next() const {
			return set_intersection_iterator(
				*this,
				sprout::next_intersection(current.first, lst1, current.second, lst2, comp)
				);
		}
		SPROUT_CXX14_CONSTEXPR void swap(set_intersection_iterator& other)
		SPROUT_NOEXCEPT_IF(
			SPROUT_NOEXCEPT_EXPR(sprout::swap(current, other.current))
			&& SPROUT_NOEXCEPT_EXPR(sprout::swap(lst1, other.lst1))
			&& SPROUT_NOEXCEPT_EXPR(sprout::swap(lst2, other.lst2))
			&& SPROUT_NOEXCEPT_EXPR(sprout::swap(comp, other.comp))
			)
		{
			sprout::swap(current, other.current);
			sprout::swap(lst1, other.lst1);
			sprout::swap(lst2, other.lst2);
			sprout::swap(comp, other.comp);
		}
	};

	template<
		typename LIterator1, typename RIterator1, typename Compare1,
		typename LIterator2, typename RIterator2, typename Compare2
	>
	inline SPROUT_CONSTEXPR bool operator==(
		sprout::set_intersection_iterator<LIterator1, RIterator1, Compare1> const& lhs,
		sprout::set_intersection_iterator<LIterator2, RIterator2, Compare2> const& rhs
		)
	{
		return lhs.base() == rhs.base() && lhs.base2() == rhs.base2();
	}
	template<
		typename LIterator1, typename RIterator1, typename Compare1,
		typename LIterator2, typename RIterator2, typename Compare2
	>
	inline SPROUT_CONSTEXPR bool operator!=(
		sprout::set_intersection_iterator<LIterator1, RIterator1, Compare1> const& lhs,
		sprout::set_intersection_iterator<LIterator2, RIterator2, Compare2> const& rhs
		)
	{
		return !(lhs == rhs);
	}

	//
	// make_set_intersection_iterator
	//
	template<typename LIterator, typename RIterator, typename Compare>
	inline SPROUT_CONSTEXPR sprout::set_intersection_iterator<LIterator, RIterator, Compare>
	make_set_intersection_iterator(LIterator it1, LIterator lst1, RIterator it2, RIterator lst2, Compare comp) {
		return sprout::set_intersection_iterator<LIterator, RIterator, Compare>(it1, lst1, it2, lst2, comp);
	}
	template<typename LIterator, typename RIterator>
	inline SPROUT_CONSTEXPR sprout::set_intersection_iterator<LIterator, RIterator>
	make_set_intersection_iterator(LIterator it1, LIterator lst1, RIterator it2, RIterator lst2) {
		return sprout::set_intersection_iterator<LIterator, RIterator>(it1, lst1, it2, lst2);
	}

	//
	// swap
	//
	template<typename LIterator, typename RIterator, typename Compare>
	inline SPROUT_CXX14_CONSTEXPR void
	swap(
		sprout::set_intersection_iterator<LIterator, RIterator, Compare>& lhs,
		sprout::set_intersection_iterator<LIterator, RIterator, Compare>& rhs
		)
	SPROUT_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
	{
		lhs.swap(rhs);
	}

	//
	// iterator_next
	//
	template<typename LIterator, typename RIterator, typename Compare>
	inline SPROUT_CONSTEXPR sprout::set_intersection_iterator<LIterator, RIterator, Compare>
	iterator_next(sprout::set_intersection_iterator<LIterator, RIterator, Compare> const& it) {
		return it.next();
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_SET_INTERSECTION_ITERATOR_HPP
