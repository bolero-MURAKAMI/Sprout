#ifndef SPROUT_ALGORITHM_FIXED_RESULT_OF_HPP
#define SPROUT_ALGORITHM_FIXED_RESULT_OF_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/utility/pair/pair.hpp>

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

			//
			// shuffle
			//
			template<typename Container, typename UniformRandomNumberGenerator>
			struct shuffle {
			public:
				typedef sprout::pair<
					typename sprout::fixed::result_of::algorithm<Container>::type,
					typename std::decay<UniformRandomNumberGenerator>::type
				> type;
			};
		}	// namespace result_of
	}	// namespace fixed

	namespace result_of {
		using sprout::fixed::result_of::algorithm;
		using sprout::fixed::result_of::shuffle;
	}	// namespace result_of
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_RESULT_OF_HPP
