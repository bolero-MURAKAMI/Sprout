/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WORKAROUND_DETAIL_UNIFORM_INT_DISTRIBUTION_HPP
#define SPROUT_WORKAROUND_DETAIL_UNIFORM_INT_DISTRIBUTION_HPP

#include <sprout/config.hpp>

#ifdef SPROUT_WORKAROUND_NOT_TERMINATE_RECURSIVE_CONSTEXPR_FUNCTION_TEMPLATE
#	include <sprout/random/uniform_smallint.hpp>
#	define SPROUT_WORKAROUND_DETAIL_UNIFORM_INT_DISTRIBUTION sprout::random::uniform_smallint
#else
#	include <sprout/random/uniform_int_distribution.hpp>
#	define SPROUT_WORKAROUND_DETAIL_UNIFORM_INT_DISTRIBUTION sprout::random::uniform_int_distribution
#endif

#endif	// #ifndef SPROUT_WORKAROUND_DETAIL_UNIFORM_INT_DISTRIBUTION_HPP
