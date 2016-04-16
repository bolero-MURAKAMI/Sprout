/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DETAIL_DO_NOTHING_STATEMENT_WITHIN_NAMESPACE_HPP
#define SPROUT_DETAIL_DO_NOTHING_STATEMENT_WITHIN_NAMESPACE_HPP

#include <sprout/config.hpp>

namespace sprout_detail_do_nothing_statement {}

//
// SPROUT_DETAIL_DO_NOTHING_STATEMENT_WITHIN_NAMESPACE
//
#define SPROUT_DETAIL_DO_NOTHING_STATEMENT_WITHIN_NAMESPACE \
	using namespace sprout_detail_do_nothing_statement

#endif	// #ifndef SPROUT_DETAIL_DO_NOTHING_STATEMENT_WITHIN_NAMESPACE_HPP
