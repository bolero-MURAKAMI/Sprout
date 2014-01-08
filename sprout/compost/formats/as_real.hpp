/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPOST_FORMATS_AS_REAL_HPP
#define SPROUT_COMPOST_FORMATS_AS_REAL_HPP

#include <utility>
#include <sprout/config.hpp>
#include <sprout/complex.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/range/adaptor/transformed.hpp>

namespace sprout {
	namespace compost {
		//
		// to_real_value
		//
		struct to_real_value {
		public:
			template<typename Complex>
			SPROUT_CONSTEXPR decltype(real(std::declval<Complex const&>())) operator()(Complex const& x) const {
				return real(x);
			}
		};

		namespace formats {
			//
			// as_real_forwarder
			//
			class as_real_forwarder {};

			//
			// as_real
			//
			namespace {
				SPROUT_STATIC_CONSTEXPR sprout::compost::formats::as_real_forwarder as_real = {};
			}	// anonymous-namespace

			//
			// operator|
			//
			template<typename Range>
			inline SPROUT_CONSTEXPR auto
			operator|(Range&& lhs, sprout::compost::formats::as_real_forwarder const&)
			-> decltype(
				sprout::forward<Range>(lhs)
					| sprout::adaptors::transformed(sprout::compost::to_real_value())
				)
			{
				return sprout::forward<Range>(lhs)
					| sprout::adaptors::transformed(sprout::compost::to_real_value())
					;
			}
		}	// namespace formats

		using sprout::compost::formats::as_real;
	}	// namespace compost
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPOST_FORMATS_AS_REAL_HPP
