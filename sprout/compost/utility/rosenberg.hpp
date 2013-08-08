/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPOST_UTILITY_ROSENBERG_HPP
#define SPROUT_COMPOST_UTILITY_ROSENBERG_HPP

#include <sprout/config.hpp>
#include <sprout/detail/pow.hpp>
#include <sprout/type_traits/float_promote.hpp>
#include <sprout/math/comparison.hpp>

namespace sprout {
	namespace compost {
		//
		// rosenberg_value
		//	Rosenberg 波は，声門開大期と閉小期が周期の40%，16%となる非対称形の波形であり，τ1 が開大期，τ2が閉小期を示す．
		//
		template<typename T>
		inline SPROUT_CONSTEXPR typename sprout::float_promote<T>::type
		rosenberg_value(T x, T tau1, T tau2) {
			typedef typename sprout::float_promote<T>::type type;
			return x >= 0 && x <= tau1
					? 3 * sprout::detail::pow2<type>(x / tau1) - 2 * sprout::detail::pow3<type>(x / tau1)
				: x > tau1 && x <= tau1 + tau2
					? 1 - sprout::detail::pow2<type>((x - tau1) / tau2)
				: 0
				;
		}
	}	// namespace compost
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPOST_UTILITY_ROSENBERG_HPP
