#ifndef SPROUT_OPERATION_FIT_PUSH_FRONT_HPP
#define SPROUT_OPERATION_FIT_PUSH_FRONT_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/operation/fixed/push_front.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace fit {
		namespace result_of {
			//
			// push_front
			//
			template<typename Container, typename T, typename... Values>
			struct push_front {
			public:
				typedef sprout::sub_array<typename sprout::fixed::result_of::push_front<Container, T, Values...>::type> type;
			};
		}	// namespace result_of

		//
		// push_front
		//
		template<typename Container, typename T, typename... Values>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::push_front<Container, T, Values...>::type push_front(
			Container const& cont,
			T const& v,
			Values const&... values
			)
		{
			return sprout::sub_copy(
				sprout::fixed::push_front(cont, v, values...),
				sprout::fixed_begin_offset(cont),
				sprout::fixed_end_offset(cont) + 1 + sizeof...(Values)
				);
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIT_PUSH_FRONT_HPP
