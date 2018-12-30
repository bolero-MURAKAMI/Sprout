/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_OPTIONAL_EXCEPTIONS_HPP
#define SPROUT_OPTIONAL_EXCEPTIONS_HPP

#include <string>
#include <stdexcept>
#include <sprout/config.hpp>

namespace sprout {
	//
	// bad_optional_access
	//
	class bad_optional_access
		: public std::logic_error
	{
	public:
		explicit bad_optional_access(std::string const& what_arg)
			: std::logic_error(what_arg)
		{}
		explicit bad_optional_access(char const* what_arg)
			: std::logic_error(what_arg)
		{}
	};
}	// namespace sprout

#endif	// SPROUT_OPTIONAL_EXCEPTIONS_HPP
