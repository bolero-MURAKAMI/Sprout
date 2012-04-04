#ifndef SPROUT_OPERATION_FIT_APPEND_BACK_HPP
#define SPROUT_OPERATION_FIT_APPEND_BACK_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
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
					typename sprout::container_traits<
						typename sprout::fixed::result_of::append_back<Container, Input>::type
					>::internal_type
				> type;
			};
		}	// namespace result_of

		//
		// append_back
		//
		template<typename Container, typename Input>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::append_back<Container, Input>::type append_back(
			Container const& cont,
			Input const& input
			)
		{
			return sprout::sub_copy(
				sprout::get_internal(sprout::fixed::append_back(cont, input)),
				sprout::internal_begin_offset(cont),
				sprout::internal_end_offset(cont) + sprout::size(input)
				);
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIT_APPEND_BACK_HPP
