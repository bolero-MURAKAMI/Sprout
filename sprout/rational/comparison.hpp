/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RATIONAL_COMPARISON_HPP
#define SPROUT_RATIONAL_COMPARISON_HPP

#include <sprout/config.hpp>
#include <sprout/rational/rational.hpp>

namespace sprout {
	//
	// operator==
	// operator!=
	//
	template<typename IntType>
	inline SPROUT_CONSTEXPR bool
	operator==(sprout::rational<IntType> const& lhs, sprout::rational<IntType> const& rhs) {
		return lhs.numerator() == rhs.numerator() && lhs.denominator() == rhs.denominator();
	}
	template<typename IntType>
	inline SPROUT_CONSTEXPR bool
	operator==(sprout::rational<IntType> const& lhs, typename sprout::rational<IntType>::param_type rhs) {
		return lhs.denominator() == IntType(1) && lhs.numerator() == rhs;
	}
	template<typename IntType>
	inline SPROUT_CONSTEXPR bool
	operator==(typename sprout::rational<IntType>::param_type lhs, sprout::rational<IntType> const& rhs) {
		return rhs == lhs;
	}
	template<typename IntType>
	inline SPROUT_CONSTEXPR bool
	operator!=(sprout::rational<IntType> const& lhs, sprout::rational<IntType> const& rhs) {
		return !(lhs == rhs);
	}
	template<typename IntType>
	inline SPROUT_CONSTEXPR bool
	operator!=(sprout::rational<IntType> const& lhs, typename sprout::rational<IntType>::param_type rhs) {
		return !(lhs == rhs);
	}
	template<typename IntType>
	inline SPROUT_CONSTEXPR bool
	operator!=(typename sprout::rational<IntType>::param_type lhs, sprout::rational<IntType> const& rhs) {
		return !(lhs == rhs);
	}

	//
	// operator<
	// operator>
	// operator<=
	// operator>=
	//
	namespace detail {
		template<typename IntType>
		inline SPROUT_CONSTEXPR bool
		rational_less_impl_2(
			sprout::rational<IntType> const& lhs, sprout::rational<IntType> const& rhs,
			IntType d1, IntType q1, IntType r1,
			IntType d2, IntType q2, IntType r2,
			unsigned reverse = 0
			)
		{
			return q1 != q2 ? reverse ? q1 > q2 : q1 < q2
				: r1 == IntType(0) || r2 == IntType(0)
					? r1 == r2 ? false
					: (r1 != IntType(0)) != static_cast<bool>(reverse ^ 1)
				: sprout::detail::rational_less_impl_2(
					lhs, rhs,
					r1, d1 / r1, d1 % r1,
					r2, d2 / r2, d2 % r2,
					reverse ^ 1
					)
				;
		}
		template<typename IntType>
		inline SPROUT_CONSTEXPR bool
		rational_less_impl_1(
			sprout::rational<IntType> const& lhs, sprout::rational<IntType> const& rhs,
			IntType d1, IntType q1, IntType r1,
			IntType d2, IntType q2, IntType r2
			)
		{
			return r2 < IntType(0) ? sprout::detail::rational_less_impl_1(
					lhs, rhs,
					d1, q1, r1,
					d2, q2 - 1, r2 + d2
					)
				: sprout::detail::rational_less_impl_2(
					lhs, rhs,
					d1, q1, r1,
					d2, q2, r2
					)
				;
		}
		template<typename IntType>
		inline SPROUT_CONSTEXPR bool
		rational_less_impl(
			sprout::rational<IntType> const& lhs, sprout::rational<IntType> const& rhs,
			IntType d1, IntType q1, IntType r1
			)
		{
			return r1 < IntType(0) ? sprout::detail::rational_less_impl(
					lhs, rhs,
					d1, q1 - 1, r1 + d1
					)
				: sprout::detail::rational_less_impl_1(
					lhs, rhs,
					d1, q1, r1,
					rhs.denominator(), rhs.numerator() / rhs.denominator(), rhs.numerator() % rhs.denominator()
					)
				;
		}

		template<typename IntType>
		inline SPROUT_CONSTEXPR bool
		rational_less_impl(
			sprout::rational<IntType> const& lhs, typename sprout::rational<IntType>::param_type rhs,
			IntType q, IntType r
			)
		{
			return r < IntType(0) ? sprout::detail::rational_less_impl(
					lhs, rhs,
					r + lhs.denominator(), q - 1
					)
				: q < rhs
				;
		}
	}	// namespace detail
	template<typename IntType>
	inline SPROUT_CONSTEXPR bool
	operator<(sprout::rational<IntType> const& lhs, sprout::rational<IntType> const& rhs) {
		return sprout::detail::rational_less_impl(
			lhs, rhs,
			lhs.denominator(), lhs.numerator() / lhs.denominator(), lhs.numerator() % lhs.denominator()
			);
	}
	template<typename IntType>
	inline SPROUT_CONSTEXPR bool
	operator<(sprout::rational<IntType> const& lhs, typename sprout::rational<IntType>::param_type rhs) {
		return sprout::detail::rational_less_impl(
			lhs, rhs,
			lhs.numerator() / lhs.denominator(), lhs.numerator() % lhs.denominator()
			);
	}
	template<typename IntType>
	inline SPROUT_CONSTEXPR bool
	operator<(typename sprout::rational<IntType>::param_type lhs, sprout::rational<IntType> const& rhs) {
		return lhs != rhs && !(rhs < lhs);
	}

	template<typename IntType>
	inline SPROUT_CONSTEXPR bool
	operator>(sprout::rational<IntType> const& lhs, sprout::rational<IntType> const& rhs) {
		return rhs < lhs;
	}
	template<typename IntType>
	inline SPROUT_CONSTEXPR bool
	operator>(sprout::rational<IntType> const& lhs, typename sprout::rational<IntType>::param_type rhs) {
		return rhs < lhs;
	}
	template<typename IntType>
	inline SPROUT_CONSTEXPR bool
	operator>(typename sprout::rational<IntType>::param_type lhs, sprout::rational<IntType> const& rhs) {
		return rhs < lhs;
	}

	template<typename IntType>
	inline SPROUT_CONSTEXPR bool
	operator<=(sprout::rational<IntType> const& lhs, sprout::rational<IntType> const& rhs) {
		return !(rhs < lhs);
	}
	template<typename IntType>
	inline SPROUT_CONSTEXPR bool
	operator<=(sprout::rational<IntType> const& lhs, typename sprout::rational<IntType>::param_type rhs) {
		return !(rhs < lhs);
	}
	template<typename IntType>
	inline SPROUT_CONSTEXPR bool
	operator<=(typename sprout::rational<IntType>::param_type lhs, sprout::rational<IntType> const& rhs) {
		return !(rhs < lhs);
	}

	template<typename IntType>
	inline SPROUT_CONSTEXPR bool
	operator>=(sprout::rational<IntType> const& lhs, sprout::rational<IntType> const& rhs) {
		return !(lhs < rhs);
	}
	template<typename IntType>
	inline SPROUT_CONSTEXPR bool
	operator>=(sprout::rational<IntType> const& lhs, typename sprout::rational<IntType>::param_type rhs) {
		return !(lhs < rhs);
	}
	template<typename IntType>
	inline SPROUT_CONSTEXPR bool
	operator>=(typename sprout::rational<IntType>::param_type lhs, sprout::rational<IntType> const& rhs) {
		return !(lhs < rhs);
	}
}	// namespace sprout

#endif	// SPROUT_RATIONAL_COMPARISON_HPP
