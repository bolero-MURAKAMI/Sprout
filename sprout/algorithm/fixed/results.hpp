/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIXED_RESULT_OF_HPP
#define SPROUT_ALGORITHM_FIXED_RESULT_OF_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/utility/pair/pair.hpp>

namespace sprout {
	namespace fixed {
		namespace results {
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
					typename sprout::fixed::results::algorithm<Container>::type,
					typename std::decay<UniformRandomNumberGenerator>::type
				> type;
			};
		}	// namespace results
	}	// namespace fixed

	namespace results {
		using sprout::fixed::results::algorithm;
		using sprout::fixed::results::shuffle;
	}	// namespace results
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_RESULT_OF_HPP
