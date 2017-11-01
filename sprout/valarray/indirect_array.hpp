/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_VALARRAY_INDIRECT_ARRAY_HPP
#define SPROUT_VALARRAY_INDIRECT_ARRAY_HPP

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
	// indirect_array
	//
	template<typename T, std::size_t N, std::size_t M>
	class indirect_array {
		friend class sprout::valarray<T, N>;
	private:
		typedef sprout::valarray<T, N> valarray_type;
	public:
		typedef typename valarray_type::value_type value_type;
		typedef typename valarray_type::reference reference;
		typedef typename valarray_type::size_type size_type;
		typedef typename valarray_type::difference_type difference_type;
		typedef typename valarray_type::pointer pointer;
		typedef sprout::index_iterator<indirect_array const&> iterator;
		typedef sprout::reverse_iterator<iterator> reverse_iterator;
	private:
		typedef sprout::valarray<size_type, M> indexes_type;
	public:
		SPROUT_STATIC_CONSTEXPR size_type static_size = valarray_type::static_size;
	private:
		sprout::value_holder<valarray_type&> arr_;
		indexes_type indexes_;
	private:
		indirect_array() SPROUT_DELETED_FUNCTION_DECL
		SPROUT_CONSTEXPR indirect_array(sprout::valarray<T, N>& arr, indexes_type const& indexes)
			: arr_(arr)
			, indexes_(indexes)
		{}
	public:
		SPROUT_CONSTEXPR indirect_array(indirect_array const& other)
			: arr_(other.arr_), indexes_(other.indexes_)
		{}
		template<std::size_t N2, std::size_t M2>
		SPROUT_CXX14_CONSTEXPR indirect_array const&
		operator=(indirect_array<T, N2, M2> const& ar) const {
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
		swap(indirect_array& other) SPROUT_NOEXCEPT {
			sprout::swap(arr_, other.arr_);
			sprout::swap(indexes_, other.indexes_);
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
			return indexes_.size();
		}
		SPROUT_CONSTEXPR bool
		empty() const SPROUT_NOEXCEPT {
			return size() == 0;
		}
		// element access:
		SPROUT_CONSTEXPR reference
		operator[](size_type i) const {
			return (*arr_)[indexes_[i]];
		}
		SPROUT_CONSTEXPR reference
		at(size_type i) const {
			return arr_->at(indexes_.at(i));
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
				: (throw std::out_of_range("indirect_array<>: index out of range"), iterator())
				;
		}
		SPROUT_CONSTEXPR size_type
		index_of(iterator p) const SPROUT_NOEXCEPT {
			return p - begin();
		}
	};
	template<typename T, std::size_t N, std::size_t M>
	SPROUT_CONSTEXPR_OR_CONST typename sprout::indirect_array<T, N, M>::size_type sprout::indirect_array<T, N, M>::static_size;

	//
	// swap
	//
	template<typename T, std::size_t N, std::size_t M>
	inline SPROUT_CXX14_CONSTEXPR void
	swap(sprout::indirect_array<T, N, M>& lhs, sprout::indirect_array<T, N, M>& rhs)
	SPROUT_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
	{
		lhs.swap(rhs);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_VALARRAY_INDIRECT_ARRAY_HPP
