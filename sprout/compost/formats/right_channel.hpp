/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPOST_FORMATS_RIGHT_CHANNEL_HPP
#define SPROUT_COMPOST_FORMATS_RIGHT_CHANNEL_HPP

#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/range/adaptor/steps.hpp>

namespace sprout {
	namespace compost {
		namespace formats {
			//
			// right_channel_forwarder
			//
			class right_channel_forwarder {};

			//
			// right_channel
			//
			namespace {
				SPROUT_STATIC_CONSTEXPR sprout::compost::formats::right_channel_forwarder right_channel = {};
			}	// anonymous-namespace

			//
			// operator|
			//
			template<typename Range, typename T>
			inline SPROUT_CONSTEXPR auto
			operator|(Range&& lhs, right_channel_forwarder const&)
			-> decltype(
				sprout::forward<Range>(lhs)
					| sprout::adaptors::steps(2, 1)
				)
			{
				return sprout::forward<Range>(lhs)
					| sprout::adaptors::steps(2, 1)
					;
			}
		}	// namespace formats

		using sprout::compost::formats::right_channel;
	}	// namespace compost
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPOST_FORMATS_RIGHT_CHANNEL_HPP
