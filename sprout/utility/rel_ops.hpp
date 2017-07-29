/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_REL_OPS_HPP
#define SPROUT_UTILITY_REL_OPS_HPP

#include <sprout/config.hpp>

namespace sprout {
	namespace rel_ops {
		//
		// operator!=
		//
		template<typename T>
		inline SPROUT_CONSTEXPR bool
		operator!=(T const& x, T const& y) {
			return !(x == y);
		}
		//
		// operator>
		//
		template<typename T>
		inline SPROUT_CONSTEXPR bool
		operator>(T const& x, T const& y) {
			return y < x;
		}
		//
		// operator<=
		//
		template<typename T>
		inline SPROUT_CONSTEXPR bool
		operator<=(T const& x, T const& y) {
			return !(y < x);
		}
		//
		// operator>=
		//
		template<typename T>
		inline SPROUT_CONSTEXPR bool
		operator>=(T const& x, T const& y) {
			return !(x < y);
		}
	}	// namespace rel_ops
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_REL_OPS_HPP
