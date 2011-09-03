#ifndef SPROUT_OPERATION_FIXED_JOIN_BACK_HPP
#define SPROUT_OPERATION_FIXED_JOIN_BACK_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/operation/fixed/join.hpp>

namespace sprout {
	namespace fixed {
		namespace result_of {
			//
			// join_back
			//
			template<typename Container, typename Input>
			struct join_back
				: public sprout::fixed::result_of::join<Container, Input>
			{};
		}	// namespace result_of

		//
		// join_back
		//
		template<typename Container, typename Input>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::join_back<Container, Input>::type join_back(
			Container const& cont,
			Input const& input
			)
		{
			return sprout::fixed::detail::join_impl<typename sprout::fixed::result_of::join_back<Container, Input>::type>(
				cont,
				typename sprout::index_range<0, sprout::fixed_container_traits<typename sprout::fixed::result_of::join_back<Container, Input>::type>::fixed_size>::type(),
				sprout::fixed_end_offset(cont),
				sprout::size(input),
				input
				);
		}
	}	// namespace fixed

	namespace result_of {
		using sprout::fixed::result_of::join_back;
	}	// namespace result_of

	using sprout::fixed::join_back;
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIXED_JOIN_BACK_HPP
