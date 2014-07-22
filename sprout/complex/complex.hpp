/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPLEX_COMPLEX_HPP
#define SPROUT_COMPLEX_COMPLEX_HPP

#include <complex>
#include <sprout/config.hpp>
#include <sprout/array/array.hpp>

namespace sprout {
	template<typename T>
	class complex;

	namespace detail {
		template<typename Complex>
		inline SPROUT_CONSTEXPR typename Complex::value_type
		complex_norm(Complex const& x) {
			return x.real() * x.real() + x.imag() * x.imag();
		}
	}	// namespace detail

	//
	// complex
	//
	template<typename T>
	class complex {
	private:
		typedef sprout::array<T, 2> array_type;
	public:
		typedef T value_type;
		typedef typename array_type::iterator iterator;
		typedef typename array_type::const_iterator const_iterator;
		typedef typename array_type::reference reference;
		typedef typename array_type::const_reference const_reference;
		typedef typename array_type::size_type size_type;
		typedef typename array_type::pointer pointer;
		typedef typename array_type::const_pointer const_pointer;
		typedef typename array_type::pointer reverse_iterator;
		typedef typename array_type::pointer const_reverse_iterator;
	public:
		SPROUT_STATIC_CONSTEXPR size_type static_size = array_type::static_size;
	private:
		array_type elems_;
	public:
		SPROUT_CONSTEXPR complex(T const& re = T(), T const& im = T()) SPROUT_NOEXCEPT
			: elems_{{re, im}}
		{}
		SPROUT_CXX14_CONSTEXPR complex(complex const&) = default;
		template<typename U>
		SPROUT_CONSTEXPR complex(complex<U> const& other) SPROUT_NOEXCEPT
			: elems_{{other.real(), other.imag()}}
		{}
		template<typename U>
		SPROUT_CONSTEXPR complex(std::complex<U> const& other) SPROUT_NOEXCEPT
			: elems_{{other.real(), other.imag()}}
		{}
		SPROUT_CONSTEXPR T const& real() const SPROUT_NOEXCEPT {
			return elems_[0];
		}
		SPROUT_CXX14_CONSTEXPR T& real() SPROUT_NOEXCEPT {
			return elems_[0];
		}
		SPROUT_CXX14_CONSTEXPR void real(T re) SPROUT_NOEXCEPT {
			elems_[0] = re;
		}
		SPROUT_CONSTEXPR T const& imag() const SPROUT_NOEXCEPT {
			return elems_[1];
		}
		SPROUT_CXX14_CONSTEXPR T& imag() SPROUT_NOEXCEPT {
			return elems_[1];
		}
		SPROUT_CXX14_CONSTEXPR void imag(T im) SPROUT_NOEXCEPT {
			elems_[1] = im;
		}
		SPROUT_CXX14_CONSTEXPR complex& operator=(T const& rhs) SPROUT_NOEXCEPT {
			real() = rhs;
			imag() = T();
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR complex& operator+=(T const& rhs) SPROUT_NOEXCEPT {
			real() += rhs;
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR complex& operator-=(T const& rhs) SPROUT_NOEXCEPT {
			real() -= rhs;
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR complex& operator*=(T const& rhs) SPROUT_NOEXCEPT {
			real() *= rhs;
			imag() *= rhs;
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR complex& operator/=(T const& rhs) SPROUT_NOEXCEPT {
			real() /= rhs;
			imag() /= rhs;
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR complex& operator=(complex const& rhs) SPROUT_NOEXCEPT {
			real() = rhs.real();
			imag() = rhs.imag();
			return *this;
		}
		template<typename X>
		SPROUT_CXX14_CONSTEXPR complex& operator=(complex<X> const& rhs) SPROUT_NOEXCEPT {
			real() = rhs.real();
			imag() = rhs.imag();
			return *this;
		}
		template<typename X>
		SPROUT_CXX14_CONSTEXPR complex& operator+=(complex<X> const& rhs) SPROUT_NOEXCEPT {
			real() += rhs.real();
			imag() += rhs.imag();
			return *this;
		}
		template<typename X>
		SPROUT_CXX14_CONSTEXPR complex& operator-=(complex<X> const& rhs) SPROUT_NOEXCEPT {
			real() -= rhs.real();
			imag() -= rhs.imag();
			return *this;
		}
		template<typename X>
		SPROUT_CXX14_CONSTEXPR complex& operator*=(complex<X> const& rhs) SPROUT_NOEXCEPT {
			return *this = complex(
				real() * rhs.real() - imag() * rhs.imag(),
				real() * rhs.imag() + imag() * rhs.real()
				);
		}
		template<typename X>
		SPROUT_CXX14_CONSTEXPR complex& operator/=(complex<X> const& rhs) SPROUT_NOEXCEPT {
			T n = sprout::detail::complex_norm(rhs);
			return *this = complex(
				(real() * rhs.real() + imag() * rhs.imag()) / n,
				(imag() * rhs.real() - real() * rhs.imag()) / n
				);
		}
		// iterators:
		SPROUT_CXX14_CONSTEXPR iterator begin() SPROUT_NOEXCEPT {
			return elems_.begin();
		}
		SPROUT_CONSTEXPR const_iterator begin() const SPROUT_NOEXCEPT {
			return elems_.begin();
		}
		SPROUT_CXX14_CONSTEXPR iterator end() SPROUT_NOEXCEPT {
			return elems_.end();
		}
		SPROUT_CONSTEXPR const_iterator end() const SPROUT_NOEXCEPT {
			return elems_.end();
		}
		SPROUT_CXX14_CONSTEXPR reverse_iterator rbegin() SPROUT_NOEXCEPT {
			return elems_.rbegin();
		}
		SPROUT_CONSTEXPR const_reverse_iterator rbegin() const SPROUT_NOEXCEPT {
			return elems_.rbegin();
		}
		SPROUT_CXX14_CONSTEXPR reverse_iterator rend() SPROUT_NOEXCEPT {
			return elems_.rend();
		}
		SPROUT_CONSTEXPR const_reverse_iterator rend() const SPROUT_NOEXCEPT {
			return elems_.rend();
		}
		SPROUT_CONSTEXPR const_iterator cbegin() const SPROUT_NOEXCEPT {
			return elems_.cbegin();
		}
		SPROUT_CONSTEXPR const_iterator cend() const SPROUT_NOEXCEPT {
			return elems_.cbegin();
		}
		SPROUT_CONSTEXPR const_reverse_iterator crbegin() const SPROUT_NOEXCEPT {
			return elems_.crbegin();
		}
		SPROUT_CONSTEXPR const_reverse_iterator crend() const SPROUT_NOEXCEPT {
			return elems_.crend();
		}
		// capacity:
		SPROUT_CONSTEXPR size_type size() const SPROUT_NOEXCEPT {
			return elems_.size();
		}
		SPROUT_CONSTEXPR size_type max_size() const SPROUT_NOEXCEPT {
			return elems_.max_size();
		}
		SPROUT_CONSTEXPR bool empty() const SPROUT_NOEXCEPT {
			return elems_.empty();
		}
		// element access:
		SPROUT_CXX14_CONSTEXPR reference operator[](size_type i) {
			return elems_[i];
		}
		SPROUT_CONSTEXPR const_reference operator[](size_type i) const {
			return elems_[i];
		}
		SPROUT_CXX14_CONSTEXPR reference at(size_type i) {
			return elems_.at(i);
		}
		SPROUT_CONSTEXPR const_reference at(size_type i) const {
			return elems_.at(i);
		}
		SPROUT_CXX14_CONSTEXPR reference front() {
			return elems_.front();
		}
		SPROUT_CONSTEXPR const_reference front() const {
			return elems_.front();
		}
		SPROUT_CXX14_CONSTEXPR reference back() {
			return elems_.back();
		}
		SPROUT_CONSTEXPR const_reference back() const {
			return elems_.back();
		}

		SPROUT_CXX14_CONSTEXPR pointer data() SPROUT_NOEXCEPT {
			return elems_.data();
		}
		SPROUT_CONSTEXPR const_pointer data() const SPROUT_NOEXCEPT {
			return elems_.data();
		}
		SPROUT_CXX14_CONSTEXPR pointer c_array() SPROUT_NOEXCEPT {
			return elems_.c_array();
		}
		SPROUT_CONSTEXPR const_pointer c_array() const SPROUT_NOEXCEPT {
			return elems_.c_array();
		}

		template<typename U>
		SPROUT_EXPLICIT_CONVERSION SPROUT_CONSTEXPR operator std::complex<U>() const SPROUT_NOEXCEPT {
			return std::complex<U>(real(), imag());
		}
	};
	template<typename T>
	SPROUT_CONSTEXPR_OR_CONST typename sprout::complex<T>::size_type sprout::complex<T>::static_size;
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPLEX_COMPLEX_HPP
