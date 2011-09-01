#ifndef SPROUT_OPERATION_FIT_PUSH_BACK_N_HPP
#define SPROUT_OPERATION_FIT_PUSH_BACK_N_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/operation/fixed/push_back_n.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace fit {
		namespace result_of {
			//
			// push_back_n
			//
			template<std::size_t N, typename Container, typename T, typename... Values>
			struct push_back_n {
			public:
				typedef sprout::sub_array<typename sprout::fixed::result_of::push_back_n<N, Container, T, Values...>::type> type;
			};
		}	// namespace result_of

		//
		// push_back_n
		//
		template<std::size_t N, typename Container, typename T, typename... Values>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::push_back_n<N, Container, T, Values...>::type push_back_n(
			Container const& cont,
			T const& v,
			Values const&... values
			)
		{
			return sprout::sub_copy(
				sprout::fixed::push_back_n<N>(cont, v, values...),
				sprout::fixed_begin_offset(cont),
				sprout::fixed_end_offset(cont) + (1 + sizeof...(Values)) * N
				);
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIT_PUSH_BACK_N_HPP
