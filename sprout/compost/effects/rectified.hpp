/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPOST_EFFECTS_RECTIFIED_HPP
#define SPROUT_COMPOST_EFFECTS_RECTIFIED_HPP

#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/range/adaptor/transformed.hpp>

namespace sprout {
	namespace compost {
		//
		// rectify_value
		//
		template<typename T = void>
		struct rectify_value {
		public:
			typedef T argument_type;
			typedef T result_type;
		public:
			SPROUT_CONSTEXPR T
			operator()(T const& x) const {
				return x < 0 ? -x : x;
			}
		};
		template<>
		struct rectify_value<void> {
		public:
			template<typename T>
			SPROUT_CONSTEXPR T
			operator()(T const& x) const {
				return sprout::compost::rectify_value<T>()(x);
			}
		};

		namespace effects {
			//
			// rectified_forwarder
			//
			class rectified_forwarder {};

			//
			// rectified
			//
			namespace {
				SPROUT_STATIC_CONSTEXPR sprout::compost::effects::rectified_forwarder rectified = {};
			}	// anonymous-namespace

			//
			// operator|
			//
			template<typename Range>
			inline SPROUT_CONSTEXPR auto
			operator|(Range&& lhs, sprout::compost::effects::rectified_forwarder const&)
			-> decltype(
				SPROUT_FORWARD(Range, lhs)
					| sprout::adaptors::transformed(sprout::compost::rectify_value<>())
				)
			{
				return SPROUT_FORWARD(Range, lhs)
					| sprout::adaptors::transformed(sprout::compost::rectify_value<>())
					;
			}
		}	// namespace effects

		using sprout::compost::effects::rectified;
	}	// namespace compost
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPOST_EFFECTS_RECTIFIED_HPP
