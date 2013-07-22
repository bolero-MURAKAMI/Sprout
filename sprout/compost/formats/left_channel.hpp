#ifndef SPROUT_COMPOST_FORMATS_LEFT_CHANNEL_HPP
#define SPROUT_COMPOST_FORMATS_LEFT_CHANNEL_HPP

#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/range/adaptor/steps.hpp>

namespace sprout {
	namespace compost {
		namespace formats {
			//
			// left_channel_forwarder
			//
			class left_channel_forwarder {};

			//
			// left_channel
			//
			namespace {
				SPROUT_STATIC_CONSTEXPR sprout::compost::formats::left_channel_forwarder left_channel = {};
			}	// anonymous-namespace

			//
			// operator|
			//
			template<typename Range, typename T>
			inline SPROUT_CONSTEXPR auto
			operator|(Range&& lhs, left_channel_forwarder const&)
			-> decltype(
				sprout::forward<Range>(lhs)
					| sprout::adaptors::steps(2)
				)
			{
				return sprout::forward<Range>(lhs)
					| sprout::adaptors::steps(2)
					;
			}
		}	// namespace formats

		using sprout::compost::formats::left_channel;
	}	// namespace compost
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPOST_FORMATS_LEFT_CHANNEL_HPP
