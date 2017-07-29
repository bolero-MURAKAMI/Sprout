/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ITERATOR_FILTER_ITERATOR_HPP
#define SPROUT_ITERATOR_FILTER_ITERATOR_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/iterator/prev.hpp>
#include <sprout/iterator/type_traits/common.hpp>
#include <sprout/iterator/detail/iterator_base.hpp>
#include <sprout/algorithm/find_if.hpp>
#include <sprout/utility/swap.hpp>

namespace sprout {
	//
	// filter_iterator
	//
	template<typename Predicate, typename Iterator>
	class filter_iterator
		: public sprout::detail::iterator_base<
			Iterator,
			typename sprout::min_iterator_category<
				typename std::iterator_traits<Iterator>::iterator_category,
				std::bidirectional_iterator_tag
			>::type
		>::type
	{
	private:
		typedef typename sprout::detail::iterator_base<
			Iterator,
			typename sprout::min_iterator_category<
				typename std::iterator_traits<Iterator>::iterator_category,
				std::bidirectional_iterator_tag
			>::type
		>::type base_type;
	public:
		typedef Predicate predicate_type;
		typedef Iterator iterator_type;
		typedef typename base_type::iterator_category iterator_category;
		typedef typename base_type::value_type value_type;
		typedef typename base_type::difference_type difference_type;
		typedef typename base_type::pointer pointer;
		typedef typename base_type::reference reference;
	private:
		struct private_construct_t {};
	private:
		static SPROUT_CONSTEXPR iterator_type find_next(iterator_type first, iterator_type last, Predicate pred) {
			return sprout::find_if(first, last, pred);
		}
		static SPROUT_CONSTEXPR iterator_type find_prev(iterator_type first, Predicate pred) {
			return pred(*first) ? first
				: find_prev(sprout::prev(first), pred)
				;
		}
	protected:
		iterator_type current;
		iterator_type last;
		Predicate pred;
	private:
		SPROUT_CXX14_CONSTEXPR void satisfy_predicate() {
			current = sprout::find_if(current, last, pred);
		}
		SPROUT_CXX14_CONSTEXPR void satisfy_predicate_backward() {
			while (!pred(*current)) {
				--current;
			}
		}
		SPROUT_CONSTEXPR filter_iterator(Predicate pred, iterator_type it, iterator_type last, private_construct_t)
			: current(it)
			, last(last)
			, pred(pred)
		{}
	public:
		SPROUT_CONSTEXPR filter_iterator()
			: current(), last(), pred()
		{}
		filter_iterator(filter_iterator const&) = default;
		SPROUT_CONSTEXPR filter_iterator(Predicate pred, iterator_type it, iterator_type last = iterator_type())
			: current(find_next(it, last, pred))
			, last(last)
			, pred(pred)
		{}
		template<typename U>
		SPROUT_CONSTEXPR filter_iterator(filter_iterator<Predicate, U> const& it)
			: current(it.current)
			, last(it.last)
			, pred(it.pred)
		{}
		template<typename U>
		SPROUT_CXX14_CONSTEXPR filter_iterator& operator=(filter_iterator<Predicate, U> const& it) {
			filter_iterator temp(it);
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

		SPROUT_CXX14_CONSTEXPR filter_iterator& operator++() {
			++current;
			satisfy_predicate();
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR filter_iterator operator++(int) {
			filter_iterator result(*this);
			++current;
			satisfy_predicate();
			return result;
		}
		SPROUT_CXX14_CONSTEXPR filter_iterator& operator--() {
			--current;
			satisfy_predicate_backward();
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR filter_iterator operator--(int) {
			filter_iterator temp(*this);
			--current;
			satisfy_predicate_backward();
			return temp;
		}
		SPROUT_CONSTEXPR filter_iterator next() const {
			return filter_iterator(pred, find_next(sprout::next(current), last, pred), last, private_construct_t());
		}
		SPROUT_CONSTEXPR filter_iterator prev() const {
			return filter_iterator(pred, find_prev(sprout::prev(current), pred), last, private_construct_t());
		}
		SPROUT_CXX14_CONSTEXPR void swap(filter_iterator& other)
		SPROUT_NOEXCEPT_IF(
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
		sprout::filter_iterator<Predicate, Iterator1> const& lhs,
		sprout::filter_iterator<Predicate, Iterator2> const& rhs
		)
	{
		return lhs.base() == rhs.base();
	}
	template<typename Predicate, typename Iterator1, typename Iterator2>
	inline SPROUT_CONSTEXPR bool operator!=(
		sprout::filter_iterator<Predicate, Iterator1> const& lhs,
		sprout::filter_iterator<Predicate, Iterator2> const& rhs
		)
	{
		return !(lhs == rhs);
	}

	//
	// make_filter_iterator
	//
	template<typename Predicate, typename Iterator>
	inline SPROUT_CONSTEXPR sprout::filter_iterator<Predicate, Iterator>
	make_filter_iterator(Predicate pred, Iterator it, Iterator last = Iterator()) {
		return sprout::filter_iterator<Predicate, Iterator>(pred, it, last);
	}

	//
	// swap
	//
	template<typename Predicate, typename Iterator>
	inline SPROUT_CXX14_CONSTEXPR void
	swap(sprout::filter_iterator<Predicate, Iterator>& lhs, sprout::filter_iterator<Predicate, Iterator>& rhs)
	SPROUT_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
	{
		lhs.swap(rhs);
	}

	//
	// iterator_next
	//
	template<typename Predicate, typename Iterator>
	inline SPROUT_CONSTEXPR sprout::filter_iterator<Predicate, Iterator>
	iterator_next(sprout::filter_iterator<Predicate, Iterator> const& it) {
		return it.next();
	}

	//
	// iterator_prev
	//
	template<typename Predicate, typename Iterator>
	inline SPROUT_CONSTEXPR sprout::filter_iterator<Predicate, Iterator>
	iterator_prev(sprout::filter_iterator<Predicate, Iterator> const& it) {
		return it.prev();
	}
}	// namespace sprout

#endif	// SPROUT_ITERATOR_FILTER_ITERATOR_HPP
