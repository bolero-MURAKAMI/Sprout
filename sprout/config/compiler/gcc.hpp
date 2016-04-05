/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONFIG_COMPILER_GCC_HPP
#define SPROUT_CONFIG_COMPILER_GCC_HPP

#if defined(__GXX_EXPERIMENTAL_CXX0X__) || (__cplusplus >= 201103L)
#	define SPROUT_GCC_CXX11
#endif

#if (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 6) || !defined(SPROUT_GCC_CXX11))
#	define SPROUT_NO_CXX11_CONSTEXPR
#endif

#if (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 4) || !defined(SPROUT_GCC_CXX11))
#	define SPROUT_NO_CXX11_DEFAULTED_FUNCTIONS
#endif

#if (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 4) || !defined(SPROUT_GCC_CXX11))
#	define SPROUT_NO_CXX11_DELETED_FUNCTIONS
#endif

#if (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 5) || !defined(SPROUT_GCC_CXX11))
#	define SPROUT_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#endif

#if (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 6) || !defined(SPROUT_GCC_CXX11))
#	define SPROUT_NO_CXX11_NOEXCEPT
#endif

#if (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 7) || !defined(SPROUT_GCC_CXX11))
#	define SPROUT_NO_CXX11_TEMPLATE_ALIASES
#endif

#if (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 7) || !defined(SPROUT_GCC_CXX11))
#	define SPROUT_NO_CXX11_USER_DEFINED_LITERALS
#endif

#if (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 7) || !defined(SPROUT_GCC_CXX11))
#	define SPROUT_NO_CXX11_DELEGATING_CONSTRUCTORS
#endif

#if (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 5) || !defined(SPROUT_GCC_CXX11))
#	define SPROUT_NO_CXX11_UNICODE_LITERALS
#endif

#if ((__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 8)) && defined(SPROUT_GCC_CXX11))
#	define SPROUT_NO_CXX11_ATTRIBUTES
#endif

#if ((__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)) && defined(SPROUT_GCC_CXX11))
#	define SPROUT_HAS_CONSTEXPR_CMATH_FUNCTION
#endif

#if ((__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)) && defined(SPROUT_GCC_CXX11))
#	define SPROUT_HAS_CONSTEXPR_COPYSIGN_FUNCTION
#endif

#if ((__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)) && defined(SPROUT_GCC_CXX11))
#	define SPROUT_HAS_CONSTEXPR_BIT_OPERATION
#endif

#if !defined(__cpp_constexpr) || (__cpp_constexpr < 201304)
#	define SPROUT_NO_CXX14_CONSTEXPR
#endif

#if !defined(__cpp_variable_templates) || (__cpp_variable_templates < 201304)
#	define SPROUT_NO_CXX14_VARIABLE_TEMPLATES
#endif

#endif	// #ifndef SPROUT_CONFIG_COMPILER_GCC_HPP
