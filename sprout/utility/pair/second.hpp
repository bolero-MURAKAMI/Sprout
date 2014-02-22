/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_PAIR_SECOND_HPP
#define SPROUT_UTILITY_PAIR_SECOND_HPP

#include <sprout/config.hpp>
#include <sprout/tuple/tuple/get.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/pair/tuple.hpp>

namespace sprout {
	//
	// second
	//
	template<typename T>
	inline SPROUT_CONSTEXPR auto
	second(T&& t)
	SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::tuples::get<1>(SPROUT_FORWARD(T, t))))
	-> decltype(sprout::tuples::get<1>(SPROUT_FORWARD(T, t)))
	{
		return sprout::tuples::get<1>(SPROUT_FORWARD(T, t));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_PAIR_SECOND_HPP
