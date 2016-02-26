/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_QUATERNION_OPERATORS_HPP
#define SPROUT_MATH_QUATERNION_OPERATORS_HPP

#include <iosfwd>
#include <sstream>
#include <locale>
#include <sprout/config.hpp>
#include <sprout/math/quaternion/quaternion.hpp>

namespace sprout {
	namespace math {
		//
		// operator+
		//
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator+(T const& lhs, sprout::math::quaternion<T> const& rhs) {
			return sprout::math::quaternion<T>(
				lhs + rhs.R_component_1(),
				rhs.R_component_2(),
				rhs.R_component_3(),
				rhs.R_component_4()
				);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator+(sprout::math::quaternion<T> const& lhs, T const& rhs) {
			return sprout::math::quaternion<T>(
				lhs.R_component_1() + rhs,
				lhs.R_component_2(),
				lhs.R_component_3(),
				lhs.R_component_4()
				);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator+(sprout::complex<T> const& lhs, sprout::math::quaternion<T> const& rhs) {
			return sprout::math::quaternion<T>(
				lhs.real() + rhs.R_component_1(),
				lhs.imag() + rhs.R_component_2(),
				rhs.R_component_3(),
				rhs.R_component_4()
				);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator+(sprout::math::quaternion<T> const& lhs, sprout::complex<T> const& rhs) {
			return sprout::math::quaternion<T>(
				lhs.R_component_1() + rhs.real(),
				lhs.R_component_2() + rhs.imag(),
				lhs.R_component_3(),
				lhs.R_component_4()
				);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator+(sprout::math::quaternion<T> const& lhs, sprout::math::quaternion<T> const& rhs) {
			return sprout::math::quaternion<T>(
				lhs.R_component_1() + rhs.R_component_1(),
				lhs.R_component_2() + rhs.R_component_2(),
				lhs.R_component_3() + rhs.R_component_3(),
				lhs.R_component_4() + rhs.R_component_4()
				);
		}
		//
		// operator-
		//
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator-(T const& lhs, sprout::math::quaternion<T> const& rhs) {
			return sprout::math::quaternion<T>(
				lhs - rhs.R_component_1(),
				rhs.R_component_2(),
				rhs.R_component_3(),
				rhs.R_component_4()
				);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator-(sprout::math::quaternion<T> const& lhs, T const& rhs) {
			return sprout::math::quaternion<T>(
				lhs.R_component_1() - rhs,
				lhs.R_component_2(),
				lhs.R_component_3(),
				lhs.R_component_4()
				);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator-(sprout::complex<T> const& lhs, sprout::math::quaternion<T> const& rhs) {
			return sprout::math::quaternion<T>(
				lhs.real() - rhs.R_component_1(),
				lhs.imag() - rhs.R_component_2(),
				rhs.R_component_3(),
				rhs.R_component_4()
				);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator-(sprout::math::quaternion<T> const& lhs, sprout::complex<T> const& rhs) {
			return sprout::math::quaternion<T>(
				lhs.R_component_1() - rhs.real(),
				lhs.R_component_2() - rhs.imag(),
				lhs.R_component_3(),
				lhs.R_component_4()
				);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator-(sprout::math::quaternion<T> const& lhs, sprout::math::quaternion<T> const& rhs) {
			return sprout::math::quaternion<T>(
				lhs.R_component_1() - rhs.R_component_1(),
				lhs.R_component_2() - rhs.R_component_2(),
				lhs.R_component_3() - rhs.R_component_3(),
				lhs.R_component_4() - rhs.R_component_4()
				);
		}
		//
		// operator*
		//
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator*(T const& lhs, sprout::math::quaternion<T> const& rhs) {
			return sprout::math::quaternion<T>(
				lhs * rhs.R_component_1(),
				lhs * rhs.R_component_2(),
				lhs * rhs.R_component_3(),
				lhs * rhs.R_component_4()
				);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator*(sprout::math::quaternion<T> const& lhs, T const& rhs) {
			return sprout::math::quaternion<T>(
				lhs.R_component_1() * rhs,
				lhs.R_component_2() * rhs,
				lhs.R_component_3() * rhs,
				lhs.R_component_4() * rhs
				);
		}
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
			mul_qc_impl(T const& a, T const& b, T const& c, T const& d, T const& ar, T const& br) {
				return sprout::math::quaternion<T>(
					+a * ar - b * br,
					+a * br + b * ar,
					+c * ar + d * br,
					-c * br + d * ar
					);
			}
		}	// namespace detail
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator*(sprout::complex<T> const& lhs, sprout::math::quaternion<T> const& rhs) {
			return sprout::math::detail::mul_qc_impl(
				lhs.R_component_1(), lhs.R_component_2(), lhs.R_component_3(), lhs.R_component_4(),
				rhs.real(), rhs.imag()
				);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator*(sprout::math::quaternion<T> const& lhs, sprout::complex<T> const& rhs) {
			return sprout::math::detail::mul_qc_impl(
				rhs.R_component_1(), rhs.R_component_2(), rhs.R_component_3(), rhs.R_component_4(),
				lhs.real(), lhs.imag()
				);
		}
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
			mul_qq_impl(T const& a, T const& b, T const& c, T const& d, T const& ar, T const& br, T const& cr, T const& dr) {
				return sprout::math::quaternion<T>(
					+a * ar - b * br - c * cr - d * dr,
					+a * br + b * ar + c * dr - d * cr,
					+a * cr - b * dr + c * ar + d * br,
					+a * dr + b * cr - c * br + d * ar
					);
			}
		}	// namespace detail
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator*(sprout::math::quaternion<T> const& lhs, sprout::math::quaternion<T> const& rhs) {
			return sprout::math::detail::mul_qq_impl(
				lhs.R_component_1(), lhs.R_component_2(), lhs.R_component_3(), lhs.R_component_4(),
				rhs.R_component_1(), rhs.R_component_2(), rhs.R_component_3(), rhs.R_component_4()
				);
		}
		//
		// operator/
		//
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator/(T const& lhs, sprout::math::quaternion<T> const& rhs) {
			return sprout::math::quaternion<T>(
				lhs / rhs.R_component_1(),
				lhs / rhs.R_component_2(),
				lhs / rhs.R_component_3(),
				lhs / rhs.R_component_4()
				);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator/(sprout::math::quaternion<T> const& lhs, T const& rhs) {
			return sprout::math::quaternion<T>(
				lhs.R_component_1() / rhs,
				lhs.R_component_2() / rhs,
				lhs.R_component_3() / rhs,
				lhs.R_component_4() / rhs
				);
		}
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
			div_qq_impl_4(sprout::array<T, 4> const& tt) {
				return sprout::math::quaternion<T>(
					tt[0], tt[1], tt[2], tt[3]
					);
			}
			template<typename T>
			inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
			div_qq_impl_3(sprout::array<T, 4> const& tr, T const& mixam, sprout::array<T, 4> const& tt) {
				return sprout::math::detail::div_qq_impl_3(
					sprout::math::detail::mul(tt, mixam / sprout::math::detail::sum(tr))
					);
			}
			template<typename T>
			inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
			div_qq_impl_2(T const& a, T const& b, T const& c, T const& d, sprout::array<T, 4> const& tr, T const& mixam) {
				return sprout::math::detail::div_qq_impl_3(
					sprout::math::detail::mul(tr, tr), mixam,
					sprout::array<T, 4>{{
						+a * tr[0] + b * tr[1] + c * tr[2] + d * tr[3],
						-a * tr[1] + b * tr[0] - c * tr[3] + d * tr[2],
						-a * tr[2] + b * tr[3] + c * tr[0] - d * tr[1],
						-a * tr[3] - b * tr[2] + c * tr[1] + d * tr[0]
						}}
					);
			}
			template<typename T>
			inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
			div_qq_impl_1(T const& a, T const& b, T const& c, T const& d, sprout::array<T, 4> const& tr, T const& mixam) {
				return sprout::math::detail::div_qq_impl_2(
					a, b, c, d, sprout::math::detail::mul(tr, mixam), mixam
					);
			}
			template<typename T>
			inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
			div_qq_impl(T const& a, T const& b, T const& c, T const& d, sprout::array<T, 4> const& tr) {
				return sprout::math::detail::div_qq_impl_1(
					a, b, c, d, tr,
					static_cast<T>(1) / sprout::math::detail::abs_max(tr)
					);
			}
		}	// namespace detail
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator/(sprout::complex<T> const& lhs, sprout::math::quaternion<T> const& rhs) {
			return sprout::math::detail::div_qq_impl(
				lhs.real(), lhs.imag(), static_cast<T>(0), static_cast<T>(0),
				sprout::array<T, 4>{{rhs.R_component_1(), rhs.R_component_2(), rhs.R_component_3(), rhs.R_component_4()}}
				);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator/(sprout::math::quaternion<T> const& lhs, sprout::complex<T> const& rhs) {
			return sprout::math::detail::div_qq_impl(
				lhs.R_component_1(), lhs.R_component_2(), lhs.R_component_3(), lhs.R_component_4(),
				sprout::array<T, 4>{{rhs.real(), rhs.imag(), static_cast<T>(0), static_cast<T>(0)}}
				);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator/(sprout::math::quaternion<T> const& lhs, sprout::math::quaternion<T> const& rhs) {
			return sprout::math::detail::div_qq_impl(
				lhs.R_component_1(), lhs.R_component_2(), lhs.R_component_3(), lhs.R_component_4(),
				sprout::array<T, 4>{{rhs.R_component_1(), rhs.R_component_2(), rhs.R_component_3(), rhs.R_component_4()}}
				);
		}

		//
		// operator+
		// operator-
		//
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator+(sprout::math::quaternion<T> const& q) {
			return q;
		}
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator-(sprout::math::quaternion<T> const& q) {
			return sprout::math::quaternion<T>(-q.R_component_1(), -q.R_component_2(), -q.R_component_3(), -q.R_component_4());
		}

		//
		// operator==
		// operator!=
		//
		template<typename T>
		inline SPROUT_CONSTEXPR bool
		operator==(T const& lhs, sprout::math::quaternion<T> const& rhs) {
			return rhs.R_component_1() == lhs
				&& rhs.R_component_2() == static_cast<T>(0)
				&& rhs.R_component_3() == static_cast<T>(0)
				&& rhs.R_component_4() == static_cast<T>(0)
				;
		}
		template<typename T>
		inline SPROUT_CONSTEXPR bool
		operator==(sprout::math::quaternion<T> const& lhs, T const& rhs) {
			return lhs.R_component_1() == rhs
				&& lhs.R_component_2() == static_cast<T>(0)
				&& lhs.R_component_3() == static_cast<T>(0)
				&& lhs.R_component_4() == static_cast<T>(0)
				;
		}
		template<typename T>
		inline SPROUT_CONSTEXPR bool
		operator==(sprout::complex<T> const& lhs, sprout::math::quaternion<T> const& rhs) {
			return rhs.R_component_1() == lhs.real()
				&& rhs.R_component_2() == lhs.imag()
				&& rhs.R_component_3() == static_cast<T>(0)
				&& rhs.R_component_4() == static_cast<T>(0)
				;
		}
		template<typename T>
		inline SPROUT_CONSTEXPR bool
		operator==(sprout::math::quaternion<T> const& lhs, sprout::complex<T> const& rhs) {
			return lhs.R_component_1() == rhs.real()
				&& lhs.R_component_2() == rhs.imag()
				&& lhs.R_component_3() == static_cast<T>(0)
				&& lhs.R_component_4() == static_cast<T>(0)
				;
		}
		template<typename T>
		inline SPROUT_CONSTEXPR bool
		operator==(sprout::math::quaternion<T> const& lhs, sprout::math::quaternion<T> const& rhs) {
			return rhs.R_component_1() == lhs.R_component_1()
				&& rhs.R_component_2() == lhs.R_component_2()
				&& rhs.R_component_3() == lhs.R_component_3()
				&& rhs.R_component_4() == lhs.R_component_4()
				;
		}

#define	SPROUT_QUATERNION_NOT_EQUAL_GENERATOR \
		{ \
			return !(lhs == rhs); \
		}

		template<typename T>
		inline SPROUT_CONSTEXPR bool
		operator!=(T const& lhs, sprout::math::quaternion<T> const& rhs)
		SPROUT_QUATERNION_NOT_EQUAL_GENERATOR
		template<typename T>
		inline SPROUT_CONSTEXPR bool
		operator!=(sprout::math::quaternion<T> const& lhs, T const& rhs)
		SPROUT_QUATERNION_NOT_EQUAL_GENERATOR
		template<typename T>
		inline SPROUT_CONSTEXPR bool
		operator!=(sprout::complex<T> const& lhs, sprout::math::quaternion<T> const& rhs)
		SPROUT_QUATERNION_NOT_EQUAL_GENERATOR
		template<typename T>
		inline SPROUT_CONSTEXPR bool
		operator!=(sprout::math::quaternion<T> const& lhs, sprout::complex<T> const& rhs)
		SPROUT_QUATERNION_NOT_EQUAL_GENERATOR
		template<typename T>
		inline SPROUT_CONSTEXPR bool
		operator!=(sprout::math::quaternion<T> const& lhs, sprout::math::quaternion<T> const& rhs)
		SPROUT_QUATERNION_NOT_EQUAL_GENERATOR

#undef	SPROUT_QUATERNION_NOT_EQUAL_GENERATOR

		//
		// operator<<
		// operator>>
		//
		template<typename T, typename Elem, typename Traits>
		inline SPROUT_NON_CONSTEXPR std::basic_ostream<Elem, Traits>&
		operator<<(	std::basic_ostream<Elem, Traits>& lhs, sprout::math::quaternion<T> const& rhs) {
			std::basic_ostringstream<Elem, Traits> s;
			s.flags(lhs.flags());
			s.imbue(lhs.getloc());
			s.precision(lhs.precision());
			s
				<< '('
				<< rhs.R_component_1() << ','
				<< rhs.R_component_2() << ','
				<< rhs.R_component_3() << ','
				<< rhs.R_component_4()
				<< ')'
				;
			return lhs << s.str();
		}
		template<typename T, typename Elem, typename Traits>
		inline SPROUT_NON_CONSTEXPR std::basic_istream<Elem, Traits>&
		operator>>(std::basic_istream<Elem, Traits>& lhs, sprout::math::quaternion<T>& rhs) {
			std::ctype<Elem> const& ct = std::use_facet<std::ctype<Elem> >(lhs.getloc());
			T a = T();
			T b = T();
			T c = T();
			T d = T();
			sprout::complex<T> u = sprout::complex<T>();
			sprout::complex<T> v = sprout::complex<T>();
			Elem ch = Elem();
			char cc;
			lhs >> ch;
			if (!lhs.good()) {
				goto finish;
			}
			cc = ct.narrow(ch, char());
			if (cc == '(') {
				lhs >> ch;
				if (!lhs.good()) {
					goto finish;
				}
				cc = ct.narrow(ch, char());
				if (cc == '(') {
					lhs.putback(ch);
					lhs >> u;
					a = u.real();
					b = u.imag();
					if (!lhs.good()) {
						goto finish;
					}
					lhs >> ch;
					if (!lhs.good()) {
						goto finish;
					}
					cc = ct.narrow(ch, char());
					if (cc == ')') {
						rhs = sprout::math::quaternion<T>(a, b);
					} else if (cc == ',') {
						lhs >> v;
						c = v.real();
						d = v.imag();
						if (!lhs.good()) {
							goto finish;
						}
						lhs >> ch;
						if (!lhs.good()) {
							goto finish;
						}
						cc = ct.narrow(ch, char());
						if (cc == ')') {
							rhs = sprout::math::quaternion<T>(a, b, c, d);
						} else {
							lhs.setstate(std::ios_base::failbit);
						}
					} else {
						lhs.setstate(std::ios_base::failbit);
					}
				} else {
					lhs.putback(ch);
					lhs >> a;
					if (!lhs.good()) {
						goto finish;
					}
					lhs >> ch;
					if (!lhs.good()) {
						goto finish;
					}
					cc = ct.narrow(ch, char());
					if (cc == ')') {
						rhs = sprout::math::quaternion<T>(a);
					} else if (cc == ',') {
						lhs >> ch;
						if (!lhs.good()) {
							goto finish;
						}
						cc = ct.narrow(ch, char());
						if (cc == '(') {
							lhs.putback(ch);
							lhs >> v;
							c = v.real();
							d = v.imag();
							if (!lhs.good()) {
								goto finish;
							}
							lhs >> ch;
							if (!lhs.good()) {
								goto finish;
							}
							cc = ct.narrow(ch, char());
							if (cc == ')') {
								rhs = sprout::math::quaternion<T>(a, b, c, d);
							} else {
								lhs.setstate(std::ios_base::failbit);
							}
						} else {
							lhs.putback(ch);
							lhs >> b;
							if (!lhs.good()) {
								goto finish;
							}
							lhs >> ch;
							if (!lhs.good()) {
								goto finish;
							}
							cc = ct.narrow(ch, char());
							if (cc == ')') {
								rhs = sprout::math::quaternion<T>(a, b);
							} else if (cc == ',') {
								lhs >> c;
								if (!lhs.good()) {
									goto finish;
								}
								lhs >> ch;
								if (!lhs.good()) {
									goto finish;
								}
								cc = ct.narrow(ch, char());
								if (cc == ')') {
									rhs = sprout::math::quaternion<T>(a, b, c);
								} else if (cc == ',') {
									lhs >> d;
									if (!lhs.good()) {
										goto finish;
									}
									lhs >> ch;
									if (!lhs.good()) {
										goto finish;
									}
									cc = ct.narrow(ch, char());
									if (cc == ')') {
										rhs = sprout::math::quaternion<T>(a, b, c, d);
									} else {
										lhs.setstate(std::ios_base::failbit);
									}
								} else {
									lhs.setstate(std::ios_base::failbit);
								}
							} else {
								lhs.setstate(std::ios_base::failbit);
							}
						}
					} else {
						lhs.setstate(std::ios_base::failbit);
					}
				}
			} else {
				lhs.putback(ch);
				lhs >> a;
				if (!lhs.good()) {
					goto finish;
				}
				rhs = sprout::math::quaternion<T>(a);
			}
		finish:
			return lhs;
		}
	}	// namespace math
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_QUATERNION_OPERATORS_HPP
