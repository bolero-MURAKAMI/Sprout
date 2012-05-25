#ifndef SPROUT_RATIONAL_HPP
#define SPROUT_RATIONAL_HPP

#include <limits>
#include <utility>
#include <stdexcept>
#include <ios>
#include <iostream>
#include <sprout/config.hpp>
#include <sprout/cstdlib/abs.hpp>
#include <sprout/math/gcd.hpp>
#include <sprout/detail/call_traits.hpp>
#include <sprout/detail/io/ios_state.hpp>

namespace sprout {
	//
	// bad_rational
	//
	class bad_rational
		: public std::domain_error
	{
	public:
		explicit bad_rational()
			: std::domain_error("bad rational: zero denominator")
		{}
	};

	template<typename IntType>
	class rational;

	namespace detail {
		struct rational_private_constructor_tag {};

		template<typename IntType>
		inline SPROUT_CONSTEXPR sprout::rational<IntType> make_rational(
			typename sprout::detail::call_traits<IntType>::param_type n,
			typename sprout::detail::call_traits<IntType>::param_type d,
			sprout::detail::rational_private_constructor_tag
			);
	}	// namespace detail

	namespace detail {
		template<typename IntType>
		class rational_impl {
		protected:
			typedef IntType int_type;
			typedef typename sprout::detail::call_traits<IntType>::param_type param_type;
		protected:
			IntType num_;
			IntType den_;
		protected:
			SPROUT_CONSTEXPR rational_impl()
				: num_(0)
				, den_(1)
			{}
			rational_impl(rational_impl const&) = default;
			SPROUT_CONSTEXPR rational_impl(param_type n)
				: num_(n)
				, den_(1)
			{}
			SPROUT_CONSTEXPR rational_impl(param_type n, param_type d)
				: num_(n)
				, den_(d)
			{}
			SPROUT_CONSTEXPR rational_impl(param_type n, param_type d, param_type g)
				: num_(n / g)
				, den_(d / g)
			{}
		};
	}	// namespace detail

	//
	// rational
	//
	template<typename IntType>
	class rational
		: private sprout::detail::rational_impl<IntType>
	{
		static_assert(std::numeric_limits<IntType>::is_specialized, "std::numeric_limits<IntType>::is_specialized");
	public:
		typedef IntType int_type;
		typedef typename sprout::detail::call_traits<IntType>::param_type param_type;
	private:
		struct private_constructor_tag {};
		typedef sprout::detail::rational_impl<IntType> base_type;
	private:
		static SPROUT_CONSTEXPR IntType normalize_g_1(IntType den, IntType g) {
			return den / g < 0 ? -g : g;
		}
		static SPROUT_CONSTEXPR IntType normalize_g(IntType num, IntType den) {
			return den == 0 ? throw sprout::bad_rational()
				: num == 0 ? den
				: normalize_g_1(den, sprout::math::gcd(num, den))
				;
		}
	private:
		using base_type::num_;
		using base_type::den_;
	private:
		SPROUT_CONSTEXPR rational(param_type n, param_type d, private_constructor_tag)
			: base_type(n, d)
		{}
	public:
		SPROUT_CONSTEXPR rational()
			: base_type()
		{}
		rational(rational const&) = default;
		SPROUT_CONSTEXPR rational(param_type n)
			: base_type(n)
		{}
		SPROUT_CONSTEXPR rational(param_type n, param_type d)
			: base_type(n, d, normalize_g(n, d))
		{}

		rational& operator=(rational const&) = default;
		rational& operator=(param_type n) {
			return assign(n, 1);
		}
		rational& assign(param_type n, param_type d) {
			using std::swap;
			rational temp(n, d);
			swap(temp, *this);
			return *this;
		}

		SPROUT_CONSTEXPR IntType numerator() const {
			return num_;
		}
		SPROUT_CONSTEXPR IntType denominator() const {
			return den_;
		}

		rational& operator+=(rational const& rhs) {
			IntType g = sprout::math::gcd(den_, rhs.den_);
			den_ /= g;
			num_ = num_ * (rhs.den_ / g) + rhs.num_ * den_;
			g = sprout::math::gcd(num_, g);
			num_ /= g;
			den_ *= rhs.den_ / g;
			return *this;
		}
		rational& operator-=(rational const& rhs) {
			IntType g = sprout::math::gcd(den_, rhs.den_);
			den_ /= g;
			num_ = num_ * (rhs.den_ / g) - rhs.num_ * den_;
			g = sprout::math::gcd(num_, g);
			num_ /= g;
			den_ *= rhs.den_ / g;
			return *this;
		}
		rational& operator*=(rational const& rhs) {
			IntType gcd1 = sprout::math::gcd(num_, rhs.den_);
			IntType gcd2 = sprout::math::gcd(rhs.num_, den_);
			num_ =(num_ / gcd1) * (rhs.num_ / gcd2);
			den_ =(den_ / gcd2) * (rhs.den_ / gcd1);
			return *this;
		}
		rational& operator/=(rational const& rhs) {
			if (rhs.num_ == IntType(0)) {
				throw bad_rational();
			}
			if (num_ == IntType(0)) {
				return *this;
			}
			IntType gcd1 = sprout::math::gcd(num_, rhs.num_);
			IntType gcd2 = sprout::math::gcd(rhs.den_, den_);
			num_ =(num_ / gcd1) * (rhs.den_ / gcd2);
			den_ =(den_ / gcd2) * (rhs.num_ / gcd1);
			if (den_ < IntType(0)) {
				num_ = -num_;
				den_ = -den_;
			}
			return *this;
		}
		rational& operator+=(param_type rhs) {
			return *this += rational(rhs);
		}
		rational& operator-=(param_type rhs) {
			return *this -= rational(rhs);
		}
		rational& operator*=(param_type rhs) {
			return *this *= rational(rhs);
		}
		rational& operator/=(param_type rhs) {
			return *this /= rational(rhs);
		}

		rational& operator++() {
			num_ += den_;
			return *this;
		}
		rational& operator--() {
			num_ -= den_;
			return *this;
		}
		rational operator++(int) {
			rational result(*this);
			++*this;
			return result;
		}
		rational operator--(int) {
			rational result(*this);
			--*this;
			return result;
		}

		SPROUT_CONSTEXPR bool operator!() const {
			return !num_;
		}
		SPROUT_CONSTEXPR operator bool() const {
			return num_ != 0;
		}

	public:
		friend sprout::rational<IntType> sprout::detail::make_rational<IntType>(
			typename sprout::detail::call_traits<IntType>::param_type n,
			typename sprout::detail::call_traits<IntType>::param_type d,
			sprout::detail::rational_private_constructor_tag
			);
	};

	namespace detail {
		template<typename IntType>
		inline SPROUT_CONSTEXPR sprout::rational<IntType> make_rational(
			typename sprout::detail::call_traits<IntType>::param_type n,
			typename sprout::detail::call_traits<IntType>::param_type d,
			sprout::detail::rational_private_constructor_tag
			)
		{
			return sprout::rational<IntType>(
				n, d,
				typename sprout::rational<IntType>::private_constructor_tag()
				);
		}
	}	// namespace detail

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

	//
	// operator>>
	// operator<<
	//
	template<typename Elem, typename Traits, typename IntType>
	inline std::basic_istream<Elem, Traits>&
	operator>>(std::basic_istream<Elem, Traits>& lhs, sprout::rational<IntType>& rhs) {
		IntType n = IntType(0);
		IntType d = IntType(1);
		Elem c = 0;
		sprout::detail::io::ios_flags_saver saver(lhs);
		lhs >> n;
		c = lhs.get();
		if (c != Elem('/')) {
			lhs.clear(std::istream::badbit);
		}
		lhs >> std::noskipws;
		lhs >> d;
		if (lhs) {
			rhs.assign(n, d);
		}
		return lhs;
	}
	template<typename Elem, typename Traits, typename IntType>
	inline std::basic_ostream<Elem, Traits>&
	operator<<(std::basic_ostream<Elem, Traits>& lhs, sprout::rational<IntType> const& rhs) {
		return lhs << rhs.numerator() << Elem('/') << rhs.denominator();
	}

	//
	// rational_cast
	//
	template<typename T, typename IntType>
	inline SPROUT_CONSTEXPR T
	rational_cast(sprout::rational<IntType> const& src) {
		return static_cast<T>(src.numerator()) / static_cast<T>(src.denominator());
	}

	//
	// abs
	//
	template<typename IntType>
	inline SPROUT_CONSTEXPR sprout::rational<IntType>
	abs(sprout::rational<IntType> const& x) {
		return x.numerator() >= IntType(0) ? x
			: sprout::detail::make_rational<IntType>(
				-x.numerator(), x.denominator(),
				sprout::detail::rational_private_constructor_tag()
				)
			;
	}

} // namespace sprout

#endif  // SPROUT_RATIONAL_HPP
