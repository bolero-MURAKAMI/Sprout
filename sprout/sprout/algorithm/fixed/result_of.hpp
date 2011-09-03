#ifndef SPROUT_ALGORITHM_FIXED_RESULT_OF_HPP
#define SPROUT_ALGORITHM_FIXED_RESULT_OF_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>

namespace sprout {
	namespace fixed {
		namespace result_of {
			//
			// algorithm
			//
			template<typename Result>
			struct algorithm {
			public:
				typedef typename sprout::fixed_container_traits<Result>::clone_type type;
			};
		}	// namespace result_of
	}	// namespace fixed

	namespace result_of {
		using sprout::fixed::result_of::algorithm;
	}	// namespace result_of
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_RESULT_OF_HPP
