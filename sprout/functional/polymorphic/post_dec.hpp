/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_POST_DEC_HPP
#define SPROUT_FUNCTIONAL_POLYMORPHIC_POST_DEC_HPP

#include <sprout/config.hpp>
#include <sprout/functional/post_dec.hpp>

namespace sprout {
	//
	// post_dec_t
	// post_dec_
	//
	typedef sprout::post_dec<> post_dec_t;
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::post_dec_t post_dec_ = {};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_POST_DEC_HPP
