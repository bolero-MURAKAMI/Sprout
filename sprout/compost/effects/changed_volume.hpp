/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPOST_EFFECTS_CHANGED_VOLUME_HPP
#define SPROUT_COMPOST_EFFECTS_CHANGED_VOLUME_HPP

#include <sprout/config.hpp>
#include <sprout/functional/multiplies.hpp>
#include <sprout/functional/bind2nd.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/range/adaptor/transformed.hpp>

namespace sprout {
	namespace compost {
		namespace effects {
			//
			// change_volume_holder
			//
			template<typename T>
			class change_volume_holder {
			public:
				typedef T value_type;
			private:
				value_type value_;
			public:
				SPROUT_CONSTEXPR change_volume_holder() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
				change_volume_holder(change_volume_holder const&) = default;
				explicit SPROUT_CONSTEXPR change_volume_holder(value_type const& value)
					: value_(value)
				{}
				SPROUT_CONSTEXPR value_type const& value() const {
					return value_;
				}
			};

			//
			// changed_volume_forwarder
			//
			class changed_volume_forwarder {
			public:
				template<typename T>
				SPROUT_CONSTEXPR sprout::compost::effects::change_volume_holder<T>
				operator()(T const& value) const {
					return sprout::compost::effects::change_volume_holder<T>(value);
				}
			};

			//
			// changed_volume
			//
			namespace {
				SPROUT_STATIC_CONSTEXPR sprout::compost::effects::changed_volume_forwarder changed_volume = {};
			}	// anonymous-namespace

			//
			// operator|
			//
			template<typename Range, typename T>
			inline SPROUT_CONSTEXPR auto
			operator|(Range&& lhs, sprout::compost::effects::change_volume_holder<T> const& rhs)
			-> decltype(
				SPROUT_FORWARD(Range, lhs)
					| sprout::adaptors::transformed(sprout::bind2nd(sprout::multiplies<>(), rhs.value()))
				)
			{
				return SPROUT_FORWARD(Range, lhs)
					| sprout::adaptors::transformed(sprout::bind2nd(sprout::multiplies<>(), rhs.value()))
					;
			}
		}	// namespace effects

		using sprout::compost::effects::changed_volume;
	}	// namespace compost
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPOST_EFFECTS_CHANGED_VOLUME_HPP
