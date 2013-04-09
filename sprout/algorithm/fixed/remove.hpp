#ifndef SPROUT_ALGORITHM_FIXED_REMOVE_HPP
#define SPROUT_ALGORITHM_FIXED_REMOVE_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/remove_copy.hpp>

namespace sprout {
	namespace fixed {
		//
		// remove
		//
		template<typename Container, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type
		remove(Container const& cont, T const& value) {
			return sprout::fixed::remove_copy(sprout::begin(cont), sprout::end(cont), cont, value);
		}
	}	// namespace fixed

	using sprout::fixed::remove;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_REMOVE_HPP
