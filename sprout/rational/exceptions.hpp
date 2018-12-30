/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RATIONAL_EXCEPTIONS_HPP
#define SPROUT_RATIONAL_EXCEPTIONS_HPP

#include <stdexcept>
#include <sprout/config.hpp>

namespace sprout {
	//
	// bad_rational
	//
	class bad_rational
		: public std::domain_error
	{
	public:
		explicit bad_rational()
			: std::domain_error("bad rational: zero denominator")
		{}
	};
}	// namespace sprout

#endif	// SPROUT_RATIONAL_EXCEPTIONS_HPP
