/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_QUATERNION_STREAM_OPERATORS_HPP
#define SPROUT_MATH_QUATERNION_STREAM_OPERATORS_HPP

#include <iosfwd>
#include <sstream>
#include <locale>
#include <sprout/config.hpp>
#include <sprout/math/quaternion/quaternion.hpp>

namespace sprout {
	namespace math {
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

#endif	// #ifndef SPROUT_MATH_QUATERNION_STREAM_OPERATORS_HPP
