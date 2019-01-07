/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONFIG_COMPILER_HAS_FUTURE_HPP
#define SPROUT_CONFIG_COMPILER_HAS_FUTURE_HPP

#ifndef SPROUT_NO_CXX11_CONSTEXPR
#	define SPROUT_HAS_CONSTEXPR
#endif
#ifndef SPROUT_NO_CXX11_DEFAULTED_FUNCTIONS
#	define SPROUT_HAS_DEFAULTED_FUNCTIONS
#endif
#ifndef SPROUT_NO_CXX11_DELETED_FUNCTIONS
#	define SPROUT_HAS_DELETED_FUNCTIONS
#endif
#ifndef SPROUT_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#	define SPROUT_HAS_EXPLICIT_CONVERSION_OPERATORS
#endif
#ifndef SPROUT_NO_CXX11_NOEXCEPT
#	define SPROUT_HAS_NOEXCEPT
#endif
#ifndef SPROUT_NO_CXX11_TEMPLATE_ALIASES
#	define SPROUT_HAS_TEMPLATE_ALIASES
#endif
#ifndef SPROUT_NO_CXX11_USER_DEFINED_LITERALS
#	define SPROUT_HAS_USER_DEFINED_LITERALS
#endif
#ifndef SPROUT_NO_CXX11_DELEGATING_CONSTRUCTORS
#	define SPROUT_HAS_DELEGATING_CONSTRUCTORS
#endif
#ifndef SPROUT_NO_CXX11_UNICODE_LITERALS
#	define SPROUT_HAS_UNICODE_LITERALS
#endif
#ifndef SPROUT_NO_CXX11_ATTRIBUTES
#	define SPROUT_HAS_ATTRIBUTES
#endif

#ifndef SPROUT_NO_CXX14_VARIABLE_TEMPLATES
#	define SPROUT_HAS_VARIABLE_TEMPLATES
#endif

#endif	// #ifndef SPROUT_CONFIG_COMPILER_HAS_FUTURE_HPP
