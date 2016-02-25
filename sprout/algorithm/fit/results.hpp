/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIT_RESULTS_HPP
#define SPROUT_ALGORITHM_FIT_RESULTS_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/metafunctions.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/sub_array/sub_array.hpp>

namespace sprout {
	namespace fit {
		namespace results {
			//
			// algorithm
			//
			template<typename Result>
			struct algorithm {
			public:
				typedef sprout::sub_array<
					typename std::decay<
						typename sprout::containers::internal<
							typename sprout::fixed::results::algorithm<Result>::type
						>::type
					>::type
				> type;
			};
		}	// namespace results
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_RESULTS_HPP
