/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_ANY_CONVERTIBLE_HPP
#define SPROUT_UTILITY_ANY_CONVERTIBLE_HPP

#include <sprout/config.hpp>

namespace sprout {
	//
	// any_convertible
	//
	struct any_convertible {
	public:
		template<typename T>
		SPROUT_CONSTEXPR operator T() const {
			return T();
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_ANY_CONVERTIBLE_HPP
