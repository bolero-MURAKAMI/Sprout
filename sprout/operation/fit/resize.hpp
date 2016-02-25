/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_OPERATION_FIT_RESIZE_HPP
#define SPROUT_OPERATION_FIT_RESIZE_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/operation/fixed/resize.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/sub.hpp>

namespace sprout {
	namespace fit {
		namespace results {
			//
			// resize
			//
			template<std::size_t N, typename Container>
			struct resize {
			public:
				typedef sprout::sub_array<
					typename sprout::container_traits<
						typename sprout::fixed::results::resize<N, Container>::type
					>::internal_type
				> type;
			};
		}	// namespace results

		//
		// resize
		//
		template<std::size_t N, typename Container, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fit::results::resize<N, Container>::type
		resize(Container const& cont, T const& v) {
			return sprout::sub_copy(
				sprout::get_internal(sprout::fixed::resize<N>(cont, v)),
				0,
				sprout::container_traits<typename sprout::fit::results::resize<N, Container>::type>::static_size
				);
		}
		template<std::size_t N, typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fit::results::resize<N, Container>::type
		resize(Container const& cont) {
			return sprout::sub_copy(
				sprout::get_internal(sprout::fixed::resize<N>(cont)),
				0,
				sprout::container_traits<typename sprout::fit::results::resize<N, Container>::type>::static_size
				);
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIT_RESIZE_HPP
