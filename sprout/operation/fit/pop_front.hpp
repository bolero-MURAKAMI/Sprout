#ifndef SPROUT_OPERATION_FIT_POP_FRONT_HPP
#define SPROUT_OPERATION_FIT_POP_FRONT_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
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
				typedef sprout::sub_array<typename sprout::fixed::result_of::pop_front<Container>::type> type;
			};
		}	// namespace result_of

		//
		// pop_front
		//
		template<typename Container>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::pop_front<Container>::type pop_front(
			Container const& cont
			)
		{
			return sprout::sub_copy(
				sprout::fixed::pop_front(cont),
				sprout::fixed_begin_offset(cont),
				sprout::fixed_end_offset(cont) - 1
				);
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIT_POP_FRONT_HPP
