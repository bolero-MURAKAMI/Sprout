/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ITERATOR_BYTES_ITERATOR_HPP
#define SPROUT_ITERATOR_BYTES_ITERATOR_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/iterator/prev.hpp>
#include <sprout/iterator/distance.hpp>
#include <sprout/endian_traits.hpp>
#include <sprout/utility/swap.hpp>

namespace sprout {
	//
	// bytes_iterator
	//
	template<
		typename Iterator,
		typename Traits = sprout::endian_traits<typename std::iterator_traits<Iterator>::value_type>
	>
	class bytes_iterator
		: public std::iterator<
			typename std::iterator_traits<Iterator>::iterator_category,
			unsigned char,
			std::ptrdiff_t,
			void,
			unsigned char
		>
	{
	public:
		typedef Iterator iterator_type;
		typedef Traits traits_type;
	private:
		typedef std::iterator<
			typename std::iterator_traits<Iterator>::iterator_category,
			unsigned char,
			std::ptrdiff_t,
			void,
			unsigned char
		> base_type;
	public:
		typedef typename base_type::iterator_category iterator_category;
		typedef typename base_type::value_type value_type;
		typedef typename base_type::difference_type difference_type;
		typedef typename base_type::pointer pointer;
		typedef typename base_type::reference reference;
	private:
		struct next_tag {};
		struct prev_tag {};
		struct ra_tag {};
	private:
		iterator_type it_;
		difference_type i_;
	private:
		SPROUT_CONSTEXPR bytes_iterator(iterator_type it, difference_type i)
			: it_(it) , i_(i)
		{}
		SPROUT_CONSTEXPR bytes_iterator(iterator_type it, difference_type i, next_tag)
			: it_(i / traits_type::size() == 0 ? it : sprout::next(it))
			, i_(i % traits_type::size())
		{}
		SPROUT_CONSTEXPR bytes_iterator(iterator_type it, difference_type i, prev_tag)
			: it_((i + 1 - traits_type::size()) / traits_type::size() == 0 ? it : sprout::prev(it))
			, i_(i % traits_type::size() + traits_type::size())
		{}
		SPROUT_CONSTEXPR bytes_iterator(iterator_type it, difference_type i, ra_tag)
			: it_(i >= 0
				? sprout::next(it, i / traits_type::size())
				: sprout::next(it, (i + 1 - traits_type::size()) / traits_type::size())
				)
			, i_(i >= 0
				? i % traits_type::size()
				: i % traits_type::size() + traits_type::size()
				)
		{}
	public:
		SPROUT_CONSTEXPR bytes_iterator()
			: it_(), i_()
		{}
		bytes_iterator(bytes_iterator const&) = default;
		explicit SPROUT_CONSTEXPR bytes_iterator(iterator_type it)
			: it_(it), i_()
		{}
		SPROUT_CONSTEXPR iterator_type const& base() const {
			return it_;
		}
		SPROUT_CONSTEXPR difference_type index() const {
			return i_;
		}
		SPROUT_CONSTEXPR bytes_iterator next() const {
			return bytes_iterator(it_, i_ + 1, next_tag());
		}
		SPROUT_CONSTEXPR bytes_iterator prev() const {
			return bytes_iterator(it_, i_ - 1, prev_tag());
		}
		SPROUT_CXX14_CONSTEXPR void swap(bytes_iterator& other)
		SPROUT_NOEXCEPT_IF_EXPR(sprout::swap(it_, other.it_))
		{
			sprout::swap(it_, other.it_);
			sprout::swap(i_, other.i_);
		}
		SPROUT_CONSTEXPR reference operator*() const {
			return traits_type::get_byte(*it_, i_);
		}
		SPROUT_CXX14_CONSTEXPR bytes_iterator& operator++() {
			bytes_iterator temp(next());
			temp.swap(*this);
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR bytes_iterator operator++(int) {
			bytes_iterator result(*this);
			++*this;
			return result;
		}
		SPROUT_CXX14_CONSTEXPR bytes_iterator& operator--() {
			bytes_iterator temp(prev());
			temp.swap(*this);
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR bytes_iterator operator--(int) {
			bytes_iterator result(*this);
			--*this;
			return result;
		}
		SPROUT_CONSTEXPR bytes_iterator operator+(difference_type n) const {
			return bytes_iterator(it_, i_ + n, ra_tag());
		}
		SPROUT_CONSTEXPR bytes_iterator operator-(difference_type n) const {
			return bytes_iterator(it_, i_ - n, ra_tag());
		}
		SPROUT_CXX14_CONSTEXPR bytes_iterator& operator+=(difference_type n) {
			bytes_iterator temp(it_, i_ + n, ra_tag());
			temp.swap(*this);
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR bytes_iterator& operator-=(difference_type n) {
			bytes_iterator temp(it_, i_ - n, ra_tag());
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR reference operator[](difference_type n) const {
			return *(*this + n);
		}
	};

	template<typename Iterator1, typename Iterator2, typename Traits>
	inline SPROUT_CONSTEXPR bool
	operator==(sprout::bytes_iterator<Iterator1, Traits> const& lhs, sprout::bytes_iterator<Iterator2, Traits> const& rhs) {
		return lhs.base() == rhs.base() && lhs.index() == rhs.index();
	}
	template<typename Iterator1, typename Iterator2, typename Traits>
	inline SPROUT_CONSTEXPR bool
	operator!=(sprout::bytes_iterator<Iterator1, Traits> const& lhs, sprout::bytes_iterator<Iterator2, Traits> const& rhs) {
		return !(lhs == rhs);
	}
	template<typename Iterator1, typename Iterator2, typename Traits>
	inline SPROUT_CONSTEXPR bool
	operator<(sprout::bytes_iterator<Iterator1, Traits> const& lhs, sprout::bytes_iterator<Iterator2, Traits> const& rhs) {
		return lhs.base() < rhs.base() || (lhs.base() == rhs.base() && lhs.index() < rhs.index());
	}
	template<typename Iterator1, typename Iterator2, typename Traits>
	inline SPROUT_CONSTEXPR bool
	operator>(sprout::bytes_iterator<Iterator1, Traits> const& lhs, sprout::bytes_iterator<Iterator2, Traits> const& rhs) {
		return rhs < lhs;
	}
	template<typename Iterator1, typename Iterator2, typename Traits>
	inline SPROUT_CONSTEXPR bool
	operator<=(sprout::bytes_iterator<Iterator1, Traits> const& lhs, sprout::bytes_iterator<Iterator2, Traits> const& rhs) {
		return !(rhs < lhs);
	}
	template<typename Iterator1, typename Iterator2, typename Traits>
	inline SPROUT_CONSTEXPR bool
	operator>=(sprout::bytes_iterator<Iterator1, Traits> const& lhs, sprout::bytes_iterator<Iterator2, Traits> const& rhs) {
		return !(lhs < rhs);
	}
	template<typename Iterator1, typename Iterator2, typename Traits>
	inline SPROUT_CONSTEXPR decltype(std::declval<Iterator1>() - std::declval<Iterator2>())
	operator-(sprout::bytes_iterator<Iterator1, Traits> const& lhs, sprout::bytes_iterator<Iterator2, Traits> const& rhs) {
		return (lhs.base() - rhs.base()) * Traits::size() + (lhs.index() - rhs.index());
	}
	template<typename Iterator, typename Traits>
	inline SPROUT_CONSTEXPR sprout::bytes_iterator<Iterator, Traits>
	operator+(typename sprout::bytes_iterator<Iterator, Traits>::difference_type n, sprout::bytes_iterator<Iterator, Traits> const& it) {
		return it + n;
	}

	//
	// swap
	//
	template<typename Iterator, typename Traits>
	inline SPROUT_CXX14_CONSTEXPR void
	swap(sprout::bytes_iterator<Iterator, Traits>& lhs, sprout::bytes_iterator<Iterator, Traits>& rhs)
	SPROUT_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
	{
		lhs.swap(rhs);
	}

	//
	// make_bytes_iterator
	//
	template<typename Iterator>
	inline SPROUT_CONSTEXPR sprout::bytes_iterator<Iterator>
	make_bytes_iterator(Iterator it) {
		return sprout::bytes_iterator<Iterator>(it);
	}
	template<typename Iterator, typename Traits>
	inline SPROUT_CONSTEXPR sprout::bytes_iterator<Iterator, Traits>
	make_bytes_iterator(Iterator it, Traits) {
		return sprout::bytes_iterator<Iterator, Traits>(it);
	}

	//
	// make_big_bytes_iterator
	// make_little_bytes_iterator
	//
	template<typename Iterator>
	inline SPROUT_CONSTEXPR sprout::bytes_iterator<Iterator, sprout::big_endian_traits<typename std::iterator_traits<Iterator>::value_type> >
	make_big_bytes_iterator(Iterator it) {
		return sprout::bytes_iterator<Iterator, sprout::big_endian_traits<typename std::iterator_traits<Iterator>::value_type> >(it);
	}
	template<typename Iterator>
	inline SPROUT_CONSTEXPR sprout::bytes_iterator<Iterator, sprout::little_endian_traits<typename std::iterator_traits<Iterator>::value_type> >
	make_little_bytes_iterator(Iterator it) {
		return sprout::bytes_iterator<Iterator, sprout::little_endian_traits<typename std::iterator_traits<Iterator>::value_type> >(it);
	}

	//
	// iterator_next
	//
	template<typename Iterator, typename Traits>
	inline SPROUT_CONSTEXPR sprout::bytes_iterator<Iterator, Traits>
	iterator_next(sprout::bytes_iterator<Iterator, Traits> const& it) {
		return it.next();
	}

	//
	// iterator_prev
	//
	template<typename Iterator, typename Traits>
	inline SPROUT_CONSTEXPR sprout::bytes_iterator<Iterator, Traits>
	iterator_prev(sprout::bytes_iterator<Iterator, Traits> const& it) {
		return it.prev();
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_BYTES_ITERATOR_HPP
