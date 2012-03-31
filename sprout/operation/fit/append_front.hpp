#ifndef SPROUT_OPERATION_FIT_APPEND_FRONT_HPP
#define SPROUT_OPERATION_FIT_APPEND_FRONT_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/operation/fixed/append_front.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace fit {
		namespace result_of {
			//
			// append_front
			//
			template<typename Container, typename Input>
			struct append_front {
				typedef sprout::sub_array<
					typename sprout::container_traits<
						typename sprout::fixed::result_of::append_front<Container, Input>::type
					>::internal_type
				> type;
			};
		}	// namespace result_of

		//
		// append_front
		//
		template<typename Container, typename Input>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::append_front<Container, Input>::type append_front(
			Container const& cont,
			Input const& input
			)
		{
			return sprout::sub_copy(
				sprout::get_internal(sprout::fixed::append_front(cont, input)),
				sprout::internal_begin_offset(cont),
				sprout::internal_end_offset(cont) + sprout::size(input)
				);
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIT_APPEND_FRONT_HPP
