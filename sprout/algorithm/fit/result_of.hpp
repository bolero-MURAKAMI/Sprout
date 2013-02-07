#ifndef SPROUT_ALGORITHM_FIT_RESULT_OF_HPP
#define SPROUT_ALGORITHM_FIT_RESULT_OF_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/metafunctions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/sub_array/sub_array.hpp>

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
					typename std::decay<
						typename sprout::containers::internal<
							typename sprout::fixed::result_of::algorithm<Result>::type
						>::type
					>::type
				> type;
			};
		}	// namespace result_of
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_RESULT_OF_HPP
