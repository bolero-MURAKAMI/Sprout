#ifndef SPROUT_RATIONAL_UDL_HPP
#define SPROUT_RATIONAL_UDL_HPP

#include <sprout/config.hpp>
#include <sprout/rational/rational.hpp>

#if SPROUT_USE_USER_DEFINED_LITERALS

namespace sprout {
	namespace udl {
		namespace rational {
			//
			// _r
			//
			inline SPROUT_CONSTEXPR sprout::rational<int>
			operator"" _r(unsigned long long x) {
				return sprout::rational<int>(x);
			}

			//
			// _rl
			// _rL
			//
			inline SPROUT_CONSTEXPR sprout::rational<long>
			operator"" _rl(unsigned long long x) {
				return sprout::rational<long>(x);
			}
			inline SPROUT_CONSTEXPR sprout::rational<long>
			operator"" _rL(unsigned long long x) {
				return sprout::rational<long>(x);
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

		using sprout::udl::rational::operator"" _r;
		using sprout::udl::rational::operator"" _rl;
		using sprout::udl::rational::operator"" _rL;
		using sprout::udl::rational::operator"" _rll;
		using sprout::udl::rational::operator"" _rLL;
	}	// namespace udl

	using sprout::udl::rational::operator"" _r;
	using sprout::udl::rational::operator"" _rl;
	using sprout::udl::rational::operator"" _rL;
	using sprout::udl::rational::operator"" _rll;
	using sprout::udl::rational::operator"" _rLL;
}	// namespace sprout

#endif	// #if SPROUT_USE_USER_DEFINED_LITERALS

#endif	// #ifndef SPROUT_RATIONAL_UDL_HPP
