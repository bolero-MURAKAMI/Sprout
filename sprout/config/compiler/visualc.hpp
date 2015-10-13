/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONFIG_COMPILER_VISUALC_HPP
#define SPROUT_CONFIG_COMPILER_VISUALC_HPP

#define SPROUT_NO_CXX11_CONSTEXPR
#if _MSC_FULL_VER < 180020827
#	define SPROUT_NO_CXX11_DEFAULTED_FUNCTIONS
#	define SPROUT_NO_CXX11_DELETED_FUNCTIONS
#	define SPROUT_NO_CXX11_TEMPLATE_ALIASES
#	define SPROUT_NO_CXX11_DELEGATING_CONSTRUCTORS
#endif
#if _MSC_FULL_VER < 170051025 || !defined(SPROUT_MSVC_ENABLE_2012_NOV_CTP)
#	define SPROUT_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#endif
#if _MSC_FULL_VER < 190023026
#	define SPROUT_NO_CXX11_NOEXCEPT
#	define SPROUT_NO_CXX11_USER_DEFINED_LITERALS
#	define SPROUT_NO_CXX11_UNICODE_LITERALS
#endif
#define SPROUT_NO_CXX11_ATTRIBUTES

#if !defined(__cpp_constexpr) || (__cpp_constexpr < 201304)
#  define SPROUT_NO_CXX14_CONSTEXPR
#endif
#if !defined(__cpp_variable_templates) || (__cpp_variable_templates < 201304)
#  define SPROUT_NO_CXX14_VARIABLE_TEMPLATES
#endif

#endif	// #ifndef SPROUT_CONFIG_COMPILER_VISUALC_HPP
