/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ITERATOR_DFT_ITERATOR_HPP
#define SPROUT_ITERATOR_DFT_ITERATOR_HPP

#include <iterator>
#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/iterator/prev.hpp>
#include <sprout/iterator/distance.hpp>
#include <sprout/utility/swap.hpp>
#include <sprout/numeric/dft/dft_element.hpp>

namespace sprout {
	//
	// dft_iterator
	//
	template<typename Iterator>
	class dft_iterator
		: public std::iterator<
			std::random_access_iterator_tag,
			typename std::iterator_traits<Iterator>::value_type,
			typename std::iterator_traits<Iterator>::difference_type,
			void,
			typename std::iterator_traits<Iterator>::value_type
		>
	{
	private:
		typedef std::iterator<
			std::random_access_iterator_tag,
			typename std::iterator_traits<Iterator>::value_type,
			typename std::iterator_traits<Iterator>::difference_type,
			void,
			typename std::iterator_traits<Iterator>::value_type
		> base_type;
	public:
		typedef Iterator iterator_type;
		typedef typename base_type::iterator_category iterator_category;
		typedef typename base_type::value_type value_type;
		typedef typename base_type::difference_type difference_type;
		typedef typename base_type::pointer pointer;
		typedef typename base_type::reference reference;
	private:
		iterator_type first_;
		iterator_type last_;
		difference_type index_;
		difference_type size_;
	private:
		SPROUT_CONSTEXPR dft_iterator(iterator_type first, iterator_type last, difference_type index, difference_type size)
			: first_(first), last_(last), index_(index)
			, size_(size)
		{}
	public:
		SPROUT_CONSTEXPR dft_iterator()
			: first_(), last_(), index_()
			, size_()
		{}
		dft_iterator(dft_iterator const&) = default;
		SPROUT_CONSTEXPR dft_iterator(iterator_type first, iterator_type last, difference_type index = 0)
			: first_(first), last_(last), index_(index)
			, size_(sprout::distance(first, last))
		{}
		SPROUT_CONSTEXPR dft_iterator next() const {
			return dft_iterator(first_, last_, index_, index_ + 1, size_);
		}
		SPROUT_CONSTEXPR dft_iterator prev() const {
			return dft_iterator(first_, last_, index_, index_ - 1, size_);
		}
		SPROUT_CXX14_CONSTEXPR void swap(dft_iterator& other)
		SPROUT_NOEXCEPT_IF(
			SPROUT_NOEXCEPT_EXPR(sprout::swap(first_, other.first_))
			&& SPROUT_NOEXCEPT_EXPR(sprout::swap(last_, other.last_))
			)
		{
			sprout::swap(first_, other.first_);
			sprout::swap(last_, other.last_);
			sprout::swap(index_, other.index_);
			sprout::swap(size_, other.size_);
		}
		SPROUT_CONSTEXPR reference operator*() const {
			return sprout::detail::dft_element_impl(first_, last_, index_, size_);
		}
		SPROUT_CXX14_CONSTEXPR dft_iterator& operator++() {
			dft_iterator temp(next());
			temp.swap(*this);
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR dft_iterator operator++(int) {
			dft_iterator result(*this);
			++*this;
			return result;
		}
		SPROUT_CXX14_CONSTEXPR dft_iterator& operator--() {
			dft_iterator temp(prev());
			temp.swap(*this);
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR dft_iterator operator--(int) {
			dft_iterator result(*this);
			--*this;
			return result;
		}
		SPROUT_CONSTEXPR dft_iterator operator+(difference_type n) const {
			return dft_iterator(first_, last_, index_, index_ + n, size_);
		}
		SPROUT_CONSTEXPR dft_iterator operator-(difference_type n) const {
			return dft_iterator(first_, last_, index_, index_ - n, size_);
		}
		SPROUT_CXX14_CONSTEXPR dft_iterator& operator+=(difference_type n) {
			dft_iterator temp(first_, last_, index_, index_ + n, size_);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR dft_iterator& operator-=(difference_type n) {
			dft_iterator temp(first_, last_, index_, index_ - n, size_);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR reference operator[](difference_type n) const {
			return sprout::detail::dft_element_impl(first_, last_, index_ + n, size_);
		}
	};

	template<typename Iterator>
	inline SPROUT_CONSTEXPR bool
	operator==(sprout::dft_iterator<Iterator> const& lhs, sprout::dft_iterator<Iterator> const& rhs) {
		return lhs.index() == rhs.index();
	}
	template<typename Iterator>
	inline SPROUT_CONSTEXPR bool
	operator!=(sprout::dft_iterator<Iterator> const& lhs, sprout::dft_iterator<Iterator> const& rhs) {
		return !(lhs == rhs);
	}
	template<typename Iterator>
	inline SPROUT_CONSTEXPR bool
	operator<(sprout::dft_iterator<Iterator> const& lhs, sprout::dft_iterator<Iterator> const& rhs) {
		return lhs.index_ < rhs.index_;
	}
	template<typename Iterator>
	inline SPROUT_CONSTEXPR bool
	operator>(sprout::dft_iterator<Iterator> const& lhs, sprout::dft_iterator<Iterator> const& rhs) {
		return rhs < lhs;
	}
	template<typename Iterator>
	inline SPROUT_CONSTEXPR bool
	operator<=(sprout::dft_iterator<Iterator> const& lhs, sprout::dft_iterator<Iterator> const& rhs) {
		return !(rhs < lhs);
	}
	template<typename Iterator>
	inline SPROUT_CONSTEXPR bool
	operator>=(sprout::dft_iterator<Iterator> const& lhs, sprout::dft_iterator<Iterator> const& rhs) {
		return !(lhs < rhs);
	}
	template<typename Iterator>
	inline SPROUT_CONSTEXPR typename sprout::dft_iterator<Iterator>::difference_type
	operator-(sprout::dft_iterator<Iterator> const& lhs, sprout::dft_iterator<Iterator> const& rhs) {
		return lhs.index() - rhs.index();
	}
	template<typename Iterator>
	inline SPROUT_CONSTEXPR sprout::dft_iterator<Iterator>
	operator+(typename sprout::dft_iterator<Iterator>::difference_type n, sprout::dft_iterator<Iterator> const& it) {
		return it + n;
	}

	//
	// make_dft_iterator
	//
	template<typename Iterator>
	inline SPROUT_CONSTEXPR sprout::dft_iterator<Iterator>
	make_dft_iterator(Iterator first, Iterator last, typename std::iterator_traits<Iterator>::difference_type i = 0) {
		return sprout::dft_iterator<Iterator>(first, last, i);
	}

	//
	// swap
	//
	template<typename Iterator>
	inline SPROUT_CXX14_CONSTEXPR void
	swap(sprout::dft_iterator<Iterator>& lhs, sprout::dft_iterator<Iterator>& rhs)
	SPROUT_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
	{
		lhs.swap(rhs);
	}

	//
	// iterator_next
	//
	template<typename Iterator>
	inline SPROUT_CONSTEXPR sprout::dft_iterator<Iterator>
	iterator_next(sprout::dft_iterator<Iterator> const& it) {
		return it.next();
	}

	//
	// iterator_prev
	//
	template<typename Iterator>
	inline SPROUT_CONSTEXPR sprout::dft_iterator<Iterator>
	iterator_prev(sprout::dft_iterator<Iterator> const& it) {
		return it.prev();
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_DFT_ITERATOR_HPP
