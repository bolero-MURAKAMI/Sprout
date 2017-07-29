/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ITERATOR_NEXT_ITERATOR_HPP
#define SPROUT_ITERATOR_NEXT_ITERATOR_HPP

#include <iterator>
#include <utility>
#include <sprout/config.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/iterator/detail/iterator_base.hpp>
#include <sprout/utility/value_holder/value_holder.hpp>
#include <sprout/utility/swap.hpp>

namespace sprout {
	//
	// next_iterator
	//
	template<typename Iterator>
	struct next_iterator
		: public sprout::detail::iterator_base<
			Iterator,
			std::forward_iterator_tag
		>::type
	{
	private:
		typedef typename sprout::detail::iterator_base<
			Iterator,
			std::forward_iterator_tag
		>::type base_type;
	public:
		typedef Iterator iterator_type;
		typedef typename base_type::iterator_category iterator_category;
		typedef typename base_type::value_type value_type;
		typedef typename base_type::difference_type difference_type;
		typedef typename base_type::pointer pointer;
		typedef typename base_type::reference reference;
	private:
		typedef sprout::value_holder<reference> holder_type;
	private:
		holder_type holder_;
	protected:
		iterator_type current;
	public:
		SPROUT_CONSTEXPR next_iterator()
			: holder_(), current()
		{}
		SPROUT_CONSTEXPR next_iterator(next_iterator const& other)
			: holder_(other.holder_), current(other.current)
		{}
		SPROUT_CONSTEXPR next_iterator(iterator_type it)
			: holder_(*it), current(sprout::next(it))
		{}
		template<typename U>
		SPROUT_CONSTEXPR next_iterator(next_iterator<U> const& it)
			: holder_(*it), current(it.base())
		{}
		template<typename U>
		SPROUT_CXX14_CONSTEXPR next_iterator& operator=(next_iterator<U> const& it) {
			next_iterator temp(it);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR iterator_type base() const {
			return current;
		}
		SPROUT_CONSTEXPR reference operator*() const {
			return *holder_;
		}
		SPROUT_CONSTEXPR pointer operator->() const {
			return &*(*this);
		}
		SPROUT_CXX14_CONSTEXPR next_iterator& operator++() {
			holder_ = holder_type(*current);
			++current;
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR next_iterator operator++(int) {
			next_iterator result(*this);
			holder_ = holder_type(*current);
			++current;
			return result;
		}
		SPROUT_CONSTEXPR next_iterator next() const {
			return next_iterator(current);
		}
		SPROUT_CXX14_CONSTEXPR void swap(next_iterator& other)
		SPROUT_NOEXCEPT_IF(
			SPROUT_NOEXCEPT_EXPR(swap(holder_, other.holder_))
			&& SPROUT_NOEXCEPT_EXPR(swap(current, other.current))
			)
		{
			swap(holder_, other.holder_);
			swap(current, other.current);
		}
	};

	template<typename Iterator1, typename Iterator2>
	inline SPROUT_CONSTEXPR bool
	operator==(sprout::next_iterator<Iterator1> const& lhs, sprout::next_iterator<Iterator2> const& rhs) {
		return lhs.base() == rhs.base();
	}
	template<typename Iterator1, typename Iterator2>
	inline SPROUT_CONSTEXPR bool
	operator!=(sprout::next_iterator<Iterator1> const& lhs, sprout::next_iterator<Iterator2> const& rhs) {
		return !(lhs == rhs);
	}

	//
	// make_next_iterator
	//
	template<typename Iterator>
	inline SPROUT_CONSTEXPR sprout::next_iterator<Iterator>
	make_next_iterator(Iterator it) {
		return sprout::next_iterator<Iterator>(it);
	}

	//
	// swap
	//
	template<typename Iterator>
	inline SPROUT_CXX14_CONSTEXPR void
	swap(sprout::next_iterator<Iterator>& lhs, sprout::next_iterator<Iterator>& rhs)
	SPROUT_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
	{
		lhs.swap(rhs);
	}

	//
	// iterator_next
	//
	template<typename Iterator>
	inline SPROUT_CONSTEXPR sprout::next_iterator<Iterator>
	iterator_next(sprout::next_iterator<Iterator> const& it) {
		return it.next();
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_NEXT_ITERATOR_HPP
