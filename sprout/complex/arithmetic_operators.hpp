/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPLEX_ARITHMETIC_OPERATORS_HPP
#define SPROUT_COMPLEX_ARITHMETIC_OPERATORS_HPP

#include <sprout/config.hpp>
#include <sprout/complex/complex.hpp>

namespace sprout {
	// 26.4.6, operators:
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	operator+(sprout::complex<T> const& lhs, sprout::complex<T> const& rhs) {
		return sprout::complex<T>(lhs.real() + rhs.real(), lhs.imag() + rhs.imag());
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	operator+(sprout::complex<T> const& lhs, T const& rhs) {
		return sprout::complex<T>(lhs.real() + rhs, lhs.imag());
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	operator+(T const& lhs, sprout::complex<T> const& rhs) {
		return sprout::complex<T>(lhs + rhs.real(), rhs.imag());
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	operator-(sprout::complex<T> const& lhs, sprout::complex<T> const& rhs) {
		return sprout::complex<T>(lhs.real() - rhs.real(), lhs.imag() - rhs.imag());
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	operator-(sprout::complex<T> const& lhs, T const& rhs) {
		return sprout::complex<T>(lhs.real() - rhs, lhs.imag());
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	operator-(T const& lhs, sprout::complex<T> const& rhs) {
		return sprout::complex<T>(lhs - rhs.real(), -rhs.imag());
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	operator*(sprout::complex<T> const& lhs, sprout::complex<T> const& rhs) {
		return sprout::complex<T>(
			lhs.real() * rhs.real() - lhs.imag() * rhs.imag(),
			lhs.real() * rhs.imag() + lhs.imag() * rhs.real()
			);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	operator*(sprout::complex<T> const& lhs, T const& rhs) {
		return sprout::complex<T>(lhs.real() * rhs, lhs.imag() * rhs);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	operator*(T const& lhs, sprout::complex<T> const& rhs) {
		return sprout::complex<T>(lhs * rhs.real(), lhs * rhs.imag());
	}
	namespace detail {
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::complex<T>
		divides_impl(sprout::complex<T> const& lhs, sprout::complex<T> const& rhs, T const& n) {
			return sprout::complex<T>(
				(lhs.real() * rhs.real() + lhs.imag() * rhs.imag()) / n,
				(lhs.imag() * rhs.real() - lhs.real() * rhs.imag()) / n
				);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::complex<T>
		divides_impl(T const& lhs, sprout::complex<T> const& rhs, T const& n) {
			return sprout::complex<T>(lhs * rhs.real() / n, -lhs * rhs.imag() / n);
		}
	}	// namespace detail
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	operator/(sprout::complex<T> const& lhs, sprout::complex<T> const& rhs) {
		return sprout::detail::divides_impl(lhs, rhs, sprout::detail::complex_norm(rhs));
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	operator/(sprout::complex<T> const& lhs, T const& rhs) {
		return sprout::complex<T>(lhs.real() / rhs, lhs.imag() / rhs);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	operator/(T const& lhs, sprout::complex<T> const& rhs) {
		return sprout::detail::divides_impl(lhs, rhs, sprout::detail::complex_norm(rhs));
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	operator+(sprout::complex<T> const& x) {
		return x;
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	operator-(sprout::complex<T> const& x) {
		return sprout::complex<T>(-x.real(), -x.imag());
	}
	template<typename T>
	inline SPROUT_CONSTEXPR bool
	operator==(sprout::complex<T> const& lhs, sprout::complex<T> const& rhs) {
		return lhs.real() == rhs.real() && lhs.imag() == rhs.imag();
	}
	template<typename T>
	inline SPROUT_CONSTEXPR bool
	operator==(sprout::complex<T> const& lhs, T const& rhs) {
		return lhs.real() == rhs && lhs.imag() == T();
	}
	template<typename T>
	inline SPROUT_CONSTEXPR bool
	operator==(T const& lhs, sprout::complex<T> const& rhs) {
		return lhs == rhs.real() && T() == rhs.imag();
	}
	template<typename T>
	inline SPROUT_CONSTEXPR bool
	operator!=(sprout::complex<T> const& lhs, sprout::complex<T> const& rhs) {
		return !(lhs == rhs);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR bool
	operator!=(sprout::complex<T> const& lhs, T const& rhs) {
		return !(lhs == rhs);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR bool
	operator!=(T const& lhs, sprout::complex<T> const& rhs) {
		return !(lhs == rhs);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPLEX_ARITHMETIC_OPERATORS_HPP
