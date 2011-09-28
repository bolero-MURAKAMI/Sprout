#ifndef SPROUT_OPERATION_FIT_APPEND_BACK_HPP
#define SPROUT_OPERATION_FIT_APPEND_BACK_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/operation/fixed/append_back.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace fit {
		namespace result_of {
			//
			// append_back
			//
			template<typename Container, typename Input>
			struct append_back {
				typedef sprout::sub_array<
					typename sprout::fixed_container_traits<
						typename sprout::fixed::result_of::append_back<Container, Input>::type
					>::internal_type
				> type;
			};
		}	// namespace result_of

		//
		// append_back
		//
		template<typename Container, typename Input>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::append_back<Container, Input>::type append_back(
			Container const& cont,
			Input const& input
			)
		{
			return sprout::sub_copy(
				sprout::get_fixed(sprout::fixed::append_back(cont, input)),
				sprout::fixed_begin_offset(cont),
				sprout::fixed_end_offset(cont) + sprout::size(input)
				);
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIT_APPEND_BACK_HPP
