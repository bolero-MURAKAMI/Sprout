/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPOST_UTILITY_EQUAL_TEMPERAMENT_HPP
#define SPROUT_COMPOST_UTILITY_EQUAL_TEMPERAMENT_HPP

#include <sprout/config.hpp>
#include <sprout/math/pow.hpp>
#include <sprout/type_traits/float_promote.hpp>

namespace sprout {
	namespace compost {
		//
		// equal_temperament_value
		//
		template<typename ArithmeticType1, typename ArithmeticType2>
		SPROUT_CONSTEXPR typename sprout::float_promote<ArithmeticType1, ArithmeticType2>::type
		equal_temperament_value(ArithmeticType1 i, ArithmeticType2 div) {
			typedef typename sprout::float_promote<ArithmeticType1, ArithmeticType2>::type type;
			using sprout::pow;
			return pow(type(2), type(i) / type(div));
		}
		template<typename ArithmeticType>
		SPROUT_CONSTEXPR typename sprout::float_promote<ArithmeticType, int>::type
		equal_temperament_value(ArithmeticType i) {
			return sprout::compost::equal_temperament_value(i, 12);
		}
	}	// namespace compost
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPOST_UTILITY_EQUAL_TEMPERAMENT_HPP
