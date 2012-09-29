#ifndef SPROUT_ALGORITHM_FIXED_UNFOLD_N_HPP
#define SPROUT_ALGORITHM_FIXED_UNFOLD_N_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/unfold.hpp>

namespace sprout {
	namespace fixed {
		//
		// unfold_n
		//
		template<typename Container, typename Size, typename Generator, typename Init>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type
		unfold_n(Container const& cont, Size n, Generator const& gen, Init const& init) {
			return sprout::fixed::detail::unfold_impl(cont, gen, init, n);
		}
	}	// namespace fixed

	using sprout::fixed::unfold_n;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_UNFOLD_N_HPP
