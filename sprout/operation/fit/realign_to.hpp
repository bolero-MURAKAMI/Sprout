#ifndef SPROUT_OPERATION_FIT_REALIGN_TO_HPP
#define SPROUT_OPERATION_FIT_REALIGN_TO_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/operation/fixed/realign_to.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace fit {
		namespace result_of {
			//
			// realign_to
			//
			template<typename Result, typename Container>
			struct realign_to {
			public:
				typedef sprout::sub_array<
					typename sprout::container_traits<
						typename sprout::fixed::result_of::realign_to<Result, Container>::type
					>::internal_type
				> type;
			};
		}	// namespace result_of

		//
		// realign_to
		//
		template<typename Result, typename Container, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::realign_to<Result, Container>::type realign_to(
			Container const& cont,
			T const& v
			)
		{
			return sprout::sub_copy(
				sprout::get_internal(sprout::fixed::realign_to<Result>(cont, v)),
				0,
				sprout::size(cont)
				);
		}

		//
		// realign_to
		//
		template<typename Result, typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::realign_to<Result, Container>::type realign_to(
			Container const& cont
			)
		{
			return sprout::sub_copy(
				sprout::get_internal(sprout::fixed::realign_to<Result>(cont)),
				0,
				sprout::size(cont)
				);
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIT_REALIGN_TO_HPP
