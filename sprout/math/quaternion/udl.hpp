/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_QUATERNION_UDL_HPP
#define SPROUT_MATH_QUATERNION_UDL_HPP

#include <sprout/config.hpp>
#include <sprout/complex/udl.hpp>
#include <sprout/math/quaternion/quaternion.hpp>

#if SPROUT_USE_USER_DEFINED_LITERALS

namespace sprout {
	namespace udl {
		namespace quaternion {
			using sprout::udl::complex::operator"" _i;
			using sprout::udl::complex::operator"" _if;
			using sprout::udl::complex::operator"" _iF;
			using sprout::udl::complex::operator"" _il;
			using sprout::udl::complex::operator"" _iL;

			//
			// _j
			//
			inline SPROUT_CONSTEXPR sprout::math::quaternion<double>
			operator"" _j(long double x) {
				return sprout::math::quaternion<double>(0, 0, x);
			}

			//
			// _jf
			// _jF
			//
			inline SPROUT_CONSTEXPR sprout::math::quaternion<float>
			operator"" _jf(long double x) {
				return sprout::math::quaternion<float>(0, 0, static_cast<float>(x));
			}
			inline SPROUT_CONSTEXPR sprout::math::quaternion<float>
			operator"" _jF(long double x) {
				return sprout::math::quaternion<float>(0, 0, static_cast<float>(x));
			}

			//
			// _jl
			// _jL
			//
			inline SPROUT_CONSTEXPR sprout::math::quaternion<long double>
			operator"" _jl(long double x) {
				return sprout::math::quaternion<long double>(0, 0, x);
			}
			inline SPROUT_CONSTEXPR sprout::math::quaternion<long double>
			operator"" _jL(long double x) {
				return sprout::math::quaternion<long double>(0, 0, x);
			}

			//
			// _k
			//
			inline SPROUT_CONSTEXPR sprout::math::quaternion<double>
			operator"" _k(long double x) {
				return sprout::math::quaternion<double>(0, 0, 0, x);
			}

			//
			// _kf
			// _kF
			//
			inline SPROUT_CONSTEXPR sprout::math::quaternion<float>
			operator"" _kf(long double x) {
				return sprout::math::quaternion<float>(0, 0, 0, static_cast<float>(x));
			}
			inline SPROUT_CONSTEXPR sprout::math::quaternion<float>
			operator"" _kF(long double x) {
				return sprout::math::quaternion<float>(0, 0, 0, static_cast<float>(x));
			}

			//
			// _kl
			// _kL
			//
			inline SPROUT_CONSTEXPR sprout::math::quaternion<long double>
			operator"" _kl(long double x) {
				return sprout::math::quaternion<long double>(0, 0, 0, x);
			}
			inline SPROUT_CONSTEXPR sprout::math::quaternion<long double>
			operator"" _kL(long double x) {
				return sprout::math::quaternion<long double>(0, 0, 0, x);
			}
		}	// namespace quaternion

		using sprout::udl::quaternion::operator"" _j;
		using sprout::udl::quaternion::operator"" _jf;
		using sprout::udl::quaternion::operator"" _jF;
		using sprout::udl::quaternion::operator"" _jl;
		using sprout::udl::quaternion::operator"" _jL;

		using sprout::udl::quaternion::operator"" _k;
		using sprout::udl::quaternion::operator"" _kf;
		using sprout::udl::quaternion::operator"" _kF;
		using sprout::udl::quaternion::operator"" _kl;
		using sprout::udl::quaternion::operator"" _kL;
	}	// namespace udl

	using sprout::udl::quaternion::operator"" _j;
	using sprout::udl::quaternion::operator"" _jf;
	using sprout::udl::quaternion::operator"" _jF;
	using sprout::udl::quaternion::operator"" _jl;
	using sprout::udl::quaternion::operator"" _jL;

	using sprout::udl::quaternion::operator"" _k;
	using sprout::udl::quaternion::operator"" _kf;
	using sprout::udl::quaternion::operator"" _kF;
	using sprout::udl::quaternion::operator"" _kl;
	using sprout::udl::quaternion::operator"" _kL;
}	// namespace sprout

#endif	// #if SPROUT_USE_USER_DEFINED_LITERALS

#endif	// #ifndef SPROUT_MATH_QUATERNION_UDL_HPP
