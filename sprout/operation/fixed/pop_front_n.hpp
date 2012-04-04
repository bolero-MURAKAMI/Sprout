#ifndef SPROUT_OPERATION_FIXED_POP_FRONT_N_HPP
#define SPROUT_OPERATION_FIXED_POP_FRONT_N_HPP

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
			// pop_front_n
			//
			template<std::size_t N, typename Container>
			struct pop_front_n
				: public sprout::fixed::result_of::erase_n<N, Container>
			{};
		}	// namespace result_of

		//
		// pop_front_n
		//
		template<std::size_t N, typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::pop_front_n<N, Container>::type pop_front_n(
			Container const& cont
			)
		{
			return sprout::fixed::detail::erase_n_impl<N, typename sprout::fixed::result_of::pop_front_n<N, Container>::type>(
				cont,
				typename sprout::index_range<0, sprout::container_traits<typename sprout::fixed::result_of::pop_front_n<N, Container>::type>::static_size>::type(),
				sprout::internal_begin_offset(cont)
				);
		}
	}	// namespace fixed

	namespace result_of {
		using sprout::fixed::result_of::pop_front_n;
	}	// namespace result_of

	using sprout::fixed::pop_front_n;
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIXED_POP_FRONT_N_HPP
