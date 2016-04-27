/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_GENERATOR_TRAITS_FWD_HPP
#define SPROUT_GENERATOR_TRAITS_FWD_HPP

#include <sprout/config.hpp>

namespace sprout {
	namespace generators {
		//
		// generator_access_traits
		//
		template<typename Gen>
		struct generator_access_traits;
	}	// namespace generators

	using sprout::generators::generator_access_traits;
}	// namespace sprout

#endif	// #ifndef SPROUT_GENERATOR_TRAITS_FWD_HPP
