/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPOST_EFFECTS_VOCAL_CANCELLED_HPP
#define SPROUT_COMPOST_EFFECTS_VOCAL_CANCELLED_HPP

#include <sprout/config.hpp>
#include <sprout/utility/lvalue_forward.hpp>
#include <sprout/functional/minus.hpp>
#include <sprout/range/adaptor/transformed.hpp>
#include <sprout/compost/formats/left_channel.hpp>
#include <sprout/compost/formats/right_channel.hpp>

namespace sprout {
	namespace compost {
		namespace effects {
			//
			// vocal_cancelled_forwarder
			//
			class vocal_cancelled_forwarder {};

			//
			// vocal_cancelled
			//
			namespace {
				SPROUT_STATIC_CONSTEXPR sprout::compost::effects::vocal_cancelled_forwarder vocal_cancelled = {};
			}	// anonymous-namespace

			//
			// operator|
			//
			// ???
#if !defined(__clang__)
			template<typename Range>
			inline SPROUT_CONSTEXPR auto
			operator|(Range&& lhs, sprout::compost::effects::vocal_cancelled_forwarder const& rhs)
			-> decltype(
				sprout::lvalue_forward<Range>(lhs) | sprout::compost::formats::left_channel
					| sprout::adaptors::transformed(
						sprout::lvalue_forward<Range>(lhs) | sprout::compost::formats::right_channel,
						sprout::minus<>()
						)
				)
			{
				return sprout::lvalue_forward<Range>(lhs) | sprout::compost::formats::left_channel
					| sprout::adaptors::transformed(
						sprout::lvalue_forward<Range>(lhs) | sprout::compost::formats::right_channel,
						sprout::minus<>()
						)
					;
			}
#endif
		}	// namespace effects

		using sprout::compost::effects::vocal_cancelled;
	}	// namespace compost
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPOST_EFFECTS_VOCAL_CANCELLED_HPP
