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
		return sprout::detail::make_rational<IntType>(
			-r.numerator(), r.denominator(),
			sprout::detail::rational_private_constructor_tag()
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
			return sprout::detail::make_rational<IntType>(
				num / g, den * (rhs.denominator() / g),
				sprout::detail::rational_private_constructor_tag()
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
				sprout::math::gcd(num, g), den, num
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
			sprout::math::gcd(lhs.denominator(), rhs.denominator())
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
			return sprout::detail::make_rational<IntType>(
				num / g, den * (rhs.denominator() / g),
				sprout::detail::rational_private_constructor_tag()
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
				sprout::math::gcd(num, g), den, num
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
			sprout::math::gcd(lhs.denominator(), rhs.denominator())
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
			return sprout::detail::make_rational<IntType>(
				(lhs.numerator() / gcd1) * (rhs.numerator() / gcd2),
				(lhs.denominator() / gcd2) * (rhs.denominator() / gcd1),
				sprout::detail::rational_private_constructor_tag()
				);
		}
	}	// namespace detail
	template<typename IntType>
	inline SPROUT_CONSTEXPR sprout::rational<IntType>
	operator*(sprout::rational<IntType> const& lhs, sprout::rational<IntType> const& rhs) {
		return sprout::detail::rational_mul_impl(
			lhs, rhs,
			sprout::math::gcd(lhs.numerator(), rhs.denominator()),
			sprout::math::gcd(rhs.numerator(), lhs.denominator())
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
			return den < IntType(0) ? sprout::detail::make_rational<IntType>(
					-num, -den,
					sprout::detail::rational_private_constructor_tag()
					)
				: sprout::detail::make_rational<IntType>(
					num, den,
					sprout::detail::rational_private_constructor_tag()
					)
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
				sprout::math::gcd(lhs.numerator(), rhs.numerator()),
				sprout::math::gcd(rhs.denominator(), lhs.denominator())
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
} // namespace sprout

#endif  // SPROUT_RATIONAL_ARITHMETIC_HPP
