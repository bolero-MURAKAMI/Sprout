/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ITERATOR_STEP_ITERATOR_HPP
#define SPROUT_ITERATOR_STEP_ITERATOR_HPP

#include <utility>
#include <sprout/config.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/iterator/prev.hpp>
#include <sprout/iterator/distance.hpp>
#include <sprout/iterator/detail/iterator_base.hpp>
#include <sprout/utility/swap.hpp>
#include HDR_ALGORITHM_MIN_MAX_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	//
	// step_iterator
	//
	template<typename Iterator>
	class step_iterator
		: public sprout::detail::iterator_base<Iterator>::type
	{
	private:
		typedef typename sprout::detail::iterator_base<Iterator>::type base_type;
	public:
		typedef Iterator iterator_type;
		typedef typename base_type::iterator_category iterator_category;
		typedef typename base_type::value_type value_type;
		typedef typename base_type::difference_type difference_type;
		typedef typename base_type::pointer pointer;
		typedef typename base_type::reference reference;
	private:
		static SPROUT_CONSTEXPR iterator_type get_back(iterator_type it, difference_type wid, iterator_type last) {
			return sprout::next(it, (sprout::distance(it, last) - 1) / wid * wid);
		}
		static SPROUT_CONSTEXPR difference_type next_distance(step_iterator const& it, difference_type n) {
			return n >= 0 ? NS_SSCRISK_CEL_OR_SPROUT::min(sprout::distance(it.current, it.back), n * it.wid)
				: it.is_last ? 0
				: NS_SSCRISK_CEL_OR_SPROUT::max(-sprout::distance(it.current, it.back), n * it.wid)
				;
		}
	protected:
		iterator_type current;
		iterator_type last;
		difference_type wid;
	private:
		iterator_type back;
		bool is_last;
	private:
		SPROUT_CONSTEXPR step_iterator(step_iterator const& other, difference_type n)
			: current(sprout::next(other.current, next_distance(other, n))), last(other.last), wid(other.wid)
			, back(other.back), is_last(next_distance(other, n) == 0)
		{}
	public:
		SPROUT_CONSTEXPR step_iterator()
			: current(), last(), wid(1)
			, back(), is_last()
		{}
		SPROUT_CONSTEXPR step_iterator(step_iterator const& other)
			: current(other.current), last(other.last), wid(other.wid)
			, back(other.back), is_last(other.is_last)
		{}
		explicit SPROUT_CONSTEXPR step_iterator(iterator_type it, difference_type wid = 1, iterator_type last = iterator_type())
			: current(it), last(last), wid(wid)
			, back(get_back(it, wid, last)), is_last(it == last)
		{}
		template<typename U>
		SPROUT_CONSTEXPR step_iterator(step_iterator<U> const& it)
			: current(it.base()), last(it.end()), wid(it.width())
			, back(get_back(it.base(), it.width(), it.end())), is_last(it.is_end())
		{}
		template<typename U>
		SPROUT_CXX14_CONSTEXPR step_iterator& operator=(step_iterator<U> const& it) {
			step_iterator temp(it);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR iterator_type base() const {
			return current;
		}
		SPROUT_CONSTEXPR difference_type width() const {
			return wid;
		}
		SPROUT_CONSTEXPR iterator_type end() const {
			return last;
		}
		SPROUT_CONSTEXPR bool is_end() const {
			return is_last;
		}
		SPROUT_CONSTEXPR reference operator*() const {
			return *current;
		}
		SPROUT_CONSTEXPR pointer operator->() const {
			return &*current;
		}
		SPROUT_CXX14_CONSTEXPR step_iterator& operator++() {
			if (current == back) {
				is_last = true;
			}
			current += next_distance(*this, 1);
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR step_iterator operator++(int) {
			step_iterator result(*this);
			if (current == back) {
				is_last = true;
			}
			current += next_distance(*this, 1);
			return result;
		}
		SPROUT_CXX14_CONSTEXPR step_iterator& operator--() {
			current += next_distance(*this, -1);
			if (current != back) {
				is_last = false;
			}
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR step_iterator operator--(int) {
			step_iterator temp(*this);
			current += next_distance(*this, -1);
			if (current != back) {
				is_last = false;
			}
			return temp;
		}
		SPROUT_CONSTEXPR step_iterator operator+(difference_type n) const {
			return step_iterator(*this, n);
		}
		SPROUT_CONSTEXPR step_iterator operator-(difference_type n) const {
			return step_iterator(*this, -n);
		}
		SPROUT_CXX14_CONSTEXPR step_iterator& operator+=(difference_type n) {
			step_iterator temp(*this, n);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR step_iterator& operator-=(difference_type n) {
			step_iterator temp(*this, -n);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR reference operator[](difference_type n) const {
			return *(current + n * wid);
		}
		SPROUT_CONSTEXPR step_iterator next() const {
			return step_iterator(*this, 1);
		}
		SPROUT_CONSTEXPR step_iterator prev() const {
			return step_iterator(*this, -1);
		}
		SPROUT_CXX14_CONSTEXPR void swap(step_iterator& other)
		SPROUT_NOEXCEPT_IF(
			SPROUT_NOEXCEPT_EXPR(swap(current, other.current))
			&& SPROUT_NOEXCEPT_EXPR(swap(last, other.last))
			&& SPROUT_NOEXCEPT_EXPR(swap(wid, other.wid))
			&& SPROUT_NOEXCEPT_EXPR(swap(back, other.back))
			&& SPROUT_NOEXCEPT_EXPR(swap(wid, other.wid))
			&& SPROUT_NOEXCEPT_EXPR(swap(is_last, other.is_last))
			)
		{
			swap(current, other.current);
			swap(last, other.last);
			swap(wid, other.wid);
			swap(back, other.back);
			swap(is_last, other.is_last);
		}
	};

	template<typename Iterator1, typename Iterator2>
	inline SPROUT_CONSTEXPR bool
	operator==(sprout::step_iterator<Iterator1> const& lhs, sprout::step_iterator<Iterator2> const& rhs) {
		return lhs.base() == rhs.base() && lhs.is_end() == rhs.is_end();
	}
	template<typename Iterator1, typename Iterator2>
	inline SPROUT_CONSTEXPR bool
	operator!=(sprout::step_iterator<Iterator1> const& lhs, sprout::step_iterator<Iterator2> const& rhs) {
		return !(lhs == rhs);
	}
	template<typename Iterator1, typename Iterator2>
	inline SPROUT_CONSTEXPR bool
	operator<(sprout::step_iterator<Iterator1> const& lhs, sprout::step_iterator<Iterator2> const& rhs) {
		return lhs.base() < rhs.base() || (lhs.base() == rhs.base() && !lhs.is_end() && rhs.is_end());
	}
	template<typename Iterator1, typename Iterator2>
	inline SPROUT_CONSTEXPR bool
	operator>(sprout::step_iterator<Iterator1> const& lhs, sprout::step_iterator<Iterator2> const& rhs) {
		return rhs < lhs;
	}
	template<typename Iterator1, typename Iterator2>
	inline SPROUT_CONSTEXPR bool
	operator<=(sprout::step_iterator<Iterator1> const& lhs, sprout::step_iterator<Iterator2> const& rhs) {
		return !(rhs < lhs);
	}
	template<typename Iterator1, typename Iterator2>
	inline SPROUT_CONSTEXPR bool
	operator>=(sprout::step_iterator<Iterator1> const& lhs, sprout::step_iterator<Iterator2> const& rhs) {
		return !(lhs < rhs);
	}
	template<typename Iterator1, typename Iterator2>
	inline SPROUT_CONSTEXPR decltype(std::declval<Iterator1>() - std::declval<Iterator2>())
	operator-(sprout::step_iterator<Iterator1> const& lhs, sprout::step_iterator<Iterator2> const& rhs) {
		return (lhs.base() - rhs.base()) / lhs.width() + (lhs.is_end() ? 1 : 0) - (rhs.is_end() ? 1 : 0);
	}
	template<typename Iterator>
	inline SPROUT_CONSTEXPR sprout::step_iterator<Iterator>
	operator+(
		typename sprout::step_iterator<Iterator>::difference_type n,
		sprout::step_iterator<Iterator> const& it
		)
	{
		return it + n;
	}

	//
	// make_step_iterator
	//
	template<typename Iterator>
	inline SPROUT_CONSTEXPR sprout::step_iterator<Iterator>
	make_step_iterator(Iterator it, typename sprout::step_iterator<Iterator>::difference_type wid = 1) {
		return sprout::step_iterator<Iterator>(it, wid);
	}

	//
	// swap
	//
	template<typename Iterator>
	inline SPROUT_CXX14_CONSTEXPR void
	swap(sprout::step_iterator<Iterator>& lhs, sprout::step_iterator<Iterator>& rhs)
	SPROUT_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
	{
		lhs.swap(rhs);
	}

	//
	// iterator_next
	//
	template<typename Iterator>
	inline SPROUT_CONSTEXPR sprout::step_iterator<Iterator>
	iterator_next(sprout::step_iterator<Iterator> const& it) {
		return it.next();
	}

	//
	// iterator_prev
	//
	template<typename Iterator>
	inline SPROUT_CONSTEXPR sprout::step_iterator<Iterator>
	iterator_prev(sprout::step_iterator<Iterator> const& it) {
		return it.prev();
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_STEP_ITERATOR_HPP
