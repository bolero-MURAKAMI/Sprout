/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONFIG_COMPILER_INTEL_HPP
#define SPROUT_CONFIG_COMPILER_INTEL_HPP

#include <sprout/config/compiler/common_edg.hpp>

#if defined(__INTEL_COMPILER)
#	define SPROUT_INTEL_CXX_VERSION __INTEL_COMPILER
#elif defined(__ICL)
#	define SPROUT_INTEL_CXX_VERSION __ICL
#elif defined(__ICC)
#	define SPROUT_INTEL_CXX_VERSION __ICC
#elif defined(__ECC)
#	define SPROUT_INTEL_CXX_VERSION __ECC
#endif

#if (!(defined(_WIN32) || defined(_WIN64)) && defined(__STDC_HOSTED__) && (__STDC_HOSTED__ && (SPROUT_INTEL_CXX_VERSION <= 1200))) || defined(__GXX_EXPERIMENTAL_CPP0X__) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#	define SPROUT_INTEL_STDCXX11
#endif
#if defined(_MSC_VER) && (_MSC_VER >= 1600)
#	define SPROUT_INTEL_STDCXX11
#endif

#if defined(SPROUT_INTEL_STDCXX11) && (SPROUT_INTEL_CXX_VERSION >= 1200)
#	undef SPROUT_NO_CXX11_DELETED_FUNCTIONS
#	undef SPROUT_NO_CXX11_DEFAULTED_FUNCTIONS
#endif

#if defined(SPROUT_INTEL_STDCXX11) && (SPROUT_INTEL_CXX_VERSION > 1200)
#	undef SPROUT_NO_CXX11_TEMPLATE_ALIASES
#endif

#if defined(SPROUT_INTEL_STDCXX11) && (SPROUT_INTEL_CXX_VERSION >= 1400) && !defined(_MSC_VER)
#	undef SPROUT_NO_CXX11_UNICODE_LITERALS
#	undef SPROUT_NO_CXX11_CONSTEXPR
#endif

#if defined(_MSC_VER) && (_MSC_VER <= 1700)
#	define SPROUT_NO_CXX11_DELETED_FUNCTIONS
#	define SPROUT_NO_CXX11_DEFAULTED_FUNCTIONS
#	define SPROUT_NO_CXX11_TEMPLATE_ALIASES
#endif

#define SPROUT_WORKAROUND_NO_TEMPLATE_ARGUMENT_DEDUCTION_WITH_ALIASES
#define SPROUT_WORKAROUND_NO_DEFAULT_TEMPLATE_PARAMETERS_SFINAE_WITH_ARRAY

#endif	// #ifndef SPROUT_CONFIG_COMPILER_INTEL_HPP
