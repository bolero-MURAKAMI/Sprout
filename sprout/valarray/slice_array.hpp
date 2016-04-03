/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_VALARRAY_SLICE_ARRAY_HPP
#define SPROUT_VALARRAY_SLICE_ARRAY_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/utility/swap.hpp>
#include <sprout/iterator/index_iterator.hpp>
#include <sprout/iterator/reverse_iterator.hpp>
#include <sprout/algorithm/cxx14/copy.hpp>
#include <sprout/algorithm/cxx14/fill.hpp>
#include <sprout/valarray/valarray_fwd.hpp>

namespace sprout {
	//
	// slice
	//
	class slice {
	private:
		std::size_t start_;
		std::size_t size_;
		std::size_t stride_;
	public:
		SPROUT_CONSTEXPR slice()
			: start_(), size_(), stride_()
		{}
		SPROUT_CONSTEXPR slice(std::size_t start, std::size_t size, std::size_t stride)
			: start_(start), size_(size), stride_(stride)
		{}
		SPROUT_CONSTEXPR std::size_t start() const {
			return start_;
		}
		SPROUT_CONSTEXPR std::size_t size() const {
			return size_;
		}
		SPROUT_CONSTEXPR std::size_t stride() const {
			return stride_;
		}
	};

	//
	// slice_array
	//
	template<typename T, std::size_t N>
	class slice_array {
		friend class sprout::valarray<T, N>;
	private:
		typedef sprout::valarray<T, N> valarray_type;
	public:
		typedef typename valarray_type::value_type value_type;
		typedef typename valarray_type::reference reference;
		typedef typename valarray_type::size_type size_type;
		typedef typename valarray_type::difference_type difference_type;
		typedef typename valarray_type::pointer pointer;
		typedef sprout::index_iterator<slice_array const&> iterator;
		typedef sprout::reverse_iterator<iterator> reverse_iterator;
	public:
		SPROUT_STATIC_CONSTEXPR size_type static_size = valarray_type::static_size;
	private:
		sprout::value_holder<valarray_type&> arr_;
		sprout::slice slice_;
	private:
		slice_array() = delete;
		SPROUT_CONSTEXPR slice_array(sprout::valarray<T, N>& arr, sprout::slice const& slice)
			: arr_(arr), slice_(slice)
		{}
	public:
		SPROUT_CONSTEXPR slice_array(slice_array const& other)
			: arr_(other.arr_), slice_(other.slice_)
		{}
		template<std::size_t N2>
		SPROUT_CXX14_CONSTEXPR slice_array const&
		operator=(slice_array<T, N2> const& ar) const {
			sprout::copy(ar.begin(), ar.end(), begin());
			return *this;
		}
		template<std::size_t N2>
		SPROUT_CXX14_CONSTEXPR void
		operator=(sprout::valarray<T, N2> const& ar) const {
			sprout::copy(ar.begin(), ar.end(), begin());
		}
		SPROUT_CXX14_CONSTEXPR void
		operator=(T const& value) const {
			sprout::fill(begin(), end(), value);
		}
		template<std::size_t N2>
		SPROUT_CXX14_CONSTEXPR void
		operator+=(sprout::valarray<T, N2> const& xs) const {
			iterator it2 = begin();
			for (typename sprout::valarray<T, N2>::const_iterator it = xs.begin(), last = xs.end(); it != last; ++it, ++it2) {
				*it2 += *it;
			}
		}
		template<std::size_t N2>
		SPROUT_CXX14_CONSTEXPR void
		operator-=(sprout::valarray<T, N2> const& xs) const {
			iterator it2 = begin();
			for (typename sprout::valarray<T, N2>::const_iterator it = xs.begin(), last = xs.end(); it != last; ++it, ++it2) {
				*it2 -= *it;
			}
		}
		template<std::size_t N2>
		SPROUT_CXX14_CONSTEXPR void
		operator*=(sprout::valarray<T, N2> const& xs) const {
			iterator it2 = begin();
			for (typename sprout::valarray<T, N2>::const_iterator it = xs.begin(), last = xs.end(); it != last; ++it, ++it2) {
				*it2 *= *it;
			}
		}
		template<std::size_t N2>
		SPROUT_CXX14_CONSTEXPR void
		operator/=(sprout::valarray<T, N2> const& xs) const {
			iterator it2 = begin();
			for (typename sprout::valarray<T, N2>::const_iterator it = xs.begin(), last = xs.end(); it != last; ++it, ++it2) {
				*it2 /= *it;
			}
		}
		template<std::size_t N2>
		SPROUT_CXX14_CONSTEXPR void
		operator%=(sprout::valarray<T, N2> const& xs) const {
			iterator it2 = begin();
			for (typename sprout::valarray<T, N2>::const_iterator it = xs.begin(), last = xs.end(); it != last; ++it, ++it2) {
				*it2 %= *it;
			}
		}
		template<std::size_t N2>
		SPROUT_CXX14_CONSTEXPR void
		operator&=(sprout::valarray<T, N2> const& xs) const {
			iterator it2 = begin();
			for (typename sprout::valarray<T, N2>::const_iterator it = xs.begin(), last = xs.end(); it != last; ++it, ++it2) {
				*it2 &= *it;
			}
		}
		template<std::size_t N2>
		SPROUT_CXX14_CONSTEXPR void
		operator|=(sprout::valarray<T, N2> const& xs) const {
			iterator it2 = begin();
			for (typename sprout::valarray<T, N2>::const_iterator it = xs.begin(), last = xs.end(); it != last; ++it, ++it2) {
				*it2 |= *it;
			}
		}
		template<std::size_t N2>
		SPROUT_CXX14_CONSTEXPR void
		operator^=(sprout::valarray<T, N2> const& xs) const {
			iterator it2 = begin();
			for (typename sprout::valarray<T, N2>::const_iterator it = xs.begin(), last = xs.end(); it != last; ++it, ++it2) {
				*it2 ^= *it;
			}
		}
		template<std::size_t N2>
		SPROUT_CXX14_CONSTEXPR void
		operator<<=(sprout::valarray<T, N2> const& xs) const {
			iterator it2 = begin();
			for (typename sprout::valarray<T, N2>::const_iterator it = xs.begin(), last = xs.end(); it != last; ++it, ++it2) {
				*it2 <<= *it;
			}
		}
		template<std::size_t N2>
		SPROUT_CXX14_CONSTEXPR void
		operator>>=(sprout::valarray<T, N2> const& xs) const {
			iterator it2 = begin();
			for (typename sprout::valarray<T, N2>::const_iterator it = xs.begin(), last = xs.end(); it != last; ++it, ++it2) {
				*it2 >>= *it;
			}
		}

		SPROUT_CXX14_CONSTEXPR void
		swap(slice_array& other) SPROUT_NOEXCEPT {
			sprout::swap(arr_, other.arr_);
			sprout::swap(slice_, other.slice_);
		}

		// iterators:
		SPROUT_CONSTEXPR iterator
		begin() const {
			return iterator(*this, 0);
		}
		SPROUT_CONSTEXPR iterator
		end() const {
			return iterator(*this, size());
		}
		SPROUT_CONSTEXPR reverse_iterator
		rbegin() const {
			return reverse_iterator(end());
		}
		SPROUT_CONSTEXPR reverse_iterator
		rend() const {
			return reverse_iterator(begin());
		}
		// capacity:
		SPROUT_CONSTEXPR size_type
		size() const SPROUT_NOEXCEPT {
			return slice_.size();
		}
		SPROUT_CONSTEXPR bool
		empty() const SPROUT_NOEXCEPT {
			return size() == 0;
		}
		// element access:
		SPROUT_CONSTEXPR reference
		operator[](size_type i) const {
			return (*arr_)[slice_.start() + slice_.stride() * i];
		}
		SPROUT_CONSTEXPR reference
		at(size_type i) const {
			return arr_->at(slice_.start() + slice_.stride() * i);
		}
		SPROUT_CONSTEXPR reference
		front() const {
			return (*this)[0];
		}
		SPROUT_CONSTEXPR reference
		back() const {
			return (*this)[size() - 1];
		}
		// others:
		SPROUT_CONSTEXPR iterator
		nth(size_type i) const {
			return i < size() ? begin() + i
				: (throw std::out_of_range("slice_array<>: index out of range"), iterator())
				;
		}
		SPROUT_CONSTEXPR size_type
		index_of(iterator p) const SPROUT_NOEXCEPT {
			return p - begin();
		}
	};
	template<typename T, std::size_t N>
	SPROUT_CONSTEXPR_OR_CONST typename sprout::slice_array<T, N>::size_type sprout::slice_array<T, N>::static_size;

	//
	// swap
	//
	template<typename T, std::size_t N>
	inline SPROUT_CXX14_CONSTEXPR void
	swap(sprout::slice_array<T, N>& lhs, sprout::slice_array<T, N>& rhs)
	SPROUT_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
	{
		lhs.swap(rhs);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_VALARRAY_SLICE_ARRAY_HPP
