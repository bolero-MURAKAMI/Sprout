/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_INTEGER_LIMITED_HPP
#define SPROUT_INTEGER_LIMITED_HPP

#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/type_traits/arithmetic_promote.hpp>

namespace sprout {
	namespace limited {
		//
		// plus
		//
		template<typename T, typename U>
		inline SPROUT_CONSTEXPR typename sprout::arithmetic_promote<T, U>::type
		plus(T const& lhs, U const& rhs) {
			typedef typename sprout::arithmetic_promote<T, U>::type type;
			return lhs > 0 && rhs > 0 && sprout::numeric_limits<type>::max() - lhs < rhs
					? sprout::numeric_limits<type>::max()
				: lhs < 0 && rhs < 0 && sprout::numeric_limits<type>::min() - lhs > rhs
					? sprout::numeric_limits<type>::min()
				: lhs + rhs
				;
		}

		//
		// multiplies
		//
		template<typename T, typename U>
		inline SPROUT_CONSTEXPR typename sprout::arithmetic_promote<T, U>::type
		multiplies(T const& lhs, U const& rhs) {
			typedef typename sprout::arithmetic_promote<T, U>::type type;
			return lhs > 0 && rhs > 0 && sprout::numeric_limits<type>::max() / lhs + (sprout::numeric_limits<type>::max() % lhs ? 1 : 0) <= rhs
					? sprout::numeric_limits<type>::max()
				: lhs > 0 && rhs < 0 && sprout::numeric_limits<type>::min() / rhs + (sprout::numeric_limits<type>::min() % rhs ? 1 : 0) <= lhs
					? sprout::numeric_limits<type>::min()
				: lhs < 0 && rhs > 0 && sprout::numeric_limits<type>::min() / lhs + (sprout::numeric_limits<type>::min() % lhs ? 1 : 0) <= rhs
					? sprout::numeric_limits<type>::min()
				: lhs < 0 && rhs < 0 && -(sprout::numeric_limits<type>::min() / rhs + (sprout::numeric_limits<type>::min() % rhs ? 1 : 0)) >= lhs
					? sprout::numeric_limits<type>::max()
				: lhs * rhs
				;
		}
	}	// namespace limited
}	// namespace sprout

#endif	// #ifndef SPROUT_INTEGER_LIMITED_HPP
