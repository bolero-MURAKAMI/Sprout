/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPOST_EFFECTS_CLIPPED_HPP
#define SPROUT_COMPOST_EFFECTS_CLIPPED_HPP

#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/range/adaptor/clamped.hpp>

namespace sprout {
	namespace compost {
		namespace effects {
			//
			// clip_holder
			//
			template<typename T>
			class clip_holder {
			public:
				typedef T value_type;
			private:
				value_type low_;
				value_type up_;
			public:
				SPROUT_CONSTEXPR clip_holder() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
				clip_holder(clip_holder const&) = default;
				explicit SPROUT_CONSTEXPR clip_holder(value_type const& low = -1, value_type const& up = 1)
					: low_(low), up_(up)
				{}
				SPROUT_CONSTEXPR value_type const& lower() const {
					return low_;
				}
				SPROUT_CONSTEXPR value_type const& upper() const {
					return up_;
				}
			};

			//
			// clipped_forwarder
			//
			class clipped_forwarder {
			public:
				template<typename T = double>
				SPROUT_CONSTEXPR sprout::compost::effects::clip_holder<T>
				operator()(T const& low = -1, T const& up = 1) const {
					return sprout::compost::effects::clip_holder<T>(low, up);
				}
			};

			//
			// clipped
			//
			namespace {
				SPROUT_STATIC_CONSTEXPR sprout::compost::effects::clipped_forwarder clipped = {};
			}	// anonymous-namespace

			//
			// operator|
			//
			template<typename Range, typename T>
			inline SPROUT_CONSTEXPR auto
			operator|(Range&& lhs, sprout::compost::effects::clip_holder<T> const& rhs)
			-> decltype(
				sprout::forward<Range>(lhs)
					| sprout::adaptors::clamped(rhs.lower(), rhs.upper())
				)
			{
				return sprout::forward<Range>(lhs)
					| sprout::adaptors::clamped(rhs.lower(), rhs.upper())
					;
			}
			template<typename Range>
			inline SPROUT_CONSTEXPR auto
			operator|(Range&& lhs, sprout::compost::effects::clipped_forwarder const&)
			-> decltype(
				sprout::forward<Range>(lhs)
					| sprout::adaptors::clamped(-1., 1.)
				)
			{
				return sprout::forward<Range>(lhs)
					| sprout::adaptors::clamped(-1., 1.)
					;
			}
		}	// namespace effects

		using sprout::compost::effects::clipped;
	}	// namespace compost
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPOST_EFFECTS_CLIPPED_HPP
