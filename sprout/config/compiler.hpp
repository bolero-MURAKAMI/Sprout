/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONFIG_COMPILER_HPP
#define SPROUT_CONFIG_COMPILER_HPP

#if defined(__GCCXML__)
#	include <sprout/config/compiler/gcc_xml.hpp>
#elif defined(_CRAYC)
#	include <sprout/config/compiler/cray.hpp>
#elif defined(__CUDACC__)
#	include <sprout/config/compiler/nvcc.hpp>
#elif defined(__COMO__)
#	include <sprout/config/compiler/comeau.hpp>
#elif defined(__PATHSCALE__) && (__PATHCC__ >= 4)
#	include <sprout/config/compiler/pathscale.hpp>
#elif defined(__clang__)
#	include <sprout/config/compiler/clang.hpp>
#elif defined(__DMC__)
#	include <sprout/config/compiler/digitalmars.hpp>
#elif defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)
#	include <sprout/config/compiler/intel.hpp>
# elif defined(__GNUC__)
#	include <sprout/config/compiler/gcc.hpp>
#elif defined(__KCC)
#	include <sprout/config/compiler/kai.hpp>
#elif defined(__sgi)
#	include <sprout/config/compiler/sgi_mipspro.hpp>
#elif defined(__DECCXX)
#	include <sprout/config/compiler/compaq_cxx.hpp>
#elif defined(__ghs)
#	include <sprout/config/compiler/greenhills.hpp>
#elif defined(__CODEGEARC__)
#	include <sprout/config/compiler/codegear.hpp>
#elif defined(__BORLANDC__)
#	include <sprout/config/compiler/borland.hpp>
#elif defined(__MWERKS__)
#	include <sprout/config/compiler/metrowerks.hpp>
#elif defined(__SUNPRO_CC)
#	include <sprout/config/compiler/sunpro_cc.hpp>
#elif defined(__HP_aCC)
#	include <sprout/config/compiler/hp_acc.hpp>
#elif defined(__MRC__) || defined(__SC__)
#	include <sprout/config/compiler/mpw.hpp>
#elif defined(__IBMCPP__)
#	include <sprout/config/compiler/vacpp.hpp>
#elif defined(__PGI)
#	include <sprout/config/compiler/pgi.hpp>
#elif defined(_MSC_VER)
#	include <sprout/config/compiler/visualc.hpp>
#endif

#include <sprout/config/compiler/no_future.hpp>
#include <sprout/config/compiler/has_future.hpp>

#endif	// #ifndef SPROUT_CONFIG_COMPILER_HPP
