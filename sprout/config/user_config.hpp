/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONFIG_USER_CONFIG_HPP
#define SPROUT_CONFIG_USER_CONFIG_HPP

//
// Configuration to disable the language features
//
//	If the user does not define, automatically defined according to the compiler.
//
//#define SPROUT_CONFIG_DISABLE_CONSTEXPR
//#define SPROUT_CONFIG_DISABLE_CXX14_CONSTEXPR
//#define SPROUT_CONFIG_DISABLE_DEFAULTED_FUNCTIONS
//#define SPROUT_CONFIG_DISABLE_DELETED_FUNCTIONS
//#define SPROUT_CONFIG_DISABLE_EXPLICIT_CONVERSION_OPERATORS
//#define SPROUT_CONFIG_DISABLE_NOEXCEPT
//#define SPROUT_CONFIG_DISABLE_TEMPLATE_ALIASES
//#define SPROUT_CONFIG_DISABLE_USER_DEFINED_LITERALS
//#define SPROUT_CONFIG_DISABLE_DELEGATING_CONSTRUCTORS
//#define SPROUT_CONFIG_DISABLE_UNICODE_LITERALS
//#define SPROUT_CONFIG_DISABLE_VARIABLE_TEMPLATES

//
// Configuration to forcibly enable the language features
//
//	Suppress the automatic definition: SPROUT_CONFIG_DISABLE_***
//	If a user definition is, invalidation is priority. (SPROUT_CONFIG_DISABLE_***)
//
//#define SPROUT_CONFIG_FORCE_CONSTEXPR
//#define SPROUT_CONFIG_FORCE_CXX14_CONSTEXPR
//#define SPROUT_CONFIG_FORCE_DEFAULTED_FUNCTIONS
//#define SPROUT_CONFIG_FORCE_DELETED_FUNCTIONS
//#define SPROUT_CONFIG_FORCE_EXPLICIT_CONVERSION_OPERATORS
//#define SPROUT_CONFIG_FORCE_NOEXCEPT
//#define SPROUT_CONFIG_FORCE_TEMPLATE_ALIASES
//#define SPROUT_CONFIG_FORCE_USER_DEFINED_LITERALS
//#define SPROUT_CONFIG_FORCE_DELEGATING_CONSTRUCTORS
//#define SPROUT_CONFIG_FORCE_UNICODE_LITERALS
//#define SPROUT_CONFIG_FORCE_VARIABLE_TEMPLATES

//
// Configuration you want to use an external library to implementation
//
//#define SPROUT_CONFIG_USE_SSCRISK_CEL

//
// Configuration to disable the function of the compiler
//
//	If the user does not define, automatically defined according to the compiler.
//
//#define SPROUT_CONFIG_DISABLE_BUILTIN_CMATH_FUNCTION
//#define SPROUT_CONFIG_DISABLE_BUILTIN_COPYSIGN_FUNCTION
//#define SPROUT_CONFIG_DISABLE_BUILTIN_BIT_OPERATION

//
// Configuration to switch the implementation details
//
//#define SPROUT_CONFIG_DISABLE_LARGE_FLOAT_ROUNDING
//#define SPROUT_CONFIG_DISABLE_SUPPORT_TEMPORARY_CONTAINER_ITERATION
//#define SPROUT_CONFIG_DISABLE_SUPPORT_EFFICIENT_ARRAY_ITERATION

//#define SPROUT_CONFIG_DISABLE_USER_CONFIG
//#define SPROUT_CONFIG_DISABLE_AUTO_CONFIG

#endif	// #ifndef SPROUT_CONFIG_USER_CONFIG_HPP
