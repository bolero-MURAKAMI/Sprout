/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_OPERATION_FIT_APPEND_HPP
#define SPROUT_OPERATION_FIT_APPEND_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/operation/fixed/append.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/sub.hpp>

namespace sprout {
	namespace fit {
		namespace results {
			//
			// append
			//
			template<typename Container, typename Input>
			struct append {
			public:
				typedef sprout::sub_array<
					typename sprout::container_traits<
						typename sprout::fixed::results::append<Container, Input>::type
					>::internal_type
				> type;
			};
		}	// namespace results

		//
		// append
		//
		template<typename Container, typename Input>
		inline SPROUT_CONSTEXPR typename sprout::fit::results::append<Container, Input>::type
		append(
			Container const& cont, typename sprout::container_traits<Container>::const_iterator pos,
			Input const& input
			)
		{
			return sprout::sub_copy(
				sprout::get_internal(sprout::fixed::append(cont, pos, input)),
				sprout::internal_begin_offset(cont),
				sprout::internal_end_offset(cont) + sprout::size(input)
				);
		}
		template<typename Container, typename Input>
		inline SPROUT_CONSTEXPR typename sprout::fit::results::append<Container, Input>::type
		append(
			Container const& cont, typename sprout::container_traits<Container>::difference_type pos,
			Input const& input
			)
		{
			return sprout::sub_copy(
				sprout::get_internal(sprout::fixed::append(cont, pos, input)),
				sprout::internal_begin_offset(cont),
				sprout::internal_end_offset(cont) + sprout::size(input)
				);
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIT_APPEND_HPP
