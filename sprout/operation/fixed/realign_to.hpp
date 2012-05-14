#ifndef SPROUT_OPERATION_FIXED_REALIGN_TO_HPP
#define SPROUT_OPERATION_FIXED_REALIGN_TO_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/operation/fixed/realign.hpp>

namespace sprout {
	namespace fixed {
		namespace result_of {
			//
			// realign_to
			//
			template<typename Result, typename Container>
			struct realign_to {
			public:
				typedef typename sprout::container_construct_traits<Result>::copied_type type;
			};
		}	// namespace result_of

		//
		// realign_to
		//
		template<typename Result, typename Container, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::realign_to<Result, Container>::type realign_to(
			Container const& cont,
			T const& v
			)
		{
			return sprout::fixed::detail::realign_impl<typename sprout::fixed::result_of::realign_to<Result, Container>::type>(
				cont,
				sprout::index_range<0, sprout::container_traits<typename sprout::fixed::result_of::realign_to<Result, Container>::type>::static_size>::make(),
				sprout::size(cont),
				v
				);
		}

		//
		// realign_to
		//
		template<typename Result, typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::realign_to<Result, Container>::type realign_to(
			Container const& cont
			)
		{
			return sprout::fixed::detail::realign_impl<typename sprout::fixed::result_of::realign_to<Result, Container>::type>(
				cont,
				sprout::index_range<0, sprout::container_traits<typename sprout::fixed::result_of::realign_to<Result, Container>::type>::static_size>::make(),
				sprout::size(cont)
				);
		}
	}	// namespace fixed

	namespace result_of {
		using sprout::fixed::result_of::realign_to;
	}	// namespace result_of

	using sprout::fixed::realign_to;
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIXED_REALIGN_TO_HPP
