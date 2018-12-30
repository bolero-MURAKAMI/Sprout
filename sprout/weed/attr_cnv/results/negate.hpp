/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_ATTR_CNV_RESULTS_NEGATE_HPP
#define SPROUT_WEED_ATTR_CNV_RESULTS_NEGATE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/weed/unused.hpp>
#include <sprout/weed/traits/type/is_unused.hpp>

namespace sprout {
	namespace weed {
		namespace attr_cnv {
			namespace results {
				//
				// negate
				//
				template<typename T, typename = void>
				struct negate;
				// -unused -> unused
				template<typename T>
				struct negate<
					T,
					typename std::enable_if<
						sprout::weed::traits::is_unused<T>::value
					>::type
				>
					: public sprout::identity<sprout::weed::unused>
				{};
			}	// namespace results
		}	// namespace attr_cnv
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_ATTR_CNV_RESULTS_NEGATE_HPP
