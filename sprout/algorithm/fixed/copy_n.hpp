#ifndef SPROUT_ALGORITHM_FIXED_COPY_N_HPP
#define SPROUT_ALGORITHM_FIXED_COPY_N_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/copy.hpp>

namespace sprout {
	namespace fixed {
		//
		// copy_n
		//
		template<typename Iterator, typename Size, typename Result>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type copy_n(
			Iterator first,
			Size n,
			Result const& result
			)
		{
			return sprout::fixed::detail::copy_impl(
				first,
				first + n,
				result,
				typename sprout::index_range<0, sprout::fixed_container_traits<Result>::fixed_size>::type(),
				sprout::fixed_begin_offset(result),
				sprout::size(result),
				n
				);
		}
	}	// namespace fixed

	using sprout::fixed::copy_n;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_COPY_N_HPP
