/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CURRENT_FUNCTION_HPP
#define SPROUT_CURRENT_FUNCTION_HPP

#include <sprout/config.hpp>

namespace sprout {
	namespace detail {
		inline void
		current_function_helper() {
#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)

#	define SPROUT_CURRENT_FUNCTION __PRETTY_FUNCTION__

#elif defined(__DMC__) && (__DMC__ >= 0x810)

#	define SPROUT_CURRENT_FUNCTION __PRETTY_FUNCTION__

#elif defined(__FUNCSIG__)

#	define SPROUT_CURRENT_FUNCTION __FUNCSIG__

#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))

#	define SPROUT_CURRENT_FUNCTION __FUNCTION__

#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)

#	define SPROUT_CURRENT_FUNCTION __FUNC__

#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)

#	define SPROUT_CURRENT_FUNCTION __func__

#else

#	define SPROUT_CURRENT_FUNCTION "(unknown)"

#endif
		}
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_CURRENT_FUNCTION_HPP
