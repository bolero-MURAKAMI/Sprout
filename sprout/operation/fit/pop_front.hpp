#ifndef SPROUT_OPERATION_FIT_POP_FRONT_HPP
#define SPROUT_OPERATION_FIT_POP_FRONT_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/operation/fixed/pop_front.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace fit {
		namespace result_of {
			//
			// pop_front
			//
			template<typename Container>
			struct pop_front {
			public:
				typedef sprout::sub_array<
					typename sprout::container_traits<
						typename sprout::fixed::result_of::pop_front<Container>::type
					>::internal_type
				> type;
			};
		}	// namespace result_of

		//
		// pop_front
		//
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::pop_front<Container>::type
		pop_front(Container const& cont) {
			return sprout::sub_copy(
				sprout::get_internal(sprout::fixed::pop_front(cont)),
				sprout::internal_begin_offset(cont),
				sprout::internal_end_offset(cont) - 1
				);
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIT_POP_FRONT_HPP
