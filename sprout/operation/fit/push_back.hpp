#ifndef SPROUT_OPERATION_FIT_PUSH_BACK_HPP
#define SPROUT_OPERATION_FIT_PUSH_BACK_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/operation/fixed/push_back.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace fit {
		namespace result_of {
			//
			// push_back
			//
			template<typename Container, typename T, typename... Values>
			struct push_back {
			public:
				typedef sprout::sub_array<
					typename sprout::fixed_container_traits<
						typename sprout::fixed::result_of::push_back<Container, T, Values...>::type
					>::internal_type
				> type;
			};
		}	// namespace result_of

		//
		// push_back
		//
		template<typename Container, typename T, typename... Values>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::push_back<Container, T, Values...>::type push_back(
			Container const& cont,
			T const& v,
			Values const&... values
			)
		{
			return sprout::sub_copy(
				sprout::get_fixed(sprout::fixed::push_back(cont, v, values...)),
				sprout::fixed_begin_offset(cont),
				sprout::fixed_end_offset(cont) + 1 + sizeof...(Values)
				);
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIT_PUSH_BACK_HPP
