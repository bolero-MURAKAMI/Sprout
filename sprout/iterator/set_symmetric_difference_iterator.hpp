/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ITERATOR_SET_SYMMETRIC_DIFFERENCE_ITERATOR_HPP
#define SPROUT_ITERATOR_SET_SYMMETRIC_DIFFERENCE_ITERATOR_HPP

#include <iterator>
#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/iterator.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/iterator/type_traits/common.hpp>
#include <sprout/functional/less.hpp>
#include <sprout/utility/swap.hpp>
#include <sprout/utility/pair/pair.hpp>
#include <sprout/algorithm/find_symmetric_difference.hpp>
#include <sprout/algorithm/next_symmetric_difference.hpp>

namespace sprout {
	namespace detail {
		template<
			typename LIterator, typename RIterator,
			typename Compare
		>
		class set_symmetric_difference_iterator_impl {
		protected:
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
			static SPROUT_CONSTEXPR bool check_in_left(
				iterator_type it1, iterator_type las1,
				iterator2_type it2, iterator2_type las2,
				Compare comp
				)
			{
				return it1 != las1 ? (it2 != las2 ? comp(*it1, *it2) : true)
					: !(it2 != las2)
					;
			}
		protected:
			pair_type current;
			iterator_type las1;
			iterator2_type las2;
			Compare comp;
		protected:
			bool in_left;
		protected:
			SPROUT_CONSTEXPR set_symmetric_difference_iterator_impl()
				: current(), las1(), las2(), comp(), in_left(true)
			{}
			set_symmetric_difference_iterator_impl(set_symmetric_difference_iterator_impl const&) = default;
			SPROUT_CONSTEXPR set_symmetric_difference_iterator_impl(
				pair_type const& current,
				iterator_type las1, iterator2_type las2,
				Compare comp
				)
				: current(current)
				, las1(las1), las2(las2)
				, comp(comp)
				, in_left(check_in_left(current.first, las1, current.second, las2, comp))
			{}
			SPROUT_CONSTEXPR set_symmetric_difference_iterator_impl(
				pair_type const& current,
				iterator_type las1, iterator2_type las2,
				Compare comp,
				bool in_left
				)
				: current(current)
				, las1(las1), las2(las2)
				, comp(comp)
				, in_left(in_left)
			{}
		};
	}	// namespace detail

	//
	// set_symmetric_difference_iterator
	//
	template<
		typename LIterator, typename RIterator,
		typename Compare = sprout::less<>
	>
	class set_symmetric_difference_iterator
		: public sprout::iterator<
			typename sprout::min_iterator_category<
				typename sprout::common_iterator_category<LIterator, RIterator>::type,
				std::forward_iterator_tag
			>::type,
			typename sprout::common_iterator_value_type<LIterator, RIterator>::type,
			typename sprout::common_iterator_difference_type<LIterator, RIterator>::type,
			typename sprout::common_iterator_pointer<LIterator, RIterator>::type,
			typename sprout::common_iterator_reference<LIterator, RIterator>::type
		>
		, private sprout::detail::set_symmetric_difference_iterator_impl<LIterator, RIterator, Compare>
	{
	private:
		typedef sprout::detail::set_symmetric_difference_iterator_impl<LIterator, RIterator, Compare> impl_type;
	public:
		typedef typename impl_type::iterator_type iterator_type;
		typedef typename impl_type::iterator2_type iterator2_type;
		typedef typename impl_type::compare_type compare_type;
		typedef typename impl_type::iterator_category iterator_category;
		typedef typename impl_type::value_type value_type;
		typedef typename impl_type::difference_type difference_type;
		typedef typename impl_type::pointer pointer;
		typedef typename impl_type::reference reference;
	protected:
		typedef typename impl_type::pair_type pair_type;
	private:
		using impl_type::check_in_left;
	protected:
		using impl_type::current;
		using impl_type::las1;
		using impl_type::las2;
		using impl_type::comp;
	private:
		using impl_type::in_left;
	private:
		SPROUT_CONSTEXPR set_symmetric_difference_iterator(set_symmetric_difference_iterator const& other, pair_type const& next)
			: impl_type(next, other.las1, other.las2, other.comp)
		{}
	public:
		SPROUT_CONSTEXPR set_symmetric_difference_iterator()
			: impl_type()
		{}
		set_symmetric_difference_iterator(set_symmetric_difference_iterator const&) = default;
		SPROUT_CONSTEXPR set_symmetric_difference_iterator(
			iterator_type it1, iterator_type las1,
			iterator2_type it2, iterator2_type las2,
			Compare comp = Compare()
			)
			: impl_type(sprout::find_symmetric_difference(it1, las1, it2, las2, comp), las1, las2, comp)
		{}
		template<typename U, typename V, typename W>
		SPROUT_CONSTEXPR set_symmetric_difference_iterator(set_symmetric_difference_iterator<U, V, W> const& it)
			: impl_type(pair_type(it.base(), it.base2()), it.last1(), it.last2(), it.compare(), it.is_in_left())
		{}
		template<typename U, typename V, typename W>
		SPROUT_CXX14_CONSTEXPR set_symmetric_difference_iterator& operator=(set_symmetric_difference_iterator<U, V, W> const& it) {
			set_symmetric_difference_iterator temp(it);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR iterator_type base() const {
			return current.first;
		}
		SPROUT_CONSTEXPR iterator_type last1() const {
			return las1;
		}
		SPROUT_CONSTEXPR iterator2_type base2() const {
			return current.second;
		}
		SPROUT_CONSTEXPR iterator2_type last2() const {
			return las2;
		}
		SPROUT_CONSTEXPR Compare compare() const {
			return comp;
		}
		SPROUT_CONSTEXPR bool is_in_left() const {
			return in_left;
		}
		SPROUT_CONSTEXPR reference operator*() const {
			return is_in_left() ? *current.first : *current.second;
		}
		SPROUT_CONSTEXPR pointer operator->() const {
			return &*(*this);
		}
		SPROUT_CXX14_CONSTEXPR set_symmetric_difference_iterator& operator++() {
			current = sprout::next_symmetric_difference(current.first, las1, current.second, las2, comp);
			in_left = check_in_left(current.first, las1, current.second, las2, comp);
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR set_symmetric_difference_iterator operator++(int) {
			set_symmetric_difference_iterator result(*this);
			current = sprout::next_symmetric_difference(current.first, las1, current.second, las2, comp);
			in_left = check_in_left(current.first, las1, current.second, las2, comp);
			return result;
		}
		SPROUT_CONSTEXPR set_symmetric_difference_iterator next() const {
			return set_symmetric_difference_iterator(
				*this,
				sprout::next_symmetric_difference(current.first, las1, current.second, las2, comp)
				);
		}
		SPROUT_CXX14_CONSTEXPR void swap(set_symmetric_difference_iterator& other)
		SPROUT_NOEXCEPT_IF(
			SPROUT_NOEXCEPT_EXPR(sprout::swap(current, other.current))
			&& SPROUT_NOEXCEPT_EXPR(sprout::swap(las1, other.las1))
			&& SPROUT_NOEXCEPT_EXPR(sprout::swap(las2, other.las2))
			&& SPROUT_NOEXCEPT_EXPR(sprout::swap(comp, other.comp))
			)
		{
			sprout::swap(current, other.current);
			sprout::swap(las1, other.las1);
			sprout::swap(las2, other.las2);
			sprout::swap(comp, other.comp);
			sprout::swap(in_left, other.in_left);
		}
	};

	template<
		typename LIterator1, typename RIterator1, typename Compare1,
		typename LIterator2, typename RIterator2, typename Compare2
	>
	inline SPROUT_CONSTEXPR bool operator==(
		sprout::set_symmetric_difference_iterator<LIterator1, RIterator1, Compare1> const& lhs,
		sprout::set_symmetric_difference_iterator<LIterator2, RIterator2, Compare2> const& rhs
		)
	{
		return lhs.base() == rhs.base() && lhs.base2() == rhs.base2();
	}
	template<
		typename LIterator1, typename RIterator1, typename Compare1,
		typename LIterator2, typename RIterator2, typename Compare2
	>
	inline SPROUT_CONSTEXPR bool operator!=(
		sprout::set_symmetric_difference_iterator<LIterator1, RIterator1, Compare1> const& lhs,
		sprout::set_symmetric_difference_iterator<LIterator2, RIterator2, Compare2> const& rhs
		)
	{
		return !(lhs == rhs);
	}

	//
	// make_set_symmetric_difference_iterator
	//
	template<typename LIterator, typename RIterator, typename Compare>
	inline SPROUT_CONSTEXPR sprout::set_symmetric_difference_iterator<LIterator, RIterator, Compare>
	make_set_symmetric_difference_iterator(LIterator it1, LIterator las1, RIterator it2, RIterator las2, Compare comp) {
		return sprout::set_symmetric_difference_iterator<LIterator, RIterator, Compare>(it1, las1, it2, las2, comp);
	}
	template<typename LIterator, typename RIterator>
	inline SPROUT_CONSTEXPR sprout::set_symmetric_difference_iterator<LIterator, RIterator>
	make_set_symmetric_difference_iterator(LIterator it1, LIterator las1, RIterator it2, RIterator las2) {
		return sprout::set_symmetric_difference_iterator<LIterator, RIterator>(it1, las1, it2, las2);
	}

	//
	// swap
	//
	template<typename LIterator, typename RIterator, typename Compare>
	inline SPROUT_CXX14_CONSTEXPR void
	swap(
		sprout::set_symmetric_difference_iterator<LIterator, RIterator, Compare>& lhs,
		sprout::set_symmetric_difference_iterator<LIterator, RIterator, Compare>& rhs
		)
	SPROUT_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
	{
		lhs.swap(rhs);
	}

	//
	// iterator_next
	//
	template<typename LIterator, typename RIterator, typename Compare>
	inline SPROUT_CONSTEXPR sprout::set_symmetric_difference_iterator<LIterator, RIterator, Compare>
	iterator_next(sprout::set_symmetric_difference_iterator<LIterator, RIterator, Compare> const& it) {
		return it.next();
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_SET_SYMMETRIC_DIFFERENCE_ITERATOR_HPP
