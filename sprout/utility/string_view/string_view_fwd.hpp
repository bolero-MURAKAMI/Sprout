/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_STRING_VIEW_STRING_VIEW_FWD_HPP
#define SPROUT_UTILITY_STRING_VIEW_STRING_VIEW_FWD_HPP

#include <sprout/config.hpp>
#include <sprout/string/char_traits.hpp>

namespace sprout {
	//
	// basic_string_view
	//
	template<typename T, typename Traits = sprout::char_traits<T> >
	class basic_string_view;
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_STRING_VIEW_STRING_VIEW_FWD_HPP
