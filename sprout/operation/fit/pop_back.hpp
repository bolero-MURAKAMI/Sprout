/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_OPERATION_FIT_POP_BACK_HPP
#define SPROUT_OPERATION_FIT_POP_BACK_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/operation/fixed/pop_back.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/sub.hpp>

namespace sprout {
	namespace fit {
		namespace results {
			//
			// pop_back
			//
			template<typename Container>
			struct pop_back {
			public:
				typedef sprout::sub_array<
					typename sprout::container_traits<
						typename sprout::fixed::results::pop_back<Container>::type
					>::internal_type
				> type;
			};
		}	// namespace results

		//
		// pop_back
		//
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fit::results::pop_back<Container>::type
		pop_back(Container const& cont) {
			return sprout::sub_copy(
				sprout::get_internal(sprout::fixed::pop_back(cont)),
				sprout::internal_begin_offset(cont),
				sprout::internal_end_offset(cont) - 1
				);
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIT_POP_BACK_HPP
