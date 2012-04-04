#ifndef SPROUT_OPERATION_FIXED_POP_BACK_N_HPP
#define SPROUT_OPERATION_FIXED_POP_BACK_N_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/operation/fixed/erase_n.hpp>

namespace sprout {
	namespace fixed {
		namespace result_of {
			//
			// pop_back_n
			//
			template<std::size_t N, typename Container>
			struct pop_back_n
				: public sprout::fixed::result_of::erase_n<N, Container>
			{};
		}	// namespace result_of

		//
		// pop_back_n
		//
		template<std::size_t N, typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::pop_back_n<N, Container>::type pop_back_n(
			Container const& cont
			)
		{
			return sprout::fixed::detail::erase_n_impl<N, typename sprout::fixed::result_of::pop_back_n<N, Container>::type>(
				cont,
				typename sprout::index_range<0, sprout::container_traits<typename sprout::fixed::result_of::pop_back_n<N, Container>::type>::static_size>::type(),
				sprout::internal_end_offset(cont) - N
				);
		}
	}	// namespace fixed

	namespace result_of {
		using sprout::fixed::result_of::pop_back_n;
	}	// namespace result_of

	using sprout::fixed::pop_back_n;
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIXED_POP_BACK_N_HPP
