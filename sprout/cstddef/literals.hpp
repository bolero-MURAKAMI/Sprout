/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CSTDDEF_LITERALS_HPP
#define SPROUT_CSTDDEF_LITERALS_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/detail/udl_namespace.hpp>

#if SPROUT_USE_USER_DEFINED_LITERALS

namespace sprout {
	namespace literals {
		namespace support_literals {
			//
			// operator"" _zu
			//
			SPROUT_CONSTEXPR std::size_t operator"" _zu(unsigned long long t) {
				return static_cast<std::size_t>(t);
			}
		}	// namespace support_literals

		using sprout::literals::support_literals::operator"" _zu;
	}	// namespace literals
}	// namespace sprout

#endif	// #if SPROUT_USE_USER_DEFINED_LITERALS

#endif	// #ifndef SPROUT_CSTDDEF_LITERALS_HPP
