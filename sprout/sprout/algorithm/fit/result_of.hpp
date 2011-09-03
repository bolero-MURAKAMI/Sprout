#ifndef SPROUT_ALGORITHM_FIT_RESULT_OF_HPP
#define SPROUT_ALGORITHM_FIT_RESULT_OF_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>

namespace sprout {
	namespace fit {
		namespace result_of {
			//
			// algorithm
			//
			template<typename Result>
			struct algorithm {
			public:
				typedef sprout::sub_array<
					typename sprout::fixed_container_traits<
						typename sprout::fixed::result_of::algorithm<Result>::type
					>::internal_type
				> type;
			};
		}	// namespace result_of
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_RESULT_OF_HPP
