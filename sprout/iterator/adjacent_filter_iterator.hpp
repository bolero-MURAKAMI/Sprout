/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ITERATOR_ADJACENT_FILTER_ITERATOR_HPP
#define SPROUT_ITERATOR_ADJACENT_FILTER_ITERATOR_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/iterator/type_traits/common.hpp>
#include <sprout/algorithm/adjacent_find.hpp>
#include <sprout/utility/swap.hpp>

namespace sprout {
	//
	// adjacent_filter_iterator
	//
	template<typename Predicate, typename Iterator>
	class adjacent_filter_iterator
		: public std::iterator<
			typename sprout::min_iterator_category<
				typename std::iterator_traits<Iterator>::iterator_category,
				std::forward_iterator_tag
			>::type,
			typename std::iterator_traits<Iterator>::value_type,
			typename std::iterator_traits<Iterator>::difference_type,
			typename std::iterator_traits<Iterator>::pointer,
			typename std::iterator_traits<Iterator>::reference
		>
	{
	public:
		typedef Predicate predicate_type;
		typedef Iterator iterator_type;
		typedef typename sprout::min_iterator_category<
			typename std::iterator_traits<Iterator>::iterator_category,
			std::forward_iterator_tag
		>::type iterator_category;
		typedef typename std::iterator_traits<Iterator>::value_type value_type;
		typedef typename std::iterator_traits<Iterator>::difference_type difference_type;
		typedef typename std::iterator_traits<Iterator>::pointer pointer;
		typedef typename std::iterator_traits<Iterator>::reference reference;
	private:
		struct private_construct_t {};
	private:
		static SPROUT_CONSTEXPR iterator_type find_next(iterator_type first, iterator_type last, Predicate pred) {
			return sprout::adjacent_find(first, last, pred);
		}
		static SPROUT_CONSTEXPR iterator_type checked_next(iterator_type found, iterator_type last) {
			return found == last ? last
				: sprout::next(found)
				;
		}
	protected:
		iterator_type current;
		iterator_type last;
		Predicate pred;
	private:
		void satisfy_predicate() {
			current = sprout::adjacent_find(current, last, pred);
		}
		SPROUT_CONSTEXPR adjacent_filter_iterator(Predicate pred, iterator_type it, iterator_type last, private_construct_t)
			: current(it)
			, last(last)
			, pred(pred)
		{}
	public:
		SPROUT_CONSTEXPR adjacent_filter_iterator()
			: current(), last(), pred()
		{}
		adjacent_filter_iterator(adjacent_filter_iterator const&) = default;
		SPROUT_CONSTEXPR adjacent_filter_iterator(Predicate pred, iterator_type it, iterator_type last = iterator_type())
			: current(find_next(it, last, pred))
			, last(last)
			, pred(pred)
		{}
		template<typename U>
		SPROUT_CONSTEXPR adjacent_filter_iterator(adjacent_filter_iterator<Predicate, U> const& it)
			: current(it.current)
			, last(it.last)
			, pred(it.pred)
		{}
		template<typename U>
		SPROUT_CXX14_CONSTEXPR adjacent_filter_iterator& operator=(adjacent_filter_iterator<Predicate, U> const& it) {
			adjacent_filter_iterator temp(it);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR iterator_type base() const {
			return current;
		}
		SPROUT_CONSTEXPR iterator_type end() const {
			return last;
		}
		SPROUT_CONSTEXPR Predicate predicate() const {
			return pred;
		}
		SPROUT_CONSTEXPR reference operator*() const {
			return *current;
		}
		SPROUT_CONSTEXPR pointer operator->() const {
			return &*current;
		}

		SPROUT_CXX14_CONSTEXPR adjacent_filter_iterator& operator++() {
			satisfy_predicate();
			if (current != last) {
				++current;
			}
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR adjacent_filter_iterator operator++(int) {
			adjacent_filter_iterator result(*this);
			satisfy_predicate();
			if (current != last) {
				++current;
			}
			return result;
		}
		SPROUT_CONSTEXPR adjacent_filter_iterator next() const {
			return adjacent_filter_iterator(pred, checked_next(find_next(current, last, pred), last), last, private_construct_t());
		}
		SPROUT_CXX14_CONSTEXPR void swap(adjacent_filter_iterator& other)
		SPROUT_NOEXCEPT_EXPR(
			SPROUT_NOEXCEPT_EXPR(sprout::swap(current, other.current))
			&& SPROUT_NOEXCEPT_EXPR(sprout::swap(last, other.last))
			&& SPROUT_NOEXCEPT_EXPR(sprout::swap(pred, other.pred))
			)
		{
			sprout::swap(current, other.current);
			sprout::swap(last, other.last);
			sprout::swap(pred, other.pred);
		}
	};

	template<typename Predicate, typename Iterator1, typename Iterator2>
	inline SPROUT_CONSTEXPR bool operator==(
		sprout::adjacent_filter_iterator<Predicate, Iterator1> const& lhs,
		sprout::adjacent_filter_iterator<Predicate, Iterator2> const& rhs
		)
	{
		return lhs.base() == rhs.base();
	}
	template<typename Predicate, typename Iterator1, typename Iterator2>
	inline SPROUT_CONSTEXPR bool operator!=(
		sprout::adjacent_filter_iterator<Predicate, Iterator1> const& lhs,
		sprout::adjacent_filter_iterator<Predicate, Iterator2> const& rhs
		)
	{
		return !(lhs == rhs);
	}

	//
	// make_adjacent_filter_iterator
	//
	template<typename Predicate, typename Iterator>
	inline SPROUT_CONSTEXPR sprout::adjacent_filter_iterator<Predicate, Iterator>
	make_adjacent_filter_iterator(Predicate pred, Iterator it, Iterator last = Iterator()) {
		return sprout::adjacent_filter_iterator<Predicate, Iterator>(pred, it, last);
	}

	//
	// swap
	//
	template<typename Predicate, typename Iterator>
	inline SPROUT_CXX14_CONSTEXPR void
	swap(sprout::adjacent_filter_iterator<Predicate, Iterator>& lhs, sprout::adjacent_filter_iterator<Predicate, Iterator>& rhs)
	SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs)))
	{
		lhs.swap(rhs);
	}

	//
	// iterator_next
	//
	template<typename Predicate, typename Iterator>
	inline SPROUT_CONSTEXPR sprout::adjacent_filter_iterator<Predicate, Iterator>
	iterator_next(sprout::adjacent_filter_iterator<Predicate, Iterator> const& it) {
		return it.next();
	}
}	// namespace sprout

#endif	// SPROUT_ITERATOR_ADJACENT_FILTER_ITERATOR_HPP
