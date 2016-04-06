/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_DETAIL_HAS_SUBSCRIPT_OP_HPP
#define SPROUT_TYPE_TRAITS_DETAIL_HAS_SUBSCRIPT_OP_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/detail/has_binary_op.hpp>

#define SPROUT_DETAIL_HAS_OP_SUBSCRIPT_EXPR(OP, LHS, RHS) \
	LHS[RHS]

#define SPROUT_DETAIL_HAS_SUBSCRIPT_OP_DECL(OP_NAME, OP, RHS_DEFAULT) \
	SPROUT_DETAIL_HAS_BINARY_OP_DECL_(OP_NAME, OP, RHS_DEFAULT, SPROUT_DETAIL_HAS_OP_SUBSCRIPT_EXPR)


#endif	// #ifndef SPROUT_TYPE_TRAITS_DETAIL_HAS_SUBSCRIPT_OP_HPP
