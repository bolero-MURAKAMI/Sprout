/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPLEX_UDL_HPP
#define SPROUT_COMPLEX_UDL_HPP

#include <sprout/config.hpp>
#include <sprout/complex/complex.hpp>

#if SPROUT_USE_USER_DEFINED_LITERALS

namespace sprout {
	namespace udl {
		namespace complex {
			//
			// _i
			//
			inline SPROUT_CONSTEXPR sprout::complex<double>
			operator"" _i(long double x) {
				return sprout::complex<double>(0, x);
			}

			//
			// _i_f
			// _i_F
			//
			inline SPROUT_CONSTEXPR sprout::complex<float>
			operator"" _i_f(long double x) {
				return sprout::complex<float>(0, x);
			}
			inline SPROUT_CONSTEXPR sprout::complex<float>
			operator"" _i_F(long double x) {
				return sprout::complex<float>(0, x);
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

		using sprout::udl::complex::operator"" _i;
		using sprout::udl::complex::operator"" _i_f;
		using sprout::udl::complex::operator"" _i_F;
		using sprout::udl::complex::operator"" _il;
		using sprout::udl::complex::operator"" _iL;
	}	// namespace udl

	using sprout::udl::complex::operator"" _i;
	using sprout::udl::complex::operator"" _i_f;
	using sprout::udl::complex::operator"" _i_F;
	using sprout::udl::complex::operator"" _il;
	using sprout::udl::complex::operator"" _iL;
}	// namespace sprout

#endif	// #if SPROUT_USE_USER_DEFINED_LITERALS

#endif	// #ifndef SPROUT_COMPLEX_UDL_HPP
