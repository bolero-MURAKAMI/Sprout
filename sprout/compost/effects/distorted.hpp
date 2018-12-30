/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPOST_EFFECTS_DISTORTED_HPP
#define SPROUT_COMPOST_EFFECTS_DISTORTED_HPP

#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/compost/effects/clipped.hpp>
#include <sprout/compost/effects/changed_volume.hpp>

namespace sprout {
	namespace compost {
		namespace effects {
			//
			// distort_holder
			//
			template<typename T>
			class distort_holder {
			public:
				typedef T value_type;
			private:
				value_type gain_;
				value_type level_;
			public:
				SPROUT_CONSTEXPR distort_holder() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
				distort_holder(distort_holder const&) = default;
				SPROUT_CONSTEXPR distort_holder(value_type const& gain, value_type const& level)
					: gain_(gain), level_(level)
				{}
				SPROUT_CONSTEXPR value_type const& gain() const {
					return gain_;
				}
				SPROUT_CONSTEXPR value_type const& level() const {
					return level_;
				}
			};

			//
			// distorted_forwarder
			//
			class distorted_forwarder {
			public:
				template<typename T>
				SPROUT_CONSTEXPR sprout::compost::effects::distort_holder<T>
				operator()(T const& gain, T const& level) const {
					return sprout::compost::effects::distort_holder<T>(gain, level);
				}
			};

			//
			// distorted
			//
			namespace {
				SPROUT_STATIC_CONSTEXPR sprout::compost::effects::distorted_forwarder distorted = {};
			}	// anonymous-namespace

			//
			// operator|
			//
			template<typename Range, typename T>
			inline SPROUT_CONSTEXPR auto
			operator|(Range&& lhs, sprout::compost::effects::distort_holder<T> const& rhs)
			-> decltype(
				SPROUT_FORWARD(Range, lhs)
					| sprout::compost::effects::changed_volume(rhs.gain())
					| sprout::compost::effects::clipped()
					| sprout::compost::effects::changed_volume(rhs.level())
				)
			{
				return SPROUT_FORWARD(Range, lhs)
					| sprout::compost::effects::changed_volume(rhs.gain())
					| sprout::compost::effects::clipped()
					| sprout::compost::effects::changed_volume(rhs.level())
					;
			}
		}	// namespace effects

		using sprout::compost::effects::distorted;
	}	// namespace compost
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPOST_EFFECTS_DISTORTED_HPP
