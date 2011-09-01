#ifndef SPROUT_OPERATION_FIT_ERASE_N_HPP
#define SPROUT_OPERATION_FIT_ERASE_N_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/operation/fixed/erase_n.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace fit {
		namespace result_of {
			//
			// erase_n
			//
			template<std::size_t N, typename Container>
			struct erase_n {
			public:
				typedef sprout::sub_array<typename sprout::fixed::result_of::erase_n<N, Container>::type> type;
			};
		}	// namespace result_of

		//
		// erase_n
		//
		template<std::size_t N, typename Container>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::erase_n<N, Container>::type erase_n(
			Container const& cont,
			typename sprout::fixed_container_traits<Container>::const_iterator pos
			)
		{
			return sprout::sub_copy(
				sprout::fixed::erase_n<N>(cont, pos),
				sprout::fixed_begin_offset(cont),
				sprout::fixed_end_offset(cont) - 1
				);
		}
		//
		// erase_n
		//
		template<std::size_t N, typename Container>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::erase_n<N, Container>::type erase_n(
			Container const& cont,
			typename sprout::fixed_container_traits<Container>::difference_type pos
			)
		{
			return sprout::sub_copy(
				sprout::fixed::erase_n<N>(cont, pos),
				sprout::fixed_begin_offset(cont),
				sprout::fixed_end_offset(cont) - 1
				);
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIT_ERASE_N_HPP
