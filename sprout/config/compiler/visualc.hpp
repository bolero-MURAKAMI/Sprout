/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONFIG_COMPILER_VISUALC_HPP
#define SPROUT_CONFIG_COMPILER_VISUALC_HPP

#define SPROUT_NO_CXX11_CONSTEXPR
#define SPROUT_NO_CXX11_DEFAULTED_FUNCTIONS
#define SPROUT_NO_CXX11_DELETED_FUNCTIONS
#if _MSC_FULL_VER < 170051025 || !defined(SPROUT_MSVC_ENABLE_2012_NOV_CTP)
#	define SPROUT_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#endif
#define SPROUT_NO_CXX11_NOEXCEPT
#define SPROUT_NO_CXX11_TEMPLATE_ALIASES
#define SPROUT_NO_CXX11_USER_DEFINED_LITERALS
#define SPROUT_NO_CXX11_DELEGATING_CONSTRUCTORS
#define SPROUT_NO_CXX11_UNICODE_LITERALS

#define SPROUT_NO_CXX14_CONSTEXPR

#endif	// #ifndef SPROUT_CONFIG_COMPILER_VISUALC_HPP
