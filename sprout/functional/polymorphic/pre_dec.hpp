/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_PRE_DEC_HPP
#define SPROUT_FUNCTIONAL_POLYMORPHIC_PRE_DEC_HPP

#include <sprout/config.hpp>
#include <sprout/functional/pre_dec.hpp>

namespace sprout {
	//
	// pre_dec_t
	// pre_dec_
	//
	typedef sprout::pre_dec<> pre_dec_t;
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::pre_dec_t pre_dec_ = {};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_PRE_DEC_HPP
