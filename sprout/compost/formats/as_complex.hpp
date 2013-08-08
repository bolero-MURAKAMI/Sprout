/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPOST_FORMATS_AS_COMPLEX_HPP
#define SPROUT_COMPOST_FORMATS_AS_COMPLEX_HPP

#include <sprout/config.hpp>
#include <sprout/complex.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/range/adaptor/transformed.hpp>

namespace sprout {
	namespace compost {
		//
		// to_complex_value
		//
		struct to_complex_value {
		public:
			template<typename FloatType>
			SPROUT_CONSTEXPR sprout::complex<FloatType> operator()(FloatType const& x) const {
				return sprout::complex<FloatType>(x);
			}
		};

		namespace formats {
			//
			// as_complex_forwarder
			//
			class as_complex_forwarder {};

			//
			// as_complex
			//
			namespace {
				SPROUT_STATIC_CONSTEXPR sprout::compost::formats::as_complex_forwarder as_complex = {};
			}	// anonymous-namespace

			//
			// operator|
			//
			template<typename Range>
			inline SPROUT_CONSTEXPR auto
			operator|(Range&& lhs, sprout::compost::formats::as_complex_forwarder const&)
			-> decltype(
				sprout::forward<Range>(lhs)
					| sprout::adaptors::transformed(sprout::compost::to_complex_value())
				)
			{
				return sprout::forward<Range>(lhs)
					| sprout::adaptors::transformed(sprout::compost::to_complex_value())
					;
			}
		}	// namespace formats

		using sprout::compost::formats::as_complex;
	}	// namespace compost
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPOST_FORMATS_AS_COMPLEX_HPP
