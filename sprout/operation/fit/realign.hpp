#ifndef SPROUT_OPERATION_FIT_REALIGN_HPP
#define SPROUT_OPERATION_FIT_REALIGN_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/operation/fixed/realign.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace fit {
		namespace result_of {
			//
			// realign
			//
			template<typename Container>
			struct realign {
			public:
				typedef sprout::sub_array<typename sprout::fixed::result_of::realign<Container>::type> type;
			};
		}	// namespace result_of

		//
		// realign
		//
		template<typename Container, typename T>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::realign<Container>::type realign(
			Container const& cont,
			T const& v
			)
		{
			return sprout::sub_copy(
				sprout::fixed::realign(cont, v),
				0,
				sprout::size(cont)
				);
		}

		//
		// realign
		//
		template<typename Container>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::realign<Container>::type realign(
			Container const& cont
			)
		{
			return sprout::sub_copy(
				sprout::fixed::realign(cont),
				0,
				sprout::size(cont)
				);
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIT_REALIGN_HPP
