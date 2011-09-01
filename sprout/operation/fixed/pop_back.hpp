#ifndef SPROUT_OPERATION_FIXED_POP_BACK_HPP
#define SPROUT_OPERATION_FIXED_POP_BACK_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/operation/fixed/erase.hpp>

namespace sprout {
	namespace fixed {
		namespace result_of {
			//
			// pop_back
			//
			template<typename Container>
			struct pop_back
				: public erase<Container>
			{};
		}	// namespace result_of

		//
		// pop_back
		//
		template<typename Container>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::pop_back<Container>::type pop_back(
			Container const& cont
			)
		{
			return sprout::fixed::detail::erase_impl<typename sprout::fixed::result_of::pop_back<Container>::type>(
				cont,
				typename sprout::index_range<0, sprout::fixed_container_traits<typename sprout::fixed::result_of::pop_back<Container>::type>::fixed_size>::type(),
				sprout::fixed_end_offset(cont) - 1
				);
		}
	}	// namespace fixed
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIXED_POP_BACK_HPP
