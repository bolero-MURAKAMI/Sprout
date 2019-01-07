/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_ATTR_CNV_NEGATE_HPP
#define SPROUT_WEED_ATTR_CNV_NEGATE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/weed/unused.hpp>
#include <sprout/weed/traits/type/is_unused.hpp>
#include <sprout/weed/attr_cnv/results/negate.hpp>

namespace sprout {
	namespace weed {
		namespace attr_cnv {
			//
			// negate
			//
			// !unused -> unused
			template<typename T>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::weed::traits::is_unused<T>::value,
				typename sprout::weed::attr_cnv::results::negate<T>::type
			>::type negate(T const&, bool) {
				return sprout::weed::unused();
			}
		}	// namespace attr_cnv
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_ATTR_CNV_NEGATE_HPP
