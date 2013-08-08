/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPOST_FORMATS_EFFECTED_LEFT_HPP
#define SPROUT_COMPOST_FORMATS_EFFECTED_LEFT_HPP

#include <sprout/config.hpp>
#include <sprout/utility/lvalue_forward.hpp>
#include <sprout/compost/formats/left_channel.hpp>
#include <sprout/compost/formats/right_channel.hpp>
#include <sprout/compost/formats/stereo.hpp>

namespace sprout {
	namespace compost {
		namespace formats {
			//
			// effect_left_holder
			//
			template<typename Adaptor>
			class effect_left_holder {
			public:
				typedef Adaptor adaptor_type;
			private:
				adaptor_type adaptor_;
			public:
				explicit SPROUT_CONSTEXPR effect_left_holder(adaptor_type const& adaptor)
					: adaptor_(adaptor)
				{}
				SPROUT_CONSTEXPR adaptor_type const& adaptor() const {
					return adaptor_;
				}
			};

			//
			// effected_left_cannel_forwarder
			//
			class effected_left_cannel_forwarder {
			public:
				template<typename Adaptor>
				SPROUT_CONSTEXPR sprout::compost::formats::effect_left_holder<Adaptor>
				operator()(Adaptor const& adaptor) const {
					return sprout::compost::formats::effect_left_holder<Adaptor>(adaptor);
				}
			};

			//
			// effected_left_cannel
			//
			namespace {
				SPROUT_STATIC_CONSTEXPR sprout::compost::formats::effected_left_cannel_forwarder effected_left_cannel = {};
			}	// anonymous-namespace

			//
			// operator|
			//
			template<typename Range, typename Adaptor>
			inline SPROUT_CONSTEXPR auto
			operator|(Range&& lhs, sprout::compost::formats::effect_left_holder<Adaptor> const& rhs)
			-> decltype(
				sprout::lvalue_forward<Range>(lhs) | sprout::compost::formats::left_channel | rhs.adaptor()
					| sprout::compost::formats::stereo(sprout::lvalue_forward<Range>(lhs) | sprout::compost::formats::right_channel)
				)
			{
				return sprout::lvalue_forward<Range>(lhs) | sprout::compost::formats::left_channel | rhs.adaptor()
					| sprout::compost::formats::stereo(sprout::lvalue_forward<Range>(lhs) | sprout::compost::formats::right_channel)
					;
			}
		}	// namespace formats

		using sprout::compost::formats::effected_left_cannel;
	}	// namespace compost
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPOST_FORMATS_EFFECTED_LEFT_HPP
