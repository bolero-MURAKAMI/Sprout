/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONFIG_COMPILER_NO_FUTURE_HPP
#define SPROUT_CONFIG_COMPILER_NO_FUTURE_HPP

#ifdef SPROUT_NO_CXX11_CONSTEXPR
#	define SPROUT_NO_CONSTEXPR
#endif
#ifdef SPROUT_NO_CXX11_DEFAULTED_FUNCTIONS
#	define SPROUT_NO_DEFAULTED_FUNCTIONS
#endif
#ifdef SPROUT_NO_CXX11_DELETED_FUNCTIONS
#	define SPROUT_NO_DELETED_FUNCTIONS
#endif
#ifdef SPROUT_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#	define SPROUT_NO_EXPLICIT_CONVERSION_OPERATORS
#endif
#ifdef SPROUT_NO_CXX11_NOEXCEPT
#	define SPROUT_NO_NOEXCEPT
#endif
#ifdef SPROUT_NO_CXX11_TEMPLATE_ALIASES
#	define SPROUT_NO_TEMPLATE_ALIASES
#endif
#ifdef SPROUT_NO_CXX11_USER_DEFINED_LITERALS
#	define SPROUT_NO_USER_DEFINED_LITERALS
#endif
#ifdef SPROUT_NO_CXX11_DELEGATING_CONSTRUCTORS
#	define SPROUT_NO_DELEGATING_CONSTRUCTORS
#endif
#ifdef SPROUT_NO_CXX11_UNICODE_LITERALS
#	define SPROUT_NO_UNICODE_LITERALS
#endif
#ifdef SPROUT_NO_CXX11_ATTRIBUTES
#	define SPROUT_NO_ATTRIBUTES
#endif

#ifdef SPROUT_NO_CXX14_VARIABLE_TEMPLATES
#	define SPROUT_NO_VARIABLE_TEMPLATES
#endif

#endif	// #ifndef SPROUT_CONFIG_COMPILER_NO_FUTURE_HPP
