/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPOST_FORMATS_STEREO_HPP
#define SPROUT_COMPOST_FORMATS_STEREO_HPP

#include <sprout/config.hpp>
#include <sprout/range/adaptor/alternated.hpp>

namespace sprout {
	namespace compost {
		namespace formats {
			//
			// stereo
			//
			namespace {
				SPROUT_STATIC_CONSTEXPR sprout::adaptors::alternated_forwarder stereo = {};
			}	// anonymous-namespace
		}	// namespace formats

		using sprout::compost::formats::stereo;
	}	// namespace compost
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPOST_FORMATS_STEREO_HPP
