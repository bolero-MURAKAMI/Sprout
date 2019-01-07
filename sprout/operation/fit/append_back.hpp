/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_OPERATION_FIT_APPEND_BACK_HPP
#define SPROUT_OPERATION_FIT_APPEND_BACK_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/operation/fixed/append_back.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/sub.hpp>

namespace sprout {
	namespace fit {
		namespace results {
			//
			// append_back
			//
			template<typename Container, typename Input>
			struct append_back {
				typedef sprout::sub_array<
					typename sprout::container_traits<
						typename sprout::fixed::results::append_back<Container, Input>::type
					>::internal_type
				> type;
			};
		}	// namespace results

		//
		// append_back
		//
		template<typename Container, typename Input>
		inline SPROUT_CONSTEXPR typename sprout::fit::results::append_back<Container, Input>::type
		append_back(Container const& cont, Input const& input) {
			return sprout::sub_copy(
				sprout::get_internal(sprout::fixed::append_back(cont, input)),
				sprout::internal_begin_offset(cont),
				sprout::internal_end_offset(cont) + sprout::size(input)
				);
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIT_APPEND_BACK_HPP
