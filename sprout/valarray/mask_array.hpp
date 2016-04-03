/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_VALARRAY_MASKE_ARRAY_HPP
#define SPROUT_VALARRAY_MASKE_ARRAY_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/utility/swap.hpp>
#include <sprout/iterator/index_iterator.hpp>
#include <sprout/algorithm/count.hpp>
#include <sprout/algorithm/cxx14/copy.hpp>
#include <sprout/algorithm/cxx14/fill.hpp>
#include <sprout/valarray/valarray_fwd.hpp>
#include <sprout/detail/algorithm/mask_index.hpp>

namespace sprout {
	//
	// mask_array
	//
	template<typename T, std::size_t N, std::size_t M>
	class mask_array {
		friend class sprout::valarray<T, N>;
	private:
		typedef sprout::valarray<T, N> valarray_type;
	public:
		typedef typename valarray_type::value_type value_type;
		typedef typename valarray_type::reference reference;
		typedef typename valarray_type::size_type size_type;
		typedef typename valarray_type::difference_type difference_type;
		typedef typename valarray_type::pointer pointer;
		typedef sprout::index_iterator<mask_array const&> iterator;
	private:
		typedef sprout::valarray<bool, M> mask_type;
		typedef sprout::valarray<size_type, (M < N ? M : N)> indexes_type;
	public:
		SPROUT_STATIC_CONSTEXPR size_type static_size = valarray_type::static_size;
	private:
		sprout::value_holder<valarray_type&> arr_;
		indexes_type indexes_;
	private:
		mask_array() = delete;
		SPROUT_CONSTEXPR mask_array(sprout::valarray<T, N>& arr, mask_type const& mask)
			: arr_(arr)
			, indexes_(
				sprout::detail::mask_index(
					mask.begin(), mask.end(),
					indexes_type(sprout::count(mask.begin(), mask.end(), true))
					)
				)
		{}
	public:
		SPROUT_CONSTEXPR mask_array(mask_array const& other)
			: arr_(other.arr_), indexes_(other.indexes_)
		{}
		template<std::size_t N2, std::size_t M2>
		SPROUT_CXX14_CONSTEXPR mask_array const&
		operator=(mask_array<T, N2, M2> const& ar) const {
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
		swap(mask_array& other) SPROUT_NOEXCEPT {
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
		// capacity:
		SPROUT_CONSTEXPR size_type size() const SPROUT_NOEXCEPT {
			return indexes_.size();
		}
		SPROUT_CONSTEXPR bool empty() const SPROUT_NOEXCEPT {
			return size() == 0;
		}
		// element access:
		SPROUT_CONSTEXPR reference operator[](size_type i) const {
			return (*arr_)[indexes_[i]];
		}
		SPROUT_CONSTEXPR reference at(size_type i) const {
			return arr_->at(indexes_.at(i));
		}
		SPROUT_CONSTEXPR reference front() const {
			return (*this)[0];
		}
		SPROUT_CONSTEXPR reference back() const {
			return (*this)[size() - 1];
		}
	};
	template<typename T, std::size_t N, std::size_t M>
	SPROUT_CONSTEXPR_OR_CONST typename sprout::mask_array<T, N, M>::size_type sprout::mask_array<T, N, M>::static_size;

	//
	// swap
	//
	template<typename T, std::size_t N, std::size_t M>
	inline SPROUT_CXX14_CONSTEXPR void
	swap(sprout::mask_array<T, N, M>& lhs, sprout::mask_array<T, N, M>& rhs)
	SPROUT_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
	{
		lhs.swap(rhs);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_VALARRAY_MASKE_ARRAY_HPP
