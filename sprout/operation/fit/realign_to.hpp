/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_OPERATION_FIT_REALIGN_TO_HPP
#define SPROUT_OPERATION_FIT_REALIGN_TO_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/operation/fixed/realign_to.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/sub.hpp>

namespace sprout {
	namespace fit {
		namespace results {
			//
			// realign_to
			//
			template<typename Result, typename Container>
			struct realign_to {
			public:
				typedef sprout::sub_array<
					typename sprout::container_traits<
						typename sprout::fixed::results::realign_to<Result, Container>::type
					>::internal_type
				> type;
			};
		}	// namespace results

		//
		// realign_to
		//
		template<typename Result, typename Container, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fit::results::realign_to<Result, Container>::type
		realign_to(Container const& cont, T const& v) {
			return sprout::sub_copy(
				sprout::get_internal(sprout::fixed::realign_to<Result>(cont, v)),
				0,
				sprout::size(cont)
				);
		}
		template<typename Result, typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fit::results::realign_to<Result, Container>::type
		realign_to(Container const& cont) {
			return sprout::sub_copy(
				sprout::get_internal(sprout::fixed::realign_to<Result>(cont)),
				0,
				sprout::size(cont)
				);
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIT_REALIGN_TO_HPP
