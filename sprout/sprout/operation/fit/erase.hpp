#ifndef SPROUT_OPERATION_FIT_ERASE_HPP
#define SPROUT_OPERATION_FIT_ERASE_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/operation/fixed/erase.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace fit {
		namespace result_of {
			//
			// erase
			//
			template<typename Container>
			struct erase {
			public:
				typedef sprout::sub_array<
					typename sprout::fixed_container_traits<
						typename sprout::fixed::result_of::erase<Container>::type
					>::internal_type
				> type;
			};
		}	// namespace result_of

		//
		// erase
		//
		template<typename Container>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::erase<Container>::type erase(
			Container const& cont,
			typename sprout::fixed_container_traits<Container>::const_iterator pos
			)
		{
			return sprout::sub_copy(
				sprout::get_fixed(sprout::fixed::erase(cont, pos)),
				sprout::fixed_begin_offset(cont),
				sprout::fixed_end_offset(cont) - 1
				);
		}
		//
		// erase
		//
		template<typename Container>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::erase<Container>::type erase(
			Container const& cont,
			typename sprout::fixed_container_traits<Container>::difference_type pos
			)
		{
			return sprout::sub_copy(
				sprout::get_fixed(sprout::fixed::erase(cont, pos)),
				sprout::fixed_begin_offset(cont),
				sprout::fixed_end_offset(cont) - 1
				);
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIT_ERASE_HPP
