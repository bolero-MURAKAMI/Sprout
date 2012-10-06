#ifndef SPROUT_OPERATION_FIT_PUSH_BACK_N_HPP
#define SPROUT_OPERATION_FIT_PUSH_BACK_N_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
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
				typedef sprout::sub_array<
					typename sprout::container_traits<
						typename sprout::fixed::result_of::push_back_n<N, Container, T, Values...>::type
					>::internal_type
				> type;
			};
		}	// namespace result_of

		//
		// push_back_n
		//
		template<std::size_t N, typename Container, typename T, typename... Values>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::push_back_n<N, Container, T, Values...>::type
		push_back_n(Container const& cont, T const& v, Values const&... values) {
			return sprout::sub_copy(
				sprout::get_internal(sprout::fixed::push_back_n<N>(cont, v, values...)),
				sprout::internal_begin_offset(cont),
				sprout::internal_end_offset(cont) + (1 + sizeof...(Values)) * N
				);
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIT_PUSH_BACK_N_HPP
