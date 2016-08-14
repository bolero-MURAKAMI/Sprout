/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPLEX_LITERALS_HPP
#define SPROUT_COMPLEX_LITERALS_HPP

#include <sprout/config.hpp>
#include <sprout/complex/complex.hpp>
#include <sprout/detail/udl_namespace.hpp>

#if SPROUT_USE_USER_DEFINED_LITERALS

namespace sprout {
	namespace literals {
		namespace complex {
			//
			// _i
			//
			inline SPROUT_CONSTEXPR sprout::complex<double>
			operator"" _i(long double x) {
				return sprout::complex<double>(0, x);
			}

			//
			// _if
			// _iF
			//
			inline SPROUT_CONSTEXPR sprout::complex<float>
			operator"" _if(long double x) {
				return sprout::complex<float>(0, static_cast<float>(x));
			}
			inline SPROUT_CONSTEXPR sprout::complex<float>
			operator"" _iF(long double x) {
				return sprout::complex<float>(0, static_cast<float>(x));
			}

			//
			// _il
			// _iL
			//
			inline SPROUT_CONSTEXPR sprout::complex<long double>
			operator"" _il(long double x) {
				return sprout::complex<long double>(0, x);
			}
			inline SPROUT_CONSTEXPR sprout::complex<long double>
			operator"" _iL(long double x) {
				return sprout::complex<long double>(0, x);
			}
		}	// namespace complex

		using sprout::literals::complex::operator"" _i;
		using sprout::literals::complex::operator"" _if;
		using sprout::literals::complex::operator"" _iF;
		using sprout::literals::complex::operator"" _il;
		using sprout::literals::complex::operator"" _iL;
	}	// namespace literals

	using sprout::literals::complex::operator"" _i;
	using sprout::literals::complex::operator"" _if;
	using sprout::literals::complex::operator"" _iF;
	using sprout::literals::complex::operator"" _il;
	using sprout::literals::complex::operator"" _iL;
}	// namespace sprout

#endif	// #if SPROUT_USE_USER_DEFINED_LITERALS

#endif	// #ifndef SPROUT_COMPLEX_LITERALS_HPP
