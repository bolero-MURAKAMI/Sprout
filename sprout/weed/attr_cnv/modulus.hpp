/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_ATTR_CNV_MODULUS_HPP
#define SPROUT_WEED_ATTR_CNV_MODULUS_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/weed/attr_cnv/results/modulus.hpp>
#include <sprout/weed/attr_cnv/times.hpp>

namespace sprout {
	namespace weed {
		namespace attr_cnv {
			//
			// modulus
			//
			template<std::size_t Limit, typename T, typename... Args>
			inline SPROUT_CONSTEXPR typename sprout::weed::attr_cnv::results::modulus<Limit, T>::type
			modulus(Args const&... args) {
				return sprout::weed::attr_cnv::times<Limit, T>(args...);
			}
		}	// namespace attr_cnv
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_ATTR_CNV_MODULUS_HPP
