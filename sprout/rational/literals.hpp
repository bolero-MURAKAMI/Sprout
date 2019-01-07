/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RATIONAL_LITERALS_HPP
#define SPROUT_RATIONAL_LITERALS_HPP

#include <sprout/config.hpp>
#include <sprout/rational/rational.hpp>
#include <sprout/detail/udl_namespace.hpp>

#if SPROUT_USE_USER_DEFINED_LITERALS

namespace sprout {
	namespace literals {
		namespace rational {
			//
			// _r
			//
			inline SPROUT_CONSTEXPR sprout::rational<int>
			operator"" _r(unsigned long long x) {
				return sprout::rational<int>(static_cast<int>(x));
			}

			//
			// _rl
			// _rL
			//
			inline SPROUT_CONSTEXPR sprout::rational<long>
			operator"" _rl(unsigned long long x) {
				return sprout::rational<long>(static_cast<long>(x));
			}
			inline SPROUT_CONSTEXPR sprout::rational<long>
			operator"" _rL(unsigned long long x) {
				return sprout::rational<long>(static_cast<long>(x));
			}

			//
			// _rll
			// _rLL
			//
			inline SPROUT_CONSTEXPR sprout::rational<long long>
			operator"" _rll(unsigned long long x) {
				return sprout::rational<long long>(x);
			}
			inline SPROUT_CONSTEXPR sprout::rational<long long>
			operator"" _rLL(unsigned long long x) {
				return sprout::rational<long long>(x);
			}
		}	// namespace rational

		using sprout::literals::rational::operator"" _r;
		using sprout::literals::rational::operator"" _rl;
		using sprout::literals::rational::operator"" _rL;
		using sprout::literals::rational::operator"" _rll;
		using sprout::literals::rational::operator"" _rLL;
	}	// namespace literals

	using sprout::literals::rational::operator"" _r;
	using sprout::literals::rational::operator"" _rl;
	using sprout::literals::rational::operator"" _rL;
	using sprout::literals::rational::operator"" _rll;
	using sprout::literals::rational::operator"" _rLL;
}	// namespace sprout

#endif	// #if SPROUT_USE_USER_DEFINED_LITERALS

#endif	// #ifndef SPROUT_RATIONAL_LITERALS_HPP
