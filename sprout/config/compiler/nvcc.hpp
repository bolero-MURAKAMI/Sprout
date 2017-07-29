/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONFIG_COMPILER_NVCC_HPP
#define SPROUT_CONFIG_COMPILER_NVCC_HPP

#if defined(__GNUC__)
#	include <sprout/config/compiler/gcc.hpp>
#elif defined(_MSC_VER)
#	include <sprout/config/compiler/visualc.hpp>
#endif

#endif	// #ifndef SPROUT_CONFIG_COMPILER_NVCC_HPP
