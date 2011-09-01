#ifndef SPROUT_OPERATION_FIXED_POP_FRONT_HPP
#define SPROUT_OPERATION_FIXED_POP_FRONT_HPP

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
			// pop_front
			//
			template<typename Container>
			struct pop_front
				: public erase<Container>
			{};
		}	// namespace result_of

		//
		// pop_front
		//
		template<typename Container>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::pop_front<Container>::type pop_front(
			Container const& cont
			)
		{
			return sprout::fixed::detail::erase_impl<typename sprout::fixed::result_of::pop_front<Container>::type>(
				cont,
				typename sprout::index_range<0, sprout::fixed_container_traits<typename sprout::fixed::result_of::pop_front<Container>::type>::fixed_size>::type(),
				sprout::fixed_begin_offset(cont)
				);
		}
	}	// namespace fixed
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIXED_POP_FRONT_HPP
