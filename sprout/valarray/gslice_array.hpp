/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_VALARRAY_GSLICE_ARRAY_HPP
#define SPROUT_VALARRAY_GSLICE_ARRAY_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/utility/swap.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/iterator/index_iterator.hpp>
#include <sprout/iterator/reverse_iterator.hpp>
#include <sprout/functional/multiplies.hpp>
#include <sprout/algorithm/cxx14/copy.hpp>
#include <sprout/algorithm/cxx14/fill.hpp>
#include <sprout/range/numeric/fixed/partial_sum.hpp>
#include <sprout/range/adaptor/copied.hpp>
#include <sprout/range/adaptor/reversed.hpp>
#include <sprout/valarray/valarray_fwd.hpp>

namespace sprout {
	//
	// gslice
	//
	template<std::size_t N>
	class gslice {
	private:
		std::size_t start_;
		sprout::valarray<std::size_t, N> size_;
		sprout::valarray<std::size_t, N> stride_;
	public:
		SPROUT_CONSTEXPR gslice()
			: start_(), size_(), stride_()
		{}
		SPROUT_CONSTEXPR gslice(
			std::size_t start,
			sprout::valarray<std::size_t, N> const& size,
			sprout::valarray<std::size_t, N> const& stride
			)
			: start_(start), size_(size), stride_(stride)
		{}
		SPROUT_CONSTEXPR std::size_t start() const {
			return start_;
		}
		SPROUT_CONSTEXPR sprout::valarray<std::size_t, N> size() const {
			return size_;
		}
		SPROUT_CONSTEXPR sprout::valarray<std::size_t, N> stride() const {
			return stride_;
		}
	};

	//
	// gslice_array
	//
	template<typename T, std::size_t N, std::size_t M>
	class gslice_array {
		friend class sprout::valarray<T, N>;
	private:
		typedef sprout::valarray<T, N> valarray_type;
	public:
		typedef typename valarray_type::value_type value_type;
		typedef typename valarray_type::reference reference;
		typedef typename valarray_type::size_type size_type;
		typedef typename valarray_type::difference_type difference_type;
		typedef typename valarray_type::pointer pointer;
		typedef sprout::index_iterator<gslice_array const&> iterator;
		typedef sprout::reverse_iterator<iterator> reverse_iterator;
	private:
		typedef sprout::gslice<M> gslice_type;
		typedef sprout::valarray<size_type, (M < N ? M : N)> indexes_type;
	public:
		SPROUT_STATIC_CONSTEXPR size_type static_size = valarray_type::static_size;
	private:
		sprout::value_holder<valarray_type&> arr_;
		std::size_t start_;
		sprout::valarray<std::size_t, M> size_;
		sprout::valarray<std::size_t, M> stride_;
	private:
		gslice_array() SPROUT_DELETED_FUNCTION_DECL
		SPROUT_CONSTEXPR gslice_array(sprout::valarray<T, N>& arr, gslice_type const& gslice)
			: arr_(arr)
			, start_(gslice.start())
			, size_(
				sprout::range::fixed::partial_sum(gslice.size() | sprout::adaptors::reversed, gslice.size(), sprout::multiplies<>())
					| sprout::adaptors::reversed | sprout::adaptors::copied(gslice.size())
				)
			, stride_(gslice.stride())
		{}
		template<typename InputIterator1, typename InputIterator2>
		SPROUT_CONSTEXPR size_type index_impl(
			size_type i,
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2
			) const
		{
			return first1 != last1 ? *first2 * (i / *first1) + index_impl(
					i % *first1,
					sprout::next(first1), last1,
					sprout::next(first2)
					)
				: *first2 * i
				;
		}
		SPROUT_CONSTEXPR size_type index(size_type i) const {
			return i < size() ? start_ + index_impl(i, sprout::next(size_.begin()), size_.end(), stride_.begin())
				: arr_->max_size()
				;
		}
	public:
		SPROUT_CONSTEXPR gslice_array(gslice_array const& other)
			: arr_(other.arr_), start_(other.start_), size_(other.size_), stride_(other.stride_)
		{}
		template<std::size_t N2, std::size_t M2>
		SPROUT_CXX14_CONSTEXPR gslice_array const&
		operator=(gslice_array<T, N2, M2> const& ar) const {
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
		swap(gslice_array& other) SPROUT_NOEXCEPT {
			sprout::swap(arr_, other.arr_);
			sprout::swap(start_, other.start_);
			sprout::swap(size_, other.size_);
			sprout::swap(stride_, other.stride_);
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
			return size_.front();
		}
		SPROUT_CONSTEXPR bool
		empty() const SPROUT_NOEXCEPT {
			return size() == 0;
		}
		// element access:
		SPROUT_CONSTEXPR reference
		operator[](size_type i) const {
			return (*arr_)[index(i)];
		}
		SPROUT_CONSTEXPR reference
		at(size_type i) const {
			return arr_->at(index(i));
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
				: (throw std::out_of_range("gslice_array<>: index out of range"), iterator())
				;
		}
		SPROUT_CONSTEXPR size_type
		index_of(iterator p) const SPROUT_NOEXCEPT {
			return p - begin();
		}
	};
	template<typename T, std::size_t N, std::size_t M>
	SPROUT_CONSTEXPR_OR_CONST typename sprout::gslice_array<T, N, M>::size_type sprout::gslice_array<T, N, M>::static_size;

	//
	// swap
	//
	template<typename T, std::size_t N, std::size_t M>
	inline SPROUT_CXX14_CONSTEXPR void
	swap(sprout::gslice_array<T, N, M>& lhs, sprout::gslice_array<T, N, M>& rhs)
	SPROUT_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
	{
		lhs.swap(rhs);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_VALARRAY_GSLICE_ARRAY_HPP
