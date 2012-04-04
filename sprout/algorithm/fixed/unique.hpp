#ifndef SPROUT_ALGORITHM_FIXED_UNIQUE_HPP
#define SPROUT_ALGORITHM_FIXED_UNIQUE_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/unique_copy.hpp>

namespace sprout {
	namespace fixed {
		//
		// unique
		//
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type unique(
			Container const& cont
			)
		{
			return sprout::fixed::unique_copy(sprout::begin(cont), sprout::end(cont), cont);
		}

		//
		// unique
		//
		template<typename Container, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type unique(
			Container const& cont,
			BinaryPredicate pred
			)
		{
			return sprout::fixed::unique_copy(sprout::begin(cont), sprout::end(cont), cont, pred);
		}
	}	// namespace fixed

	using sprout::fixed::unique;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_UNIQUE_HPP
