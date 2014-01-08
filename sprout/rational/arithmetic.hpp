/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RATIONAL_ARITHMETIC_HPP
#define SPROUT_RATIONAL_ARITHMETIC_HPP

#include <sprout/config.hpp>
#include <sprout/rational/rational.hpp>
#include <sprout/rational/exceptions.hpp>
#include <sprout/math/gcd.hpp>

namespace sprout {
	//
	// operator+
	// operator-
	//
	template<typename IntType>
	inline SPROUT_CONSTEXPR sprout::rational<IntType>
	operator+(rational<IntType> const& r) {
		return r;
	}
	template<typename IntType>
	inline SPROUT_CONSTEXPR sprout::rational<IntType>
	operator-(rational<IntType> const& r) {
		return sprout::detail::rational_construct_access<IntType>::raw_construct(
			-r.numerator(), r.denominator()
			);
	}

	//
	// operator+
	// operator-
	// operator*
	// operator/
	//
	namespace detail {
		template<typename IntType>
		inline SPROUT_CONSTEXPR sprout::rational<IntType>
		rational_add_impl_3(
			sprout::rational<IntType> const& rhs,
			IntType g, IntType den, IntType num
			)
		{
			return sprout::detail::rational_construct_access<IntType>::raw_construct(
				num / g, den * (rhs.denominator() / g)
				);
		}
		template<typename IntType>
		inline SPROUT_CONSTEXPR sprout::rational<IntType>
		rational_add_impl_2(
			sprout::rational<IntType> const& rhs,
			IntType g, IntType den, IntType num
			)
		{
			return rational_add_impl_3(
				rhs,
				sprout::gcd(num, g), den, num
				);
		}
		template<typename IntType>
		inline SPROUT_CONSTEXPR sprout::rational<IntType>
		rational_add_impl_1(
			sprout::rational<IntType> const& lhs, sprout::rational<IntType> const& rhs,
			IntType g, IntType den
			)
		{
			return rational_add_impl_2(
				rhs,
				g, den, lhs.numerator() * (rhs.denominator() / g) + rhs.numerator() * den
				);
		}
		template<typename IntType>
		inline SPROUT_CONSTEXPR sprout::rational<IntType>
		rational_add_impl(
			sprout::rational<IntType> const& lhs, sprout::rational<IntType> const& rhs,
			IntType g
			)
		{
			return rational_add_impl_1(
				lhs, rhs,
				g, lhs.denominator() / g
				);
		}
	}	// namespace detail
	template<typename IntType>
	inline SPROUT_CONSTEXPR sprout::rational<IntType>
	operator+(sprout::rational<IntType> const& lhs, sprout::rational<IntType> const& rhs) {
		return sprout::detail::rational_add_impl(
			lhs, rhs,
			sprout::gcd(lhs.denominator(), rhs.denominator())
			);
	}
	template<typename IntType>
	inline SPROUT_CONSTEXPR sprout::rational<IntType>
	operator+(sprout::rational<IntType> const& lhs, typename sprout::rational<IntType>::param_type rhs) {
		return lhs + sprout::rational<IntType>(rhs);
	}
	template<typename IntType>
	inline SPROUT_CONSTEXPR sprout::rational<IntType>
	operator+(typename sprout::rational<IntType>::param_type lhs, sprout::rational<IntType> const& rhs) {
		return sprout::rational<IntType>(lhs) + rhs;
	}

	namespace detail {
		template<typename IntType>
		inline SPROUT_CONSTEXPR sprout::rational<IntType>
		rational_sub_impl_3(
			sprout::rational<IntType> const& rhs,
			IntType g, IntType den, IntType num
			)
		{
			return sprout::detail::rational_construct_access<IntType>::raw_construct(
				num / g, den * (rhs.denominator() / g)
				);
		}
		template<typename IntType>
		inline SPROUT_CONSTEXPR sprout::rational<IntType>
		rational_sub_impl_2(
			sprout::rational<IntType> const& rhs,
			IntType g, IntType den, IntType num
			)
		{
			return rational_sub_impl_3(
				rhs,
				sprout::gcd(num, g), den, num
				);
		}
		template<typename IntType>
		inline SPROUT_CONSTEXPR sprout::rational<IntType>
		rational_sub_impl_1(
			sprout::rational<IntType> const& lhs, sprout::rational<IntType> const& rhs,
			IntType g, IntType den
			)
		{
			return rational_sub_impl_2(
				rhs,
				g, den, lhs.numerator() * (rhs.denominator() / g) - rhs.numerator() * den
				);
		}
		template<typename IntType>
		inline SPROUT_CONSTEXPR sprout::rational<IntType>
		rational_sub_impl(
			sprout::rational<IntType> const& lhs, sprout::rational<IntType> const& rhs,
			IntType g
			)
		{
			return rational_sub_impl_1(
				lhs, rhs,
				g, lhs.denominator() / g
				);
		}
	}	// namespace detail
	template<typename IntType>
	inline SPROUT_CONSTEXPR sprout::rational<IntType>
	operator-(sprout::rational<IntType> const& lhs, sprout::rational<IntType> const& rhs) {
		return sprout::detail::rational_sub_impl(
			lhs, rhs,
			sprout::gcd(lhs.denominator(), rhs.denominator())
			);
	}
	template<typename IntType>
	inline SPROUT_CONSTEXPR sprout::rational<IntType>
	operator-(sprout::rational<IntType> const& lhs, typename sprout::rational<IntType>::param_type rhs) {
		return lhs - sprout::rational<IntType>(rhs);
	}
	template<typename IntType>
	inline SPROUT_CONSTEXPR sprout::rational<IntType>
	operator-(typename sprout::rational<IntType>::param_type lhs, sprout::rational<IntType> const& rhs) {
		return sprout::rational<IntType>(lhs) - rhs;
	}

	namespace detail {
		template<typename IntType>
		inline SPROUT_CONSTEXPR sprout::rational<IntType>
		rational_mul_impl(
			sprout::rational<IntType> const& lhs, sprout::rational<IntType> const& rhs,
			IntType gcd1, IntType gcd2
			)
		{
			return sprout::detail::rational_construct_access<IntType>::raw_construct(
				(lhs.numerator() / gcd1) * (rhs.numerator() / gcd2),
				(lhs.denominator() / gcd2) * (rhs.denominator() / gcd1)
				);
		}
	}	// namespace detail
	template<typename IntType>
	inline SPROUT_CONSTEXPR sprout::rational<IntType>
	operator*(sprout::rational<IntType> const& lhs, sprout::rational<IntType> const& rhs) {
		return sprout::detail::rational_mul_impl(
			lhs, rhs,
			sprout::gcd(lhs.numerator(), rhs.denominator()),
			sprout::gcd(rhs.numerator(), lhs.denominator())
			);
	}
	template<typename IntType>
	inline SPROUT_CONSTEXPR sprout::rational<IntType>
	operator*(sprout::rational<IntType> const& lhs, typename sprout::rational<IntType>::param_type rhs) {
		return lhs * sprout::rational<IntType>(rhs);
	}
	template<typename IntType>
	inline SPROUT_CONSTEXPR sprout::rational<IntType>
	operator*(typename sprout::rational<IntType>::param_type lhs, sprout::rational<IntType> const& rhs) {
		return sprout::rational<IntType>(lhs) * rhs;
	}

	namespace detail {
		template<typename IntType>
		inline SPROUT_CONSTEXPR sprout::rational<IntType>
		rational_div_impl_1(IntType num, IntType den) {
			return den < IntType(0) ? sprout::detail::rational_construct_access<IntType>::raw_construct(-num, -den)
				: sprout::detail::rational_construct_access<IntType>::raw_construct(num, den)
				;
		}
		template<typename IntType>
		inline SPROUT_CONSTEXPR sprout::rational<IntType>
		rational_div_impl(
			sprout::rational<IntType> const& lhs, sprout::rational<IntType> const& rhs,
			IntType gcd1, IntType gcd2
			)
		{
			return sprout::detail::rational_div_impl_1(
				(lhs.numerator() / gcd1) * (rhs.denominator() / gcd2),
				(lhs.denominator() / gcd2) * (rhs.numerator() / gcd1)
				);
		}
	}	// namespace detail
	template<typename IntType>
	inline SPROUT_CONSTEXPR sprout::rational<IntType>
	operator/(sprout::rational<IntType> const& lhs, sprout::rational<IntType> const& rhs) {
		return rhs.numerator() == IntType(0) ? throw sprout::bad_rational()
			: lhs.numerator() == IntType(0) ? lhs
			: sprout::detail::rational_div_impl(
				lhs, rhs,
				sprout::gcd(lhs.numerator(), rhs.numerator()),
				sprout::gcd(rhs.denominator(), lhs.denominator())
				)
			;
	}
	template<typename IntType>
	inline SPROUT_CONSTEXPR sprout::rational<IntType>
	operator/(sprout::rational<IntType> const& lhs, typename sprout::rational<IntType>::param_type rhs) {
		return lhs / sprout::rational<IntType>(rhs);
	}
	template<typename IntType>
	inline SPROUT_CONSTEXPR sprout::rational<IntType>
	operator/(typename sprout::rational<IntType>::param_type lhs, sprout::rational<IntType> const& rhs) {
		return sprout::rational<IntType>(lhs) / rhs;
	}
}	// namespace sprout

#endif	// SPROUT_RATIONAL_ARITHMETIC_HPP
