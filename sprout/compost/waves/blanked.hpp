/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPOST_WAVES_BLANKED_HPP
#define SPROUT_COMPOST_WAVES_BLANKED_HPP

#include <sprout/config.hpp>
#include <sprout/range/adaptor/blanked.hpp>

namespace sprout {
	namespace compost {
		namespace waves {
			//
			// blanked_forwarder
			//
			class blanked_forwarder {
			public:
				SPROUT_CONSTEXPR sprout::adaptors::blanked_range<double>
				operator()() const {
					return sprout::adaptors::blanked_range<double>();
				}
				template<typename Difference>
				SPROUT_CONSTEXPR sprout::adaptors::blanked_range<double>
				operator()(Difference n) const {
					return sprout::adaptors::blanked_range<double>(n);
				}
				template<typename T, typename Difference>
				SPROUT_CONSTEXPR sprout::adaptors::blanked_range<T>
				operator()(Difference n, T const& value) const {
					return sprout::adaptors::blanked_range<T>(n, value);
				}
			};

			//
			// blanked
			//
			namespace {
				SPROUT_STATIC_CONSTEXPR sprout::compost::waves::blanked_forwarder blanked = {};
			}	// anonymous-namespace
		}	// namespace waves

		using sprout::compost::waves::blanked;
	}	// namespace compost
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPOST_WAVES_BLANKED_HPP
