#ifndef SPROUT_OPERATION_FIT_JOIN_FRONT_HPP
#define SPROUT_OPERATION_FIT_JOIN_FRONT_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/operation/fixed/join_front.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace fit {
		namespace result_of {
			//
			// join_front
			//
			template<typename Container, typename Input>
			struct join_front {
				typedef sprout::sub_array<
					typename sprout::fixed_container_traits<
						typename sprout::fixed::result_of::join_front<Container, Input>::type
					>::internal_type
				> type;
			};
		}	// namespace result_of

		//
		// join_front
		//
		template<typename Container, typename Input>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::join_front<Container, Input>::type join_front(
			Container const& cont,
			Input const& input
			)
		{
			return sprout::sub_copy(
				sprout::get_fixed(sprout::fixed::join_front(cont, input)),
				sprout::fixed_begin_offset(cont),
				sprout::fixed_end_offset(cont) + sprout::size(input)
				);
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIT_JOIN_FRONT_HPP
