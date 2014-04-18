/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPLEX_COMPLEX_HPP
#define SPROUT_COMPLEX_COMPLEX_HPP

#include <sprout/config.hpp>

namespace sprout {
	template<typename T>
	class complex;

	namespace detail {
		template<typename T>
		inline SPROUT_CONSTEXPR T
		complex_norm(sprout::complex<T> const& x) {
			return x.real() * x.real() + x.imag() * x.imag();
		}
	}	// namespace detail

	//
	// complex
	//
	template<typename T>
	class complex {
	public:
		typedef T value_type;
	private:
		T re_;
		T im_;
	public:
		SPROUT_CONSTEXPR complex(T const& re = T(), T const& im = T()) SPROUT_NOEXCEPT
			: re_(re), im_(im)
		{}
		complex(complex const&) = default;
		template<typename X>
		SPROUT_CONSTEXPR complex(complex<X> const& other) SPROUT_NOEXCEPT
			: re_(other.real()), im_(other.imag())
		{}
		SPROUT_CONSTEXPR T const& real() const SPROUT_NOEXCEPT {
			return re_;
		}
		SPROUT_CXX14_CONSTEXPR T& real() SPROUT_NOEXCEPT {
			return re_;
		}
		SPROUT_CXX14_CONSTEXPR void real(T re) SPROUT_NOEXCEPT {
			re_ = re;
		}
		SPROUT_CONSTEXPR T const& imag() const SPROUT_NOEXCEPT {
			return im_;
		}
		SPROUT_CXX14_CONSTEXPR T& imag() SPROUT_NOEXCEPT {
			return im_;
		}
		SPROUT_CXX14_CONSTEXPR void imag(T im) SPROUT_NOEXCEPT {
			im_ = im;
		}
		SPROUT_CXX14_CONSTEXPR complex& operator=(T const& rhs) SPROUT_NOEXCEPT {
			re_ = rhs;
			im_ = T();
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR complex& operator+=(T const& rhs) SPROUT_NOEXCEPT {
			re_ += rhs;
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR complex& operator-=(T const& rhs) SPROUT_NOEXCEPT {
			re_ -= rhs;
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR complex& operator*=(T const& rhs) SPROUT_NOEXCEPT {
			re_ *= rhs;
			im_ *= rhs;
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR complex& operator/=(T const& rhs) SPROUT_NOEXCEPT {
			re_ /= rhs;
			im_ /= rhs;
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR complex& operator=(complex const& rhs) SPROUT_NOEXCEPT {
			re_ = rhs.real();
			im_ = rhs.imag();
			return *this;
		}
		template<typename X>
		SPROUT_CXX14_CONSTEXPR complex& operator=(complex<X> const& rhs) SPROUT_NOEXCEPT {
			re_ = rhs.real();
			im_ = rhs.imag();
			return *this;
		}
		template<typename X>
		SPROUT_CXX14_CONSTEXPR complex& operator+=(complex<X> const& rhs) SPROUT_NOEXCEPT {
			re_ += rhs.real();
			im_ += rhs.imag();
			return *this;
		}
		template<typename X>
		SPROUT_CXX14_CONSTEXPR complex& operator-=(complex<X> const& rhs) SPROUT_NOEXCEPT {
			re_ -= rhs.real();
			im_ -= rhs.imag();
			return *this;
		}
		template<typename X>
		SPROUT_CXX14_CONSTEXPR complex& operator*=(complex<X> const& rhs) SPROUT_NOEXCEPT {
			return *this = complex(
				re_ * rhs.real() - im_ * rhs.imag(),
				re_ * rhs.imag() + im_ * rhs.real()
				);
		}
		template<typename X>
		SPROUT_CXX14_CONSTEXPR complex& operator/=(complex<X> const& rhs) SPROUT_NOEXCEPT {
			T n = sprout::detail::complex_norm(rhs);
			return *this = complex(
				(re_ * rhs.real() + im_ * rhs.imag()) / n,
				(im_ * rhs.real() - re_ * rhs.imag()) / n
				);
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPLEX_COMPLEX_HPP
