/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_ATTR_CNV_RESULTS_MEM_PTR_HPP
#define SPROUT_WEED_ATTR_CNV_RESULTS_MEM_PTR_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/result_of.hpp>

namespace sprout {
	namespace weed {
		namespace attr_cnv {
			namespace results {
				//
				// mem_ptr
				//
				template<typename T, typename U, typename = void>
				struct mem_ptr
					: public sprout::result_of<U(T)>
				{};
			}	// namespace results
		}	// namespace attr_cnv
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_ATTR_CNV_RESULTS_MEM_PTR_HPP
