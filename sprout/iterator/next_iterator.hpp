/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
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
#include <sprout/utility/value_holder/value_holder.hpp>
#include <sprout/utility/swap.hpp>

namespace sprout {
	//
	// next_iterator
	//
	template<typename Iterator>
	struct next_iterator
		: public std::iterator<
			std::forward_iterator_tag,
			typename std::iterator_traits<Iterator>::value_type,
			typename std::iterator_traits<Iterator>::difference_type,
			typename std::iterator_traits<Iterator>::pointer,
			typename std::iterator_traits<Iterator>::reference
		>
	{
	public:
		typedef Iterator iterator_type;
		typedef std::forward_iterator_tag iterator_category;
		typedef typename std::iterator_traits<iterator_type>::value_type value_type;
		typedef typename std::iterator_traits<iterator_type>::difference_type difference_type;
		typedef typename std::iterator_traits<iterator_type>::pointer pointer;
		typedef typename std::iterator_traits<iterator_type>::reference reference;
	private:
		typedef sprout::value_holder<reference> holder_type;
	private:
		holder_type holder_;
	protected:
		iterator_type current;
	public:
		next_iterator() = default;
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
		next_iterator& operator=(next_iterator<U> const& it) {
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
		next_iterator& operator++() {
			holder_ = holder_type(*current);
			++current;
			return *this;
		}
		next_iterator operator++(int) {
			next_iterator result(*this);
			holder_ = holder_type(*current);
			++current;
			return result;
		}
		SPROUT_CONSTEXPR next_iterator next() const {
			return next_iterator(current);
		}
		void swap(next_iterator& other)
		SPROUT_NOEXCEPT_EXPR(
			SPROUT_NOEXCEPT_EXPR(swap(holder_, other.holder_)) && SPROUT_NOEXCEPT_EXPR(swap(current, other.current))
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
	inline void
	swap(sprout::next_iterator<Iterator>& lhs, sprout::next_iterator<Iterator>& rhs)
	SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs)))
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
