#ifndef SPROUT_ALGORITHM_FIXED_RESULT_OF_HPP
#define SPROUT_ALGORITHM_FIXED_RESULT_OF_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>

namespace sprout {
	namespace fixed {
		namespace result_of {
			//
			// algorithm
			//
			template<typename Result>
			struct algorithm {
			public:
				typedef typename sprout::container_construct_traits<Result>::copied_type type;
			};
		}	// namespace result_of
	}	// namespace fixed

	namespace result_of {
		using sprout::fixed::result_of::algorithm;
	}	// namespace result_of
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_RESULT_OF_HPP
