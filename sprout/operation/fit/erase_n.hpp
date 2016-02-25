/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_OPERATION_FIT_ERASE_N_HPP
#define SPROUT_OPERATION_FIT_ERASE_N_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/operation/fixed/erase_n.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/sub.hpp>

namespace sprout {
	namespace fit {
		namespace results {
			//
			// erase_n
			//
			template<std::size_t N, typename Container>
			struct erase_n {
			public:
				typedef sprout::sub_array<
					typename sprout::container_traits<
						typename sprout::fixed::results::erase_n<N, Container>::type
					>::internal_type
				> type;
			};
		}	// namespace results

		//
		// erase_n
		//
		template<std::size_t N, typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fit::results::erase_n<N, Container>::type
		erase_n(Container const& cont, typename sprout::container_traits<Container>::const_iterator pos) {
			return sprout::sub_copy(
				sprout::get_internal(sprout::fixed::erase_n<N>(cont, pos)),
				sprout::internal_begin_offset(cont),
				sprout::internal_end_offset(cont) - 1
				);
		}
		template<std::size_t N, typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fit::results::erase_n<N, Container>::type
		erase_n(Container const& cont, typename sprout::container_traits<Container>::difference_type pos) {
			return sprout::sub_copy(
				sprout::get_internal(sprout::fixed::erase_n<N>(cont, pos)),
				sprout::internal_begin_offset(cont),
				sprout::internal_end_offset(cont) - 1
				);
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIT_ERASE_N_HPP
